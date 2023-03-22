package bajtTrade.agenci;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class SpekulantWypukły extends Kariera {

    @Override
    public boolean czyKupić(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        boolean wynik = false;
        int dzień = średnieCeny.size() - 1;

        // Zakładamy, że funkcja złożona z mniej niż 3 punktów nie jest ani
        // wklęsła, ani wypukła
        if (średnieCeny.size() >= 3) {
            wynik = czyWypukła(indeks, średnieCeny);
        }

        return wynik;
    }

    @Override
    public boolean czySprzedać(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        boolean wynik = false;
        int dzień = średnieCeny.size() - 1;

        // Zakładamy, że funkcja złożona z mniej niż 3 punktów nie jest ani
        // wklęsła, ani wypukła
        if (średnieCeny.size() >= 3) {
            wynik = !czyWypukła(indeks, średnieCeny);
        }

        return wynik;
    }

    @Override
    public double zaIleKupić(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        int dzień = średnieCeny.size() - 1;
        return 0.9 * średnieCeny.get(dzień - 1).cena(indeks);
    }

    @Override
    public double zaIleSprzedać(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        int dzień = średnieCeny.size() - 1;
        return 1.1 * średnieCeny.get(dzień - 1).cena(indeks);
    }

    private boolean czyWypukła(int indeks, ArrayList<InfoCeny> średnieCeny) {
        boolean wynik = false;
        int dzień = średnieCeny.size() - 1;

        double a = średnieCeny.get(dzień - 1).cena(indeks);
        double b = średnieCeny.get(dzień - 2).cena(indeks);
        double c = średnieCeny.get(dzień - 3).cena(indeks);
        if (b < (a + c) / 2) {
            wynik = true;
        }

        return wynik;
    }

}
