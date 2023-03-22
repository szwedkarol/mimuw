package bajtTrade.agenci;

import bajtTrade.daneJSON.InfoCeny;
import bajtTrade.karieraRobotnik.Konserwatysta;
import bajtTrade.karieraRobotnik.Rewolucjonista;
import bajtTrade.karieraRobotnik.StrZmianyKariery;
import bajtTrade.karieraRobotnik.Zawód;
import bajtTrade.kupowanie.StrKupowania;
import bajtTrade.nauka.StrNauki;
import bajtTrade.przedmiotyOferty.*;
import bajtTrade.typProdukcji.StrProd;
import com.squareup.moshi.Json;

import java.util.ArrayList;
import java.util.List;

public class Robotnik extends Agent {

    // Określa, czy Robotnik wykonuje jeszcze działania podczas symulacji.
    boolean czyŻywy = true;
    @Json(name = "produktywnosc")
    Produkcja bazowaProdukcja;
    private transient ArrayList<UbraniaNoszone> ubraniaNoszone;
    private int ileNieJadł = 0; // Ile dni Robotnik nie jadł.
    private int kara_za_brak_ubrań;
    private int ileDziśWyprodukowano = 0;
    private String zmiana;
    private String kariera; // Początkowa kariera Robotnika
    private int poziom; // Początkowy poziom Robotnika w karierze

    private transient Zawód zawód; // Opis kariery Robotnika
    @Json(name = "uczenie")
    private StrNauki strNauki;
    @Json(name = "kupowanie")
    private StrKupowania strKupowania;
    private StrZmianyKariery strZmianyKariery;
    @Json(name = "produkcja")
    private StrProd strProd;

    public void dodatkowaInicjalizacja() {
        // Dodatkowa inicjalizacja zawodu Robotnika
        kariera = switch (kariera) {
            case "górnik" -> "Górnik";
            case "rolnik" -> "Rolnik";
            case "rzemieślnik" -> "Rzemieślnik";
            case "inżynier" -> "Inżynier";
            case "programista" -> "Programista";
            default -> throw new IllegalStateException("Unexpected value: " + kariera);
        };
        zawód.aktZawód(kariera);

        while (zawód.aktPoziomKariery() < poziom) {
            zawód.rozwójKariery();
        }

        // Dodatkowa inicjalizacja strategii zmiany kariery przez Robotnika
        if (zmiana.equals("konserwatysta")) {
            strZmianyKariery = new Konserwatysta();
        } else {
            strZmianyKariery = new Rewolucjonista();
        }
    }

    public void wykonajDzień(int dzień, ArrayList<OfertaRobotnik> ofertySprzedaży,
                             ArrayList<OfertaRobotnik> ofertyKupna,
                             List<ArrayList<OfertaSpekulant>> historiaTransakcji,
                             ArrayList<InfoCeny> średnieCeny) {
        ileDziśWyprodukowano = 0;
        if (strNauki.czySięUczy(dzień, diamenty(), średnieCeny)) {
            zawód.rozwójKariery();
            ileNieJadł = 0;
        } else if (strZmianyKariery.czyZmianaKariery(dzień)) {
            zawód.aktZawód(strZmianyKariery.NowaKariera(id(), dzień, historiaTransakcji));
            ileNieJadł = 0;
        } else {
            // Normalny dzień pracy robotnika
            String typProduktu = strProd.typProdukcji(średnieCeny, ileByWyprodukował());

            if (typProduktu.equals("Diamenty")) {
                // Brak ofert sprzedaży wystawianych przez robotnika
                zasoby.dodajDiamenty(produkcjaDiamentów());
            } else {
                ArrayList<Produkt> naSprzedaż = produkcjaNieDiamenty(typProduktu);

                for (Produkt produkt : naSprzedaż) {
                    int ile = produkt.sztuki();
                    int poziom = produkt.poziom();
                    OfertaRobotnik oferta = new OfertaRobotnik(ile, poziom, typProduktu, id());
                    ofertySprzedaży.add(oferta);
                }
            }

            if (strKupowania.ileKupićJedzenia() > 0) {
                ofertyKupna.add(new OfertaRobotnik(100 - zasoby.jedzenie(),
                        1, "Jedzenie", id()));
            }

            if (strKupowania.ileKupićUbrań(ileUbrań()) > 0) {
                ofertyKupna.add(new OfertaRobotnik(strKupowania.ileKupićUbrań(ileUbrań()),
                        1, "Ubrania", id()));
            }

            if (strKupowania.ileKupićNarzędzi() > 0) {
                ofertyKupna.add(new OfertaRobotnik(strKupowania.ileKupićNarzędzi(),
                        1, "Narzędzia", id()));
            }

            if (strKupowania.ileKupićProgramów(ileDziśWyprodukowano) > 0) {
                ofertyKupna.add(new
                        OfertaRobotnik(strKupowania.ileKupićProgramów(ileDziśWyprodukowano),
                        1, "Programy", id()));
            }
        }
    }

    private int[] ileByWyprodukował() {
        return new int[4];
    }

    public void koniecDnia() {
        posiłek();
        nośUbrania();
        zużyjNarzędzia();
        zużyjProgramy();
    }

    private void posiłek() {
        if (zasoby.jedzenie() < 100) {
            zasoby.odejmijJedzenie(zasoby.jedzenie());
            zwiększGłód();
        } else {
            zasoby.odejmijJedzenie(100);
        }

        if (ileNieJadł > 2) {
            czyŻywy = false;
        }
    }

    private void zużyjNarzędzia() {
        zasoby.wyzerujNarzędzia();
    }

    private void zużyjProgramy() {

    }

    private void zwiększGłód() {
        ileNieJadł++;
    }

