package bajtTrade.agenci;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public abstract class Kariera {

    private String typ;

    public String typ() {
        return typ;
    }

    public abstract boolean czyKupić(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano);

    public abstract boolean czySprzedać(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano);

    public abstract double zaIleKupić(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano);

    public abstract double zaIleSprzedać(int indeks, ArrayList<InfoCeny> średnieCeny, ArrayList<Integer[]> ileWyprodukowano);





}
