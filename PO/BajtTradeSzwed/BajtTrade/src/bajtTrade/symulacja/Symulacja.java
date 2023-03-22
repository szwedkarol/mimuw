package bajtTrade.symulacja;

import bajtTrade.agenci.Robotnik;
import bajtTrade.agenci.Spekulant;
import bajtTrade.daneJSON.InfoCeny;
import bajtTrade.przedmiotyOferty.OfertaRobotnik;
import bajtTrade.przedmiotyOferty.OfertaSpekulant;

import java.util.ArrayList;
import java.util.List;

public class Symulacja {

    private int dzień = 0;
    private Info info;
    private Robotnik[] robotnicy;
    private Spekulant[] spekulanci;
    private transient List<ArrayList<OfertaSpekulant>> historiaTransakcji;
    private transient ArrayList<InfoCeny> średnieCeny;
    private transient ArrayList<InfoCeny> maksCeny;
    private transient ArrayList<InfoCeny> minCeny;
    private transient ArrayList<OfertaRobotnik> ofertySprzedażyRobotnicy;
    private transient ArrayList<OfertaRobotnik> ofertyKupnaRobotnicy;
    private transient ArrayList<Integer[]> ileWyprodukowano;
    private transient ArrayList<OfertaSpekulant> ofertySprzedażySpekulanci;
    private transient ArrayList<OfertaSpekulant> ofertyKupnaSpekulanci;
    private transient int[] poziom_maks; // Maksymalne poziomy produktów danego dnia.

    public void symulacja() {
        dodatkowaInicjalizacja();
        dzień = 0;
        while (dzień < info().długośćSymulacji()) {
            dzień++;

        }
    }

    private void dopasowanieOfert() {

    }

    private void sortOfertSprzedażyRobotników() {

    }

    private void sortOfertSprzedażySpekulantów() {

    }

    private void dodatkowaInicjalizacja() {
        for (Robotnik robotnik : robotnicy) {
            robotnik.dodatkowaInicjalizacja();
        }
    }

    public Info info() {
        return info;
    }

}
