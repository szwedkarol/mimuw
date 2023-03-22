package bajtTrade.karieraRobotnik;

import bajtTrade.przedmiotyOferty.OfertaSpekulant;

import java.util.ArrayList;
import java.util.List;

public class Konserwatysta extends StrZmianyKariery {

    @Override
    public boolean czyZmianaKariery(int dzień) {
        return false;
    }

    @Override
    public String NowaKariera(int id, int dzień, List<ArrayList<OfertaSpekulant>> historiaTransakcji) {
        // Konserwatysta nigdy nie zmienia kariery, więc ta metoda dla niego nie
        // powinna się nigdy wywołać.
        assert true;
        return null;
    }

}
