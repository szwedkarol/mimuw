package bajtTrade.nauka;

import bajtTrade.daneJSON.InfoCeny;
import bajtTrade.przedmiotyOferty.Produkt;

import java.util.ArrayList;
import java.util.List;

public abstract class StrNauki {

    public abstract boolean czySięUczy(int dzień, double ileDiamentów, ArrayList<InfoCeny> średnieCeny);

}
