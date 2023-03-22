package bajtTrade.przedmiotyOferty;

import bajtTrade.przedmiotyOferty.Produkt;

public class OfertaRobotnik extends Produkt {

    private final int id;
    private final String typ;

    public OfertaRobotnik(int ile, int poziom, String typ, int id) {
        super(ile, poziom);
        assert typ != null;
        this.typ = typ;
        this.id = id;
    }

    public String typ() {
        return typ;
    }

    public int id() {
        return id;
    }
}
