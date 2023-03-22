package bajtTrade.typProdukcji;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public abstract class StrProd {

    public abstract String typProdukcji(ArrayList<InfoCeny> średnieCeny, int[] ileByWyprodukował);

}
