package bajtTrade.typProdukcji;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class Chciwy extends StrProd {

    @Override
    public String typProdukcji(ArrayList<InfoCeny> średnieCeny, int[] ileByWyprodukował) {
        double[] zysk = new double[4];
        int dzień = średnieCeny.size() - 1;
        int indeks_maks_zysku = 0;

        for (int i = 0; i < 4; i++) {
            zysk[i] = ileByWyprodukował[i] * dzień;
            if (zysk[i] > zysk[indeks_maks_zysku]) {
                indeks_maks_zysku = i;
            }
        }

        return switch (indeks_maks_zysku) {
            case 0 -> "Jedzenie";
            case 1 -> "Ubrania";
            case 2 -> "Narzędzia";
            case 3 -> "Programy";
            default -> throw new IllegalStateException("Unexpected value: " + indeks_maks_zysku);
        };
    }

}
