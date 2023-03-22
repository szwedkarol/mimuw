package bajtTrade.typProdukcji;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;
import java.util.Random;

public class Losowy extends StrProd {

    @Override
    public String typProdukcji(ArrayList<InfoCeny> średnieCeny, int[] ileByWyprodukował) {
        Random rand = new Random();
        return switch (rand.nextInt(5)) {
            case 0 -> "Diamenty";
            case 1 -> "Jedzenie";
            case 2 -> "Ubrania";
            case 3 -> "Narzędzia";
            case 4 -> "Programy";
            default -> throw new IllegalStateException("Unexpected value: " + rand.nextInt(5));
        };
    }
}
