package bajtTrade.kupowanie;

public class Zmechanizowany extends StrKupowania {

    private static int liczba_narzedzi;

    public Zmechanizowany(int liczba_narzedzi) {
        Zmechanizowany.liczba_narzedzi = liczba_narzedzi;
    }

    @Override
    public int ileKupićUbrań(int ileMaUbrań) {
        return 100 - ileMaUbrań;
    }

    @Override
    public int ileKupićNarzędzi() {
        return liczba_narzedzi;
    }

}
