package bajtTrade.typProdukcji;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class Krótkowzroczny extends StrProd {

    @Override
    public String typProdukcji(ArrayList<InfoCeny> średnieCeny, int[] ileByWyprodukował) {
        int indeks_maks_ceny = 0;
        int dzień = średnieCeny.size() - 1;

        for (int i = 0; i < 4; i++ ) {
            if (średnieCeny.get(dzień - 1).cena(i) >
                    średnieCeny.get(dzień - 1).cena(indeks_maks_ceny)) {
                indeks_maks_ceny = i;
            }
        }

        return switch (indeks_maks_ceny) {
            case 0 -> "Jedzenie";
            case 1 -> "Ubrania";
            case 2 -> "Narzędzia";
            case 3 -> "Programy";
            default -> throw new IllegalStateException("Unexpected value: " + indeks_maks_ceny);
        };
    }
}
