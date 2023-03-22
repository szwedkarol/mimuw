package bajtTrade.nauka;

import bajtTrade.daneJSON.InfoCeny;
import com.squareup.moshi.Json;

import java.util.ArrayList;

public class Oszczędny extends StrNauki {

    @Json(name = "limit_diamentow")
    private static int limit_diamentów;

    public Oszczędny(int limit_diamentów) {
        Oszczędny.limit_diamentów = limit_diamentów;
    }

    @Override
    public boolean czySięUczy(int dzień, double ileDiamentów, ArrayList<InfoCeny> średnieCeny) {
        return ileDiamentów > limit_diamentów;
    }

}
