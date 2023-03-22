package bajtTrade.nauka;

import bajtTrade.daneJSON.InfoCeny;
import bajtTrade.przedmiotyOferty.Produkt;

import java.util.ArrayList;
import java.util.List;

public class Rozkładowy extends StrNauki {

    @Override
    public boolean czySięUczy(int dzień, double ileDiamentów, ArrayList<InfoCeny> średnieCeny) {
        double p = 1.0 / (dzień + 3);
        return Math.random() < p;
    }

}
