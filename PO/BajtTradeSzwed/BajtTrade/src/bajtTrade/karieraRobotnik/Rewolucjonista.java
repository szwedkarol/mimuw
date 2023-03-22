package bajtTrade.karieraRobotnik;

import bajtTrade.przedmiotyOferty.OfertaSpekulant;

import java.util.ArrayList;
import java.util.List;

public class Rewolucjonista extends StrZmianyKariery {

    @Override
    public boolean czyZmianaKariery(int dzień) {
        return dzień % 7 == 0;
    }

    @Override
    public String NowaKariera(int id, int dzień, List<ArrayList<OfertaSpekulant>> historiaTransakcji) {
        int n = Math.max(1, id % 17);
        int ileJedzenia = 0;
        int ileUbrań = 0;
        int ileNarzędzi = 0;
        int ileProgramów = 0;

        for (int i = dzień - n; i <= dzień - 1; i++) {
            for (int j = 0; j < historiaTransakcji.get(i).size(); j++) {
                switch (historiaTransakcji.get(i).get(j).typ()) {
                    case "Jedzenie" -> ileJedzenia +=  historiaTransakcji.get(i).get(j).sztuki();
                    case "Ubrania" -> ileUbrań +=  historiaTransakcji.get(i).get(j).sztuki();
                    case "Narzędzia" -> ileNarzędzi +=  historiaTransakcji.get(i).get(j).sztuki();
                    case "Programów" -> ileProgramów +=  historiaTransakcji.get(i).get(j).sztuki();
                };
            }
        }

        String nowyZawód = null;
        int maks = 0;

        // Diamentów nie ma w ofertach, więc nową karierą nie będzie Górnik.
        if (ileJedzenia >= maks) {
            maks = ileJedzenia;
            nowyZawód = "Rolnik";
        }

        if (ileUbrań >= maks) {
            maks = ileUbrań;
            nowyZawód = "Rzemieślnik";
        }

        if (ileNarzędzi >= maks) {
            maks = ileNarzędzi;
            nowyZawód = "Inżynier";
        }

        if (ileProgramów >= maks) {
            maks = ileProgramów;
            nowyZawód = "Programista";
        }

        assert nowyZawód != null;
        return nowyZawód;
    }

}