    private void nośUbrania() {
        int ileZużyliśmy = 0;
        for (int i = 0; ileZużyliśmy < 100 && i < ubraniaNoszone.size(); i++) {
            if (ubraniaNoszone.get(i).sztuki() > 100) {
                // Ponad 100 ubrań w danym rekordzie listy, więc dodajemy nowy
                // rekord na koniec, a poprzednim zmniejszamy liczbę ubrań o 100.
                // Możemy tak zrobić, bo robotnik może tylko początkowo mieć w
                // danym rekordzie listy ponad 100 ubrań, gdyż potem niezależnie
                // od strategii kupowania kupi naraz maksymalnie 100 ubrań,
                // a przez siebie wyprodukowanych nie nosi.
                ubraniaNoszone.add(new UbraniaNoszone(100,
                        ubraniaNoszone.get(i).poziom()));
                ubraniaNoszone.get(ubraniaNoszone.size()-1).zmniejszWytrzymałość();
                ubraniaNoszone.get(i).dodajSztuki(100);
                ileZużyliśmy += 100;
            } else {
                // Mniej niż 100 ubrań w danym rekordzie listy, więc tylko
                // zmniejszamy ich wytrzymałość
                ileZużyliśmy += ubraniaNoszone.get(i).sztuki();
                if (ubraniaNoszone.get(i).wytrzymałość() == 1) {
                    ubraniaNoszone.remove(i);
                } else {
                    ubraniaNoszone.get(i).zmniejszWytrzymałość();
                }
            }
        }
    }

    private int karaGłód() {
        // Robotnik po 3. dniu niejedzenia powinien być martwy.
        assert ileNieJadł <= 3;
        int wynik = 0;

        if (ileNieJadł == 1) {
            wynik = -100;
        }

        if (ileNieJadł == 2) {
            wynik = -300;
        }

        return wynik;
    }

    public ArrayList<Produkt> produkcjaNieDiamenty(String typ) {
        ArrayList<Produkt> wynik = new ArrayList<>();
        int ile = bazowaProdukcja.produkcja(typ);
        int bonus_narzędzia = zasoby.sumaPoziomówNarzędzi();
        int karaUbrania = 0;

        if(!czyMa100Ubrań()) {
            karaUbrania = -kara_za_brak_ubrań;
        }

        int sumaBonusyKary = zawód.bonusProdukcji(typ)
                + karaUbrania + bonus_narzędzia + karaGłód();

        ile += sumaBonusyKary / 100 * bazowaProdukcja.produkcja(typ);
        ileDziśWyprodukowano = ile;

        if (typ.equals("Jedzenie")) {
            Produkt produkt = new Produkt(ile, 1);
            wynik.add(produkt);
        } else if (typ.equals("Programy")) {
            if (zawód.aktZawód().equals("Programista")) {
                Produkt produkt = new Produkt(ile, zawód.aktPoziomKariery());
                wynik.add(produkt);
            } else {
                Produkt produkt = new Produkt(ile, 1);
                wynik.add(produkt);
            }
        } else {
            // Produkcja ubrań lub narzędzi, więc bierzemy pod uwagę programy komputerowe.
            int i = zasoby.programyRozmiar();
            while (zasoby.programyRozmiar() > 0 && ile > 0) {
                if (zasoby.program(i).sztuki() > ile) {
                    Produkt produkt = new Produkt(ile, zasoby.program(i).poziom());
                    zasoby.odejmijProgramy(ile, zasoby.program(i).poziom());
                } else {
                    Produkt produkt = new Produkt(zasoby.program(i).sztuki(), zasoby.program(i).poziom());
                    ile -= zasoby.program(i).sztuki();
                    wynik.add(produkt);
                }
                i--;
            }

            Produkt produkt = new Produkt(ile, 1);
            wynik.add(produkt);
        }

        return wynik;
    }

    public int produkcjaDiamentów() {
        int wynik = bazowaProdukcja.produkcja("Diamenty");
        int bonus_narzędzia = zasoby.sumaPoziomówNarzędzi();
        int karaUbrania = 0;

        if(!czyMa100Ubrań()) {
            karaUbrania = -kara_za_brak_ubrań;
        }

        int sumaBonusyKary = zawód.bonusProdukcji("Diamenty")
                + karaUbrania + bonus_narzędzia + karaGłód();

        wynik += sumaBonusyKary / 100 * bazowaProdukcja.produkcja("Diamenty");

        ileDziśWyprodukowano = Math.max(wynik, 0);
        return Math.max(wynik, 0); // Produkcja zawsze >= 0
    }

    private boolean czyMa100Ubrań() {
        return ileUbrań() >= 100;
    }

    private int ileUbrań() {
        int ileUbrań = 0;
        for (int i = 0; ileUbrań < 100 && i < ubraniaNoszone.size(); i++) {
            ileUbrań += ubraniaNoszone.get(i).sztuki();
        }

        return ileUbrań;
    }

    private ArrayList<UbraniaNoszone> ustawUbraniaNaNoszone() {
        ArrayList<UbraniaNoszone> ubraniaNoszone = new ArrayList<>();

        for (int i = 0; i < zasoby.ubraniaRozmiar(); i++) {
            ubraniaNoszone.add(i, new UbraniaNoszone(zasoby.ubranie(i).sztuki(),
                    zasoby.ubranie(i).poziom()));
            zasoby.odejmijUbrania(zasoby.ubranie(i).sztuki(),
                    zasoby.ubranie(i).poziom());
        }

        return ubraniaNoszone;
    }

    public String aktZawód() {
        return zawód.aktZawód();
    }

    public boolean czyŻywy() {
        return czyŻywy;
    }

}
