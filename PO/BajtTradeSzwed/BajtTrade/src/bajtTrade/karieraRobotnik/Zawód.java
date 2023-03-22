package bajtTrade.karieraRobotnik;

public class Zawód {

    private int rolnik = 1;
    private int górnik = 1;
    private int rzemieślnik = 1;
    private int inżynier = 1;
    private int programista = 1;
    private String aktZawód;

    public String aktZawód() {
        return aktZawód;
    }

    public void aktZawód(String nowyZawód) {
        aktZawód = nowyZawód;
    }

    public int bonusProdukcji(String produkt) {
        int wynik = 0;
        if (aktZawód.equals(produkt)) {
            wynik = switch (aktPoziomKariery()) {
                case 1 -> 50;
                case 2 -> 150;
                case 3 -> 300;
                default -> 300 + (25 - aktPoziomKariery());
            };
        }

        return wynik;
    }

    public int aktPoziomKariery() {
        return switch (aktZawód) {
            case "Rolnik" -> rolnik;
            case "Górnik" -> górnik;
            case "Rzemieślnik" -> rzemieślnik;
            case "Inżynier" -> inżynier;
            case "Programista" -> programista;
            default -> throw new IllegalStateException("Unexpected value: " + aktZawód);
        };
    }

    public void rozwójKariery() {
        switch (aktZawód) {
            case "Rolnik" -> rolnik++;
            case "Górnik" -> górnik++;
            case "Rzemieślnik" -> rzemieślnik++;
            case "Inżynier" -> inżynier++;
            case "Programista" -> programista++;
            default -> System.out.println("Zły String w zmiennej aktZawód!");
        }
    }

}
