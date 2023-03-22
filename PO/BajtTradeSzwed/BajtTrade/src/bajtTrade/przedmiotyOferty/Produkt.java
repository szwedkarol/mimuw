package bajtTrade.przedmiotyOferty;


/*
 * Klasa opisująca produkty z poziomem jakości (ubrania, narzędzia, programy).
 * Ubrania noszone przez robotnika stanowią oddzielny obiekt od np. ubrań przez
 * niego wyprodukowanych danego dnia lub ubrań posiadanych przez Spekulanta.
 * Jedzenie i diamenty, jako przedmioty bez poziomu, są zawsze typu prostego
 * (odpowiednio int oraz double).
 */
public class Produkt {

    private int sztuki;
    private final int poziom;

    public Produkt(int sztuki, int poziom) {
        assert poziom >= 1;
        assert sztuki >= 1;
        this.sztuki = sztuki;
        this.poziom = poziom;
    }

    public int sztuki() {
        return sztuki;
    }

    public int poziom() {
        return poziom;
    }

    public void dodajSztuki(int sztuki) {
        this.sztuki += sztuki;
    }

    public void odejmijSztuki(int sztuki) {
        this.sztuki -= sztuki;
    }

}
