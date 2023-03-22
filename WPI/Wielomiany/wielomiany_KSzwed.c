/*
Karol Szwed
16.11.2021 r.
Projekt zaliczeniowy nr 1 - Wielomiany
Kalkulator liczacy sume i iloczyn wielomianow o wspolczynnikach calkowitych
*/
#include <stdio.h>
#include <stdlib.h>

#define maks_st 11 //liczba stopni wielomianu (od 0 do 10)
#define maks_dl 1000 //maksymalna dlugosc wiersza danych

void wypisz_akumulator( int akumulator[] );
void zeruj( int tab[], int n );
void wczytaj_dane( int wielomian[] );
void dodawanie( int akumulator[], int wielomian[] );
void mnozenie( int akumulator[], int wielomian[] );

//wypisuje zawartosc akumulatora na wyjscie standardowe
void wypisz_akumulator( int akumulator[] )
{
    //Najpierw sprawdzamy, czy w akumulatorze jest wielomian zerowy
    int zero = 1;//0, jesli nie jest zerowy, 1 - wielomian jest zerowy
    for( int i = 0; i < maks_st; i++ )
    {
        if( akumulator[i] != 0 )//wystarczy 1 wspolczynnik rozny od 0, aby wielomian nie byl zerowy
        {
            zero = 0;
        }
    }

    //jesli zero != 0, to w akumulatorze jest wielomian zerowy
    if( zero )
    {
        printf("0");
    }
    else
    {
        int pierwszy = 1;//1, jesli jeszcze nie zostal wypisany pierwszy jednomian
        for( int i = maks_st-1; i >= 0; i-- )
        {
            if( pierwszy && akumulator[i] != 0 )
            {
                pierwszy = 0;
                if( akumulator[i] < 0 )
                {
                    printf( "-" );//znak '-' bez spacji znajduje sie tylko na poczatku
                }
            }
            else
            {
                if( akumulator[i] < 0 )
                {
                    printf( " - " );
                }
                else if( akumulator[i] > 0 )
                {
                    printf( " + " );
                }
            }

            if( akumulator[i] != 0 )
            {
                if( akumulator[i] != 1 && akumulator[i] != -1 )//wypisujemy tylko wspolczynniki rozne od 1 i -1, jesli na prawo jest zmienna x
                {
                    printf("%d", abs(akumulator[i]) );//abs(), bo znak wspolczynnika wypisujemy wczesniej
                }
                else if( i == 0 )//wolny wyraz (brak na prawo zmiennej x) wypisujemy zawsze, kiedy jest rozny od 0
                {
                    printf("%d", abs(akumulator[i]) );//abs(), bo znak wspolczynnika wypisujemy wczesniej
                }

                if( i > 0 )
                {
                    printf("x");
                    if( i > 1 )//wypisujemy tylko wykladniki wieksze od 1
                    {
                        printf( "^%d", i );
                    }
                }
            }
        }//end for
    }

    printf("\n");//ostatni znak po każdym wierszu danych wyjściowych
}

//ustawia wartosci na zero w tablicy
void zeruj( int tab[], int n )
{
    for( int i = 0; i < n; i++ )
    {
        tab[i] = 0;
    }
}

