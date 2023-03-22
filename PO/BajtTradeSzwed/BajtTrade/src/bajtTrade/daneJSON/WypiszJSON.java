package bajtTrade.daneJSON;

import bajtTrade.agenci.*;
import bajtTrade.symulacja.Symulacja;
import bajtTrade.kupowanie.*;
import bajtTrade.nauka.*;
import bajtTrade.typProdukcji.*;
import com.squareup.moshi.JsonAdapter;
import com.squareup.moshi.Moshi;
import com.squareup.moshi.adapters.PolymorphicJsonAdapterFactory;

public class WypiszJSON {

    public static String wypiszDane(Symulacja s) {
        Moshi.Builder builder = new Moshi.Builder();
        builder.add(PolymorphicJsonAdapterFactory.of(StrNauki.class, "typ")
                        .withSubtype(Rozkładowy.class, "rozkladowy")
                        .withSubtype(Student.class, "student")
                        .withSubtype(Okresowy.class, "okresowy")
                        .withSubtype(Oszczędny.class, "oszczedny")
                        .withSubtype(Pracuś.class, "pracus"))
                .add(PolymorphicJsonAdapterFactory.of(StrProd.class, "typ")
                        .withSubtype(Chciwy.class, "chciwy")
                        .withSubtype(Krótkowzroczny.class, "krotkowzroczny")
                        .withSubtype(Losowy.class, "losowy")
                        .withSubtype(Perspektywiczny.class, "perspektywiczny")
                        .withSubtype(Średniak.class, "sredniak"))
                .add(PolymorphicJsonAdapterFactory.of(StrKupowania.class, "typ")
                        .withSubtype(Czyścioszek.class, "czyscioszek")
                        .withSubtype(Gadżeciarz.class, "gadzeciarz")
                        .withSubtype(Technofob.class, "technofob")
                        .withSubtype(Zmechanizowany.class, "zmechanizowany"))
                .add(PolymorphicJsonAdapterFactory.of(Kariera.class, "typ")
                        .withSubtype(SpekulantRegulującyRynek.class, "regulujacy_rynek")
                        .withSubtype(SpekulantŚredni.class, "sredni")
                        .withSubtype(SpekulantWypukły.class, "wypukly"));
        Moshi moshi = builder.build();

        JsonAdapter<SymulacjaJSON> jsonAdapter = moshi.adapter(SymulacjaJSON.class).indent("   ");

        return jsonAdapter.toJson(new SymulacjaJSON(s));
    }
}
