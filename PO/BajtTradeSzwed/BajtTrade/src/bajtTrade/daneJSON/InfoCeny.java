package bajtTrade.daneJSON;

public class InfoCeny {

    private final double jedzenie;
    private final double ubrania;
    private final double narzedzia;
    private final double programy;

    public InfoCeny(double jedzenie, double ubrania, double narzedzia, double programy) {
        this.jedzenie = jedzenie;
        this.ubrania = ubrania;
        this.narzedzia = narzedzia;
        this.programy = programy;
    }

    public double jedzenie() {
        return jedzenie;
    }

    public double ubrania() {
        return ubrania;
    }

    public double narzedzia() {
        return narzedzia;
    }

    public double programy() {
        return programy;
    }

    public double cena(int indeks) {
        assert indeks <= 3 && indeks >= 0;
        return switch (indeks) {
            case 0 -> jedzenie;
            case 1 -> ubrania;
            case 2 -> narzedzia;
            case 3 -> programy;
            default -> -1;
        };
    }

}
