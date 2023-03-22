package bajtTrade.typProdukcji;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class Perspektywiczny extends StrProd {

    private final int historia_perspektywy;

    public Perspektywiczny(int historia_perspektywy) {
        this.historia_perspektywy = historia_perspektywy;
    }

    @Override
    public String typProdukcji(ArrayList<InfoCeny> średnieCeny, int[] ileByWyprodukował) {
        double[] wzrost = new double[4];
        int dzień = średnieCeny.size() - 1;
        int indeks_maks_wzrostu = 0;

        for (int i = 0; i < 4; i++) {
            wzrost[i] = średnieCeny.get(dzień - 1).cena(i) -
                    średnieCeny.get(dzień - historia_perspektywy).cena(i);
            if (wzrost[i] > wzrost[indeks_maks_wzrostu]) {
                indeks_maks_wzrostu = i;
            }
        }

        return switch (indeks_maks_wzrostu) {
            case 0 -> "Jedzenie";
            case 1 -> "Ubrania";
            case 2 -> "Narzędzia";
            case 3 -> "Programy";
            default -> throw new IllegalStateException("Unexpected value: " + indeks_maks_wzrostu);
        };
    }

}
