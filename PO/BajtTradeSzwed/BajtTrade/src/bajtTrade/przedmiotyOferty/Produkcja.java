package bajtTrade.przedmiotyOferty;

import com.squareup.moshi.Json;

public class Produkcja {

    @Json(name = "diamenty")
    private final int prodDiamenty;
    @Json(name = "narzedzia")
    private final int prodNarzędzia;
    @Json(name = "jedzenie")
    private final int prodJedzenie;
    @Json(name = "programy")
    private final int prodProgramy;
    @Json(name = "ubrania")
    private final int prodUbrania;

    public Produkcja(int prodDiamenty, int prodNarzędzia, int prodJedzenie, int prodProgramy, int prodUbrania) {
        assert prodDiamenty % 100 == 0;
        assert prodJedzenie % 100 == 0;
        assert prodProgramy % 100 == 0;
        assert prodUbrania % 100 == 0;
        this.prodDiamenty = prodDiamenty;
        this.prodNarzędzia = prodNarzędzia;
        this.prodJedzenie = prodJedzenie;
        this.prodProgramy = prodProgramy;
        this.prodUbrania = prodUbrania;
    }

    @Override
    public String toString() {
        return "Produkcja:\n" + "Diamenty: " + prodDiamenty + "\n" +
                "Jedzenie: " + prodJedzenie + "\n" +
                "Ubrania: " + prodUbrania + "\n" +
                "Narzędzia: " + prodNarzędzia + "\n" +
                "Programy: " + prodProgramy + "\n";
    }

    public int produkcja(String typ) {
        return switch(typ) {
            case "Diamenty" -> prodDiamenty;
            case "Jedzenie" -> prodJedzenie;
            case "Ubrania" -> prodUbrania;
            case "Narzędzia" -> prodNarzędzia;
            case "Programy" -> prodProgramy;
            default -> throw new IllegalStateException("Unexpected value: " + typ);
        };
    }

}
