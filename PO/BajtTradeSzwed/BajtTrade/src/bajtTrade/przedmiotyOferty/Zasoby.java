package bajtTrade.przedmiotyOferty;

import bajtTrade.przedmiotyOferty.Produkt;

import java.util.ArrayList;

public class Zasoby {

    private double diamenty;
    private Produkt jedzenie;
    private ArrayList<Produkt> ubrania;
    private ArrayList<Produkt> narzędzia;
    private ArrayList<Produkt> programy;

    public Zasoby(double diamenty, Produkt jedzenie, ArrayList<Produkt> ubrania,
                  ArrayList<Produkt> narzędzia, ArrayList<Produkt> programy) {
        this.diamenty = diamenty;
        this.jedzenie = jedzenie;
        this.ubrania = ubrania;
        this.narzędzia = narzędzia;
        this.programy = programy;
    }

    public int ubraniaRozmiar() {
        return ubrania.size();
    }

    public int narzędziaRozmiar() {
        return narzędzia.size();
    }

    public int programyRozmiar() {
        return programy.size();
    }

    public Produkt ubranie(int i) {
        assert i <= ubrania.size();
        return ubrania.get(i);
    }

    public Produkt program(int i) {
        assert i <= programy.size();
        return programy.get(i);
    }

    public Produkt narzędzie(int i) {
        assert i <= narzędzia.size();
        return narzędzia.get(i);
    }

    public double diamenty() {
        return diamenty;
    }

    public int jedzenie() {
        return jedzenie.sztuki();
    }

    public void dodajDiamenty(double diamenty) {
        this.diamenty += diamenty;
    }

    public void odejmijDiamenty(double diamenty) {
        this.diamenty -= diamenty;
    }

    public void dodajJedzenie(Produkt jedzenie) {
        assert jedzenie.sztuki() >= 0;
        this.jedzenie.dodajSztuki(jedzenie.sztuki());
    }

    public void odejmijJedzenie(int ile) {
        assert ile >= 0;
        this.jedzenie.odejmijSztuki(ile);
    }

    public void dodajUbranie(int ile, int poziom) {
        dodajZasób(ile, poziom, ubrania);
    }

    public void dodajNarzędzia(int ile, int poziom) {
        dodajZasób(ile, poziom, narzędzia);
    }

    public void dodajProgramy(int ile, int poziom) {
        dodajZasób(ile, poziom, programy);
    }

    public void odejmijUbrania(int ile, int poziom) {
        odejmijZasób(ile, poziom, ubrania);
    }

    public void odejmijNarzędzia(int ile, int poziom) {
        odejmijZasób(ile, poziom, narzędzia);
    }

    public void odejmijProgramy(int ile, int poziom) {
        odejmijZasób(ile, poziom, programy);
    }

    private void dodajZasób(int ile, int poziom, ArrayList<Produkt> zasób) {
        assert ile >= 0;
        assert poziom >= 1;

        int i = 0;

        while ( poziom > zasób.get(i).poziom() && i < zasób.size() ) {
            i++;
        }

        if (i == zasób.size()) {
            zasób.add(new Produkt(ile, poziom));
        } else if (poziom == zasób.get(i).poziom()){
            zasób.get(i).dodajSztuki(ile);
        } else {
            zasób.add(i, new Produkt(ile, poziom));
        }
    }

    private void odejmijZasób(int ile, int poziom, ArrayList<Produkt> zasób) {
        assert ile >= 0;
        assert poziom >= 1;

        int i = 0;

        while ( poziom > zasób.get(i).poziom() && i < zasób.size() ) {
            i++;
        }

        // Możemy odjąć tylko te zasoby, które posiadamy
        assert i != zasób.size() && poziom == zasób.get(i).poziom();
        assert ile <= zasób.get(i).sztuki();

        if (ile == zasób.get(i).sztuki()) {
            // Już nie posiadamy żadnej sztuki zasobu danego poziomu
            zasób.remove(i);
        } else {
            zasób.get(i).odejmijSztuki(ile);
        }
    }

    public int sumaPoziomówNarzędzi() {
        int wynik = 0;

        for (Produkt produkt : narzędzia) {
            wynik += produkt.poziom() * produkt.sztuki();
        }

        return wynik;
    }

    public void wyzerujNarzędzia() {
        narzędzia = new ArrayList<Produkt>();
    }

}
