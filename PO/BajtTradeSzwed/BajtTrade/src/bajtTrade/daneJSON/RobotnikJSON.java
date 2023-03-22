package bajtTrade.daneJSON;

import bajtTrade.agenci.Robotnik;
import bajtTrade.karieraRobotnik.Zawód;
import bajtTrade.kupowanie.StrKupowania;
import bajtTrade.nauka.StrNauki;
import bajtTrade.przedmiotyOferty.Produkcja;
import bajtTrade.typProdukcji.StrProd;

public class RobotnikJSON {
    private int id;
    private int poziom;
    private Zawód zawód;
    private StrKupowania kupowanie;
    private StrProd produkcja;
    private StrNauki uczenie;
    private String zmiana;
    private Produkcja produktywnosc;
    private ZasobyJSON zasoby;

    public RobotnikJSON(Robotnik robotnik) {
        // Tworzenie kopii robotnika do wypisania w pliku JSON
    }
}
