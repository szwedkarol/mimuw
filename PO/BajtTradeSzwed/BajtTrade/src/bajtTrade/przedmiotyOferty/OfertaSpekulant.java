package bajtTrade.przedmiotyOferty;

import bajtTrade.przedmiotyOferty.OfertaRobotnik;

public class OfertaSpekulant extends OfertaRobotnik {

    private final double cena;

    public OfertaSpekulant(int ile, int poziom, String typ, int id, double cena) {
        super(ile, poziom, typ, id);
        assert typ != null;
        this.cena = cena;
    }

    public double cena() {
        return cena;
    }
}
