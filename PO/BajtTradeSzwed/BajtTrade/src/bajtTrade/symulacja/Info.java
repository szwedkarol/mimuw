package bajtTrade.symulacja;

import com.squareup.moshi.Json;

public class Info {

    @Json(name = "dlugosc")
    private int długość;
    @Json(name = "gielda")
    private String typGiełdy;
    @Json(name = "kara_za_brak_ubran")
    private int kara_za_brak_ubrań;

    private static class CenyDzieńZerowy {
        private double jedzenie;
        private double ubrania;
        @Json(name = "narzedzia")
        private double narzędzia;
        private double programy;
    }

    private CenyDzieńZerowy ceny;

    @Override
    public String toString() {
        return "długość: " + długość + "\ngiełda: " + typGiełdy;
    }

    public int długośćSymulacji() {
        return długość;
    }

    public int kara_za_brak_ubrań() {
        return kara_za_brak_ubrań;
    }

    public double[] cenyŚrednieDzieńZerowy() {
        double[] wynik = new double[4];

        wynik[0] = ceny.jedzenie;
        wynik[1] = ceny.ubrania;
        wynik[2] = ceny.narzędzia;
        wynik[3] = ceny.programy;

        return wynik;
    }

}
