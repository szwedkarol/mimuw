package bajtTrade.agenci;

import bajtTrade.przedmiotyOferty.Zasoby;

public abstract class Agent {

    private int id;
    Zasoby zasoby;

    public int id() {
        return id;
    }

    @Override
    public String toString() {
        return "ID: " + id;
    }

    public double diamenty() {
        return zasoby.diamenty();
    }

}
