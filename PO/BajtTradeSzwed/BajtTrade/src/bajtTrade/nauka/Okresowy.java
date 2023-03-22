package bajtTrade.nauka;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class Okresowy extends StrNauki {

    private static int okresowosc_nauki;

    @Override
    public boolean czySięUczy(int dzień, double ileDiamentów, ArrayList<InfoCeny> średnieCeny) {
        return dzień % okresowosc_nauki == 0;
    }

}
