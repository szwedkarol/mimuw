package bajtTrade.kupowanie;

public class Gadżeciarz extends StrKupowania {

    private static int liczba_narzedzi;

    public Gadżeciarz(int liczba_narzedzi) {
        Gadżeciarz.liczba_narzedzi = liczba_narzedzi;
    }

    @Override
    public int ileKupićUbrań(int ileMaUbrań) {
        return 100 - ileMaUbrań;
    }

    @Override
    public int ileKupićNarzędzi() {
        return liczba_narzedzi;
    }

    public int ileKupićProgramów(int ileWyprodukowano) {
        return ileWyprodukowano;
    }
}
