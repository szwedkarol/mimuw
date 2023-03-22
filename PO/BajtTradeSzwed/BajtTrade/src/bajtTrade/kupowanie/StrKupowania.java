package bajtTrade.kupowanie;

public abstract class StrKupowania {

    public int ileKupićJedzenia()
    {
        return 100;
    }

    public int ileKupićUbrań(int ileMaUbrań) {
        return 100 - ileMaUbrań;
    }

    public abstract int ileKupićNarzędzi();

    public int ileKupićProgramów(int ileWyprodukowano) {
        return 0;
    }

}
