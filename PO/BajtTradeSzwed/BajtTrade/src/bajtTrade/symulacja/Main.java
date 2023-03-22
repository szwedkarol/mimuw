package bajtTrade.symulacja;

import bajtTrade.daneJSON.WczytajJSON;
import bajtTrade.daneJSON.WypiszJSON;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {

    public static void main(String[] args) throws IOException {
        assert args.length == 2;
        Symulacja symulacja = new Symulacja();
        File wejście = new File(args[0]);
        File wyjście = new File(args[1]);
        String json;

        try {
            json = new String(Files.readAllBytes(Path.of(wejście.getPath())));
        } catch (IOException ignored) {
            System.err.println("Nie udało się odczytać pliku wejściowego");
            return;
        }

        WczytajJSON.wczytajDane(json, symulacja);
        symulacja.symulacja();
        String wyjściowyJSON = WypiszJSON.wypiszDane(symulacja);

        BufferedWriter writer = new BufferedWriter(new FileWriter(wyjście));
        writer.write(wyjściowyJSON);

        writer.close();
    }

}