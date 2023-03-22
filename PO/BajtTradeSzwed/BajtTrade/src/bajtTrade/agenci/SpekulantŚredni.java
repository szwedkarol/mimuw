package bajtTrade.agenci;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class SpekulantŚredni extends Kariera {

    private int historia_spekulanta_sredniego;

    @Override
    public boolean czyKupić(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        // Spekulant średni zawsze kupuje.
        return true;
    }

    @Override
    public boolean czySprzedać(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        // Spekulant średni zawsze sprzedaje.
        return true;
    }

    @Override
    public double zaIleKupić(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        return 0.9 * średnia(indeks, średnieCeny);
    }

    @Override
    public double zaIleSprzedać(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        return 1.1 * średnia(indeks, średnieCeny);
    }

    private double średnia(int indeks, ArrayList<InfoCeny> średnieCeny) {
        double wynik = 0;
        int dzień = średnieCeny.size() - 1;

        for (int i = 1; i <= historia_spekulanta_sredniego; i++ ) {
            if ( dzień - i < 0 ) {
                wynik += średnieCeny.get(0).cena(indeks);
            } else {
                wynik += średnieCeny.get(dzień - i).cena(indeks);
            }
        }

        wynik /= historia_spekulanta_sredniego;
        return wynik;
    }

}
