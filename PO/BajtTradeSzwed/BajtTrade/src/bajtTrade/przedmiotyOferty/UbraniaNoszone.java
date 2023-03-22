package bajtTrade.przedmiotyOferty;

public class UbraniaNoszone extends Produkt {

    private int wytrzymałość;

    public UbraniaNoszone(int sztuki, int poziom) {
        super(sztuki, poziom);
        wytrzymałość = poziom * poziom;
    }

    public void zmniejszWytrzymałość() {
        assert wytrzymałość > 1;
        wytrzymałość--;
    }

    public int wytrzymałość() {
        return wytrzymałość;
    }
}