//wczytuje aktualny wiersz danych (okreslenie wspolczynnikow przy jednomianach danego stopnia)
//tj. wypelnia tablice wielomian[] wartosciami wspolczynnikow (wielomian[i] zawiera wspol. przy x^i)
void wczytaj_dane( int wielomian[] )
{
    int wielomian_tekst[maks_dl];//wielomian z obecnego wiersza danych w formie tekstowej
    //(dokladnie wartosci calkowite ASCII poszczegolnych znakow)

    //najpierw wczytujemy wiersz danych jako tekst (bez spacji) do wielomian_tekst[]
    int i = 0;//dlugosc tekstowego zapisu wielomianu bez spacji
    int c;
    c = getchar();
    while( c != '\n' && i < maks_dl )
    {
        //pomijamy spacje
        if( c != ' ' )
        {
            wielomian_tekst[i] = c;
            i++;
        }

        c = getchar();
    }

    //zamieniamy tekst na wspolczynniki przy odpowiednich potegach zmiennej x
    int j = 0;
    while( j < i )
    {
        int mnoznik = 1;//mnozy wczytywany wspolczynnik przez 1 lub -1 jesli jest odp. dodatni/ujemny
        int wspolczynnik = 1;//wartosc bezwzgledna wspolczynnika calkowitego przy parsowanym aktualnie jednomianie
        int stopien = 0;//stopien parsowanego aktualnie jednomianu

        if( wielomian_tekst[j] == '-' )
        {
            //dany wspolczynnik jest ujemny
            mnoznik = -1;
            j++;
        }
        else if ( wielomian_tekst[j] == '+' )
        {
            //mnoznika w tym wypadku nie zmieniamy
            j++;
        }

        if( wielomian_tekst[j] >= '0' && wielomian_tekst[j] <= '9' )//wspolczynnik moze byc rozny od 1
        {
            wspolczynnik = 0;//od nowa liczymy wspolczynnik
            while( wielomian_tekst[j] >= '0' && wielomian_tekst[j] <= '9' && j < i )
            {
                wspolczynnik *= 10;
                wspolczynnik += wielomian_tekst[j] - '0';
                j++;
            }
        }

        //okreslenie stopnia jednomianu
        if( wielomian_tekst[j] == 'x' )
        {
            j++;
            if( wielomian_tekst[j] == '^' )
            {
                j++;
                while( wielomian_tekst[j] >= '0' && wielomian_tekst[j] <= '9' && j < i )
                {
                    stopien *= 10;
                    stopien += wielomian_tekst[j] - '0';
                    j++;
                }
            }
            else
            {
                stopien = 1;//brak '^' przy x, wiec jest to jednomian st. 1
            }
        }

        wielomian[stopien] = wspolczynnik * mnoznik;
    }
}

//kiedy wiersz zaczyna sie od '+', wykonujemy dodawanie wielomianow
void dodawanie( int akumulator[], int wielomian[] )
{
    zeruj( wielomian, maks_st );
    wczytaj_dane( wielomian );

    for( int i = 0; i < maks_st; i++ )
    {
        akumulator[i] += wielomian[i];
    }
}

//kiedy wiersz zaczyna sie od '*', wykonujemy mnozenie wielomianow
void mnozenie( int akumulator[], int wielomian[] )
{
    zeruj( wielomian, maks_st );
    wczytaj_dane( wielomian );

    int wyniki_mnozenia[maks_st];
    //przechowuje wyniki mnozenia wspolczynnikow wielomianu w akumulatorze przez
    //wspol. wielomianu z obecnego wiersza danych
    zeruj( wyniki_mnozenia, maks_st );

    for( int i = 0; i < maks_st; i++ )
    {
        for( int j = 0; i + j < maks_st; j++ )
        {
            wyniki_mnozenia[i+j] += akumulator[i] * wielomian[j];//kx^a * tx^b = (k*t)x^(a+b)
        }
    }

    for( int i = 0; i < maks_st; i++ )
    {
        akumulator[i] = wyniki_mnozenia[i];
    }
}

int main(void)
{
    int akumulator[maks_st];//wspolczynniki wielomianu bedacego w akumulatorze
    //akumulator[i] zawiera wspolczynnik stojacy przy x^i
    int wielomian[maks_st];//wspolczynniki wielomianu z obecnego wiersza danych

    //akumulator na poczatku zawiera wielomian zerowy
    zeruj( akumulator, maks_st );
    //przed wczytaniem 1. wiersza danych wielomian[] zawiera wielomian zerowy
    zeruj( wielomian, maks_st );

    int c = getchar();
    while( c != EOF && c != '.' )
    {
        if( c == '*' )
        {
            mnozenie( akumulator, wielomian );
            wypisz_akumulator( akumulator );
        }
        else if( c == '+' )
        {
            dodawanie( akumulator, wielomian );
            wypisz_akumulator( akumulator );
        }
        c = getchar();
    }

    return 0;
}
