package bajtTrade.nauka;

import bajtTrade.daneJSON.InfoCeny;

import java.util.ArrayList;

public class Student extends StrNauki {

    private static int zapas;
    private static int okres;

    public Student(int zapas, int okres) {
        this.zapas = zapas;
        this.okres = okres;
    }

    @Override
    public boolean czySięUczy(int dzień, double ileDiamentów, ArrayList<InfoCeny> średnieCeny) {
        double średniaCenaJedzenia = 0;

        for (int i = dzień - okres; i <= dzień - 1; i++) {
            średniaCenaJedzenia += średnieCeny.get(i).jedzenie();
        }
        średniaCenaJedzenia /= okres;

        return ileDiamentów >= 100 * zapas * średniaCenaJedzenia;
    }

}
