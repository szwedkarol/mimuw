package bajtTrade.daneJSON;

import bajtTrade.agenci.*;
import bajtTrade.symulacja.Symulacja;
import bajtTrade.kupowanie.*;
import bajtTrade.nauka.*;
import bajtTrade.typProdukcji.*;
import com.squareup.moshi.JsonAdapter;
import com.squareup.moshi.Moshi;
import com.squareup.moshi.adapters.PolymorphicJsonAdapterFactory;

import java.io.IOException;

public class WczytajJSON {

    public static void wczytajDane(String wejścieJson, Symulacja s) throws IOException {
        Moshi.Builder builder = new Moshi.Builder().add(
                        PolymorphicJsonAdapterFactory.of(Kariera.class, "typ")
                                .withSubtype(SpekulantŚredni.class, "sredni")
                                .withSubtype(SpekulantWypukły.class, "wypukly")
                                .withSubtype(SpekulantRegulującyRynek.class, "regulujacy_rynek"))
                .add(PolymorphicJsonAdapterFactory.of(StrNauki.class, "typ")
                        .withSubtype(Rozkładowy.class, "rozkladowy")
                        .withSubtype(Student.class, "student")
                        .withSubtype(Okresowy.class, "okresowy")
                        .withSubtype(Pracuś.class, "pracus")
                        .withSubtype(Oszczędny.class, "oszczedny"))
                .add(PolymorphicJsonAdapterFactory.of(StrProd.class, "typ")
                        .withSubtype(Chciwy.class, "chciwy")
                        .withSubtype(Krótkowzroczny.class, "krotkowzroczny")
                        .withSubtype(Losowy.class, "losowy")
                        .withSubtype(Perspektywiczny.class, "Perspektywiczny")
                        .withSubtype(Średniak.class, "sredniak"))
                .add(PolymorphicJsonAdapterFactory.of(StrKupowania.class, "typ")
                        .withSubtype(Czyścioszek.class, "czyscioszek")
                        .withSubtype(Gadżeciarz.class, "gadzeciarz")
                        .withSubtype(Technofob.class, "technofob")
                        .withSubtype(Zmechanizowany.class, "zmechanizowany"));

        Moshi moshi = builder.build();

        JsonAdapter<Symulacja> jsonAdapter = moshi.adapter(Symulacja.class);
        s = jsonAdapter.fromJson(wejścieJson);
        assert s != null;
    }

}
