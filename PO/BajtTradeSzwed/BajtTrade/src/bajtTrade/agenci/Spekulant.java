package bajtTrade.agenci;

import bajtTrade.daneJSON.InfoCeny;
import bajtTrade.przedmiotyOferty.OfertaSpekulant;
import com.squareup.moshi.Json;

import java.util.ArrayList;

public class Spekulant extends Agent {

    @Json(name = "kariera")
    private Kariera strSpekulanta;
    private final static int ILE_KUPIĆ = 100;
    private final static int ILE_TYPÓW_PRODUKTÓW = 4;

    public void wykonajDzień(ArrayList<OfertaSpekulant> ofertySprzedaży,
                             ArrayList<OfertaSpekulant> ofertyKupna,
                             ArrayList<Integer[]> ileWyprodukowano,
                             ArrayList<InfoCeny> średnieCeny, int[] poziom_maks) {
        // Wystawiamy oferty kupna
        for (int i = 0; i < ILE_TYPÓW_PRODUKTÓW; i++ ) {
            if (strSpekulanta.czyKupić(i, średnieCeny, ileWyprodukowano)) {
                for ( int j = 0; j < poziom_maks[i]; j++ ) {
                    String typ = switch (i) {
                        case 0 -> "Jedzenie";
                        case 1 -> "Ubrania";
                        case 2 -> "Narzędzia";
                        case 3 -> "Programy";
                        default -> null;
                    };
                    ofertyKupna.add(new OfertaSpekulant(ILE_KUPIĆ, j, typ, id(),
                            strSpekulanta.zaIleKupić(i, średnieCeny, ileWyprodukowano)));
                }
            }
        }

        // Wystawiamy oferty sprzedaży
        for (int i = 0; i < ILE_TYPÓW_PRODUKTÓW; i++ ) {
            if (strSpekulanta.czyKupić(i, średnieCeny, ileWyprodukowano)) {
                for ( int j = 0; j < poziom_maks[i]; j++ ) {
                    String typ = switch (i) {
                        case 0 -> "Jedzenie";
                        case 1 -> "Ubrania";
                        case 2 -> "Narzędzia";
                        case 3 -> "Programy";
                        default -> null;
                    };

                    int ile = switch (i) {
                        case 0 -> zasoby.jedzenie();
                        case 1 -> zasoby.ubranie(j).sztuki();
                        case 2 -> zasoby.narzędzie(j).sztuki();
                        case 3 -> zasoby.program(j).sztuki();
                        default -> -1;
                    };
                    assert ile != -1;

                    ofertySprzedaży.add(new OfertaSpekulant(ile, j, typ, id(),
                            strSpekulanta.zaIleSprzedać(i, średnieCeny, ileWyprodukowano)));
                }
            }
        }
    }

}
