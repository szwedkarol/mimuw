package bajtTrade.karieraRobotnik;

import bajtTrade.przedmiotyOferty.OfertaSpekulant;

import java.util.ArrayList;
import java.util.List;

public abstract class StrZmianyKariery {

    public abstract boolean czyZmianaKariery(int dzień);

    public abstract String NowaKariera(int id, int dzień, List<ArrayList<OfertaSpekulant>> historiaTransakcji);

}
