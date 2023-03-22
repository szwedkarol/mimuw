package bajtTrade.typProdukcji;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class Średniak extends StrProd {

    private final int historia_sredniej_produkcji;

    public Średniak(int historia_sredniej_produkcji) {
        this.historia_sredniej_produkcji = historia_sredniej_produkcji;
    }

    @Override
    public String typProdukcji(ArrayList<InfoCeny> średnieCeny, int[] ileByWyprodukował) {
        double[] maks_cena = new double[4];
        int dzień = średnieCeny.size() - 1;
        int indeks_maks_ceny = 0;

        for (int i = 0; i < 4; i++) {
            maks_cena[i] = 0;
            if (maks_cena[i] > maks_cena[indeks_maks_ceny]) {
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
