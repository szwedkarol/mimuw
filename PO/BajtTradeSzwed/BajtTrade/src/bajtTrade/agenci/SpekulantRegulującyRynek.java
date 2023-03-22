package bajtTrade.agenci;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class SpekulantRegulującyRynek extends Kariera {

    @Override
    public boolean czyKupić(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        // Ten Spekulant kupuje tylko 2 i każdego następnego dnia
        return średnieCeny.size() > 2;
    }

    @Override
    public boolean czySprzedać(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        // Ten Spekulant sprzedaje tylko 2 i każdego następnego dnia
        return średnieCeny.size() > 2;
    }

    @Override
    public double zaIleKupić(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        return 0.9 * cenaWyregulowana(indeks, średnieCeny, ileWyprodukowano);
    }

    @Override
    public double zaIleSprzedać(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        return 1.1 * cenaWyregulowana(indeks, średnieCeny, ileWyprodukowano);
    }

    private double cenaWyregulowana(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano) {
        int dzień = średnieCeny.size() - 1;
        double cena_wczoraj = średnieCeny.get(dzień - 1).cena(indeks);
        double produkcja_dziś =  ileWyprodukowano.get(dzień)[indeks];
        double dzielnik = Math.max(1, ileWyprodukowano.get(dzień - 1)[indeks]);

        return cena_wczoraj * produkcja_dziś / dzielnik;
    }


}
