/**************************************************************************************************
	Karol Szwed
	25.01.2022 r.
	Projekt zaliczeniowy nr 4 - Osiągalne
	Program czyta opis grafu skierowanego w podzbiorze języka DOT i pisze liczbę węzłów osiągalnych z
	węzła o nazwie "start".

	Wejście:
	Opis w podzbiorze języka DOT pojedynczego niepustego grafu skierowanego (co najmniej jeden
	węzeł o nazwie "start").

	Wyjście:
	Pojedyncza liczba całkowita oznaczająca liczbę węzłów osiągalnych z węzła o nazwie "start".
**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// POCZĄTEK DEKLARACJI STRUKTUR DANYCH

/**
    Struktura danych rekordów będących częścią głównej listy opisującej graf.
	Do każdego rekordu podpięta jest (pusta lub niepusta) lista siąsiedztwa danego węzła.
*/
typedef struct Wezel Wezel;

/**
    Rekordy to kolejne węzły stanowiące końce krawędzi wychodzących z węzła wskazującego na daną
	listę sąsiedztwa.
*/
typedef struct Lista Lista;

/**
    Stos zaimplementowany listowo (lista jednokierunkowa, niecykliczna).
*/
typedef struct Stack Stack;

// KONIEC DEKLARACJI STRUKTUR DANYCH

// POCZĄTEK DEFINICJI STRUKTUR DANYCH

/**
    Przechowuje rekordy o węzłach grafu
*/
typedef struct Wezel
{
	Wezel * nast; // kolejny węzeł grafu na liście list sąsiedztwa
	Lista * l_sasiadow; // wskaźnik na listę sąsiedztwa danego węzła
	char * nazwa; // ID/nazwa węzła
	bool odwiedzone; // przy DFS określa, czy już przetwarzaliśmy dany wierzchołek
} Wezel;

/**
    Rekordy z węzłami z listy sąsiedztwa danego węzła.
*/
typedef struct Lista
{
	// kolejny końcowy węzeł krawędzi wychodzącej z węzła, do którego podpięta jest ta lista
	Lista * nast_ls; // następny węzeł - koniec krawędzi wychodzącej z węzła wsk. na daną listę
	Wezel * odp_wezel; // wskaźnik na rekord z węzłem z głównej listy grafu typu 'Wezel'
} Lista;

/**
    Kolejne rekordy to węzły trafiające na stos (=do magazynu) w trakcie DFS
*/
typedef struct Stack
{
	Stack * nast;
	Wezel * wierzcholek;
} Stack;

// KONIEC DEFINICJI STRUKTUR DANYCH

// POCZĄTEK DEKLARACJI FUNKCJI

/**
    IN: '**S' - Adres wskaźnika na niepusty stos wykorzystywany przy DFS
	FUN: Zdejmuje element z góry stosu, zwalniająć pamięć zaalokowaną do umieszczenia go na stosie
	OUT: Wskaźnik na rekord typu 'Wezel', który znajdował się na szczycie stosu.
*/
Wezel * Pop( Stack **S );

/**
    IN: '**S' - adres wskaźnika na (pusty lub niepusty) stos wykorzystywany przy DFS;
	'wezel' - wskaźnik (nie NULL) na rekord typu 'Wezel', będący jednym z węzłów grafu
	FUN: Umieszcza węzeł '*wezel' na górze stosu, alokując dla niego pamię (którą później czyścimy
	w trakcie DFS poprzez zdejmowanie wszystkich elementów ze stosu)
	OUT: Brak.
*/
void Push( Stack ** S, Wezel * wezel );

/**
    IN: Adres wskaźnika (NULL lub nie) na zmienną typu 'Stack', która ma stanowić nasz stos
	FUN: Inicjalizuje pusty stos, poprzez ustawienie wskaźnika '*S' na NULL
	OUT: Brak.
*/
void Init( Stack ** S );

/**
    IN: Wskaźnik na zmienną typu 'Stack' (NULL lub nie)
	FUN: Sprawdza, czy stos jest pusty.
	OUT: Wartość logiczna - true, jeśli stos jest pusty, false w p. p.
*/
bool Pusty( Stack * S );

/**
    IN: Brak.
    FUN: Przechodzi przez wszystkie białe znaki na wejściu pomiędzy dwoma niebędącymi białym
	znakiem (co pozwala nam je pominąć).
	OUT: Brak.
*/
void pomin_biale_znaki();

/**
    IN: Wskaźnik (nie NULL) na węzeł, który ma być końcem krawędzi.
	FUN: Dodaje na końcu listy sąsiedztwa rekord z wierzchołkiem będącym końcem krawędzi.
	Po zakończeniu korzystania z reprezentacji grafu, należy usunąć całą listę sąsiedztwa danego
	wierzchołka, gdyż każdy z nich ma dynamicznie alokowaną pamięć przy umieszczaniu na liście.
	OUT: Wskaźnik na koniec krawędzi umieszczony na liście sąsiedztwa.
*/
Lista * dodaj_krawedz( Wezel * wezel_kon );

/**
    IN: Wskaźnik na (pusty lub nie) graf reprezentowany za pomocą list sąsiedztwa.
	FUN: Czyści całą zaalokowaną pamięć w trakcie procesu tworzenia reprezentacji grafu
	(w tym nazwy, rekordy na głównej liście grafu, listy sąsiedztwa danego rekordu).
	OUT: Brak.
*/
void destruktor( Wezel * graf );

/**
    IN:
	FUN:
	OUT:
*/
Wezel * czy_istnieje_wezel( Wezel * graf, char * nazwa );

/**
    TODO: Komentarz 
*/
void wczytaj_nazwe_wezla( char ** nazwa );

/**
    TODO: Komentarz
*/
void dodaj_wezel( Wezel ** graf, Wezel ** wezel );

/**
    IN: Dwa (nie NULL) wskaźniki na początek i koniec krawędzi (odp. 'pocz' i 'kon').
	FUN: 
	OUT: Wartość logiczna - true, jeśli dana krawędź istnieje, false w p. p.
*/
bool czy_istnieje_krawedz( Wezel * pocz, Wezel * kon );

// KONIEC DEKLARACJI FUNKCJI

/**
    Usuwa 1. element na stosie '*S' i przekazuje adres do węzła, na jaki wskazywał
*/
Wezel * Pop( Stack **S )
{
	Stack * pom = *S;
	Wezel * top = (*S)->wierzcholek;

	*S = (*S)->nast;
	free( pom );

	return top;
}

/**
    Umieszcza na górze stosu rekord ze wskaźnikiem na przekazany na wejściu węzeł
*/
void Push( Stack ** S, Wezel * wezel )
{
	Stack * pom;

	pom = malloc( sizeof( Stack ) );
	pom->nast = *S;
	pom->wierzcholek = wezel;
	*S = pom;
}

/**
    Inicjalizuje pusty stos, który będziemy wykorzystywali do DFS
*/
void Init( Stack ** S )
{
	*S = NULL;
}

/**
    Sprawdza, czy stos dany na wejście przez wskaźnik jest pusty
*/
bool Pusty( Stack * S )
{
	return ( S == NULL );
}

/**
    Przechodzi przez białe znaki na wejściu, efektywnie pomijając je.
*/
void pomin_biale_znaki()
{
	char c;

	do
	{
		c = (char) getchar();
	}while ( isspace(c) );
	ungetc(c, stdin); // ostatni wczytany znak jest nie-biały, więc go oddajemy na wejście
}

/**
    Wczytuje z stdin nazwę węzła - modyfikuje pusty napis przekazany przez podwójny wskaźnik
*/
void wczytaj_nazwe_wezla( char ** nazwa )
{
	int rozmiar_alokacji = 2;
	*nazwa = malloc( rozmiar_alokacji * sizeof(char) ); // wskaźnik 'nazwa' początkowo na nic nie pokazuje
	char c = (char) getchar();
	int k = 0; // indeks wewnętrzny napisu 'nazwa'

	(*nazwa)[0] = c;
	(*nazwa)[1] = '\0';
	do
	{
		// Za mała ilość pamięci przeznaczona na nazwę, więc podwajamy pamięć
		if ( k == (int)( strlen( *nazwa ) ) )
		{
			*nazwa = realloc( *nazwa, ( 2 * strlen( *nazwa ) + 1 ) * sizeof(char) );
		}

		(*nazwa)[k] = c;
		c = (char) getchar();
		k++;
	}while ( isalnum(c) );
	ungetc( c, stdin ); // zwracamy na wejście zmienną 'c', gdyż nie jest to część nazwy węzła

	*nazwa = realloc( *nazwa, ( strlen( *nazwa ) + 1 ) * sizeof(char) );
	if ( k == (int)(strlen( *nazwa ) ) ) // musimy mieć miejsce na umieszczenie '\0' na końcu napisu
	{
		*nazwa = realloc( *nazwa, ( strlen( *nazwa ) + 1 ) * sizeof(char) );
	}
	k++;
	(*nazwa)[k] = '\0'; // wstawiamy '\0' na koniec nazwy węzła
}

/**
    Dodaje nowy węzeł na początku listy opisującej graf
*/
void dodaj_wezel( Wezel ** graf, Wezel ** wezel )
{
	*wezel = malloc( sizeof( Wezel ) );

	if ( *graf == NULL )
	{
		*graf = *wezel;
		(*wezel)->nast = NULL;
	}
	else
	{
		(*wezel)->nast = (*graf)->nast;
		(*graf)->nast = *wezel;
	}
}

/**
    Sprawdza, czy został już dodany do listy '*graf' wezęł o nazwie '*nazwa' - jeśli tak, to zwraca
	jego adres; jeśli nie, to zwraca NULL
*/
Wezel * czy_istnieje_wezel( Wezel * graf, char * nazwa )
{
	Wezel * akt = graf; // wskaźnik do przechodzenia przez listę '*graf'
	Wezel * wynik = NULL;

	while ( akt != NULL )
	{
		if ( !strcmp( akt->nazwa, nazwa ) )
		{
			wynik = akt; // znaleźliśmy wezęł o spr. nazwie, więc już został przedtem dodany
		}

		akt = akt->nast;
	}

	return wynik;
}

/**
    Dodaje do listy sąsiedztwa koniec krawędzi przekazanej jako argument.
*/
Lista * dodaj_krawedz( Wezel * wezel_kon )
{
	Lista * akt = malloc( sizeof( Lista ) );
	akt->odp_wezel = wezel_kon;
	akt->nast_ls = NULL;

	return akt;
}

/**
    Sprawdza, czy istnieje krawędź od wierzchołaka '*pocz' do wierzchołka '*kon'.
*/
bool czy_istnieje_krawedz( Wezel * pocz, Wezel * kon )
{
	bool jest = false;
	Lista * akt = pocz->l_sasiadow;

	while ( akt != NULL && !jest )
	{
		if ( akt->odp_wezel == kon )
		{
			jest = true;
		}

		akt = akt->nast_ls;
	}

	return jest;
}

/**
    Usuwa całą zaalokowaną pamięć, przechodząc przez listę 'graf' (i odpowiednie podlisty)
*/
void destruktor( Wezel * graf )
{
	// Nie usuwamy niczego, jeśli nasz graf 'graf' jest pusty
	if ( graf != NULL )
	{
		Wezel * akt = graf; // wskazuje na węzeł, który będziemy usuwali
		Wezel * po_akt = graf->nast; // wskazuje na następny po 'akt' węzeł

		do
		{
			// Usuwanie listy sąsiedztwa danego węzła
			if ( akt->l_sasiadow != NULL )
			{
				Lista * akt_lista_sasiedztwa = akt->l_sasiadow;
				Lista * po_akt_lista_sasiedztwa = akt->l_sasiadow->nast_ls;

				while ( akt_lista_sasiedztwa != NULL )
				{
					free( akt_lista_sasiedztwa );
					akt_lista_sasiedztwa = po_akt_lista_sasiedztwa;
					if ( po_akt_lista_sasiedztwa != NULL )
					{
						po_akt_lista_sasiedztwa = po_akt_lista_sasiedztwa->nast_ls;
					}
				}
			}
			
			free( akt->nazwa ); // ID węzłów były dynamicznie alokowane, więc je też czyścimy
			free(akt);
			akt = po_akt;
			po_akt = po_akt->nast;
		}while ( po_akt != NULL );
		free( akt ); // ostatni raz usuwamy pamięć zaalokowaną na węzeł grafu
	}
}

/**
    Zwraca liczbę wierzchołków będących częścią grafu 'graf', jakie są osiągalne z wierzchołka
	o nazwie 'start'. Funkcja oblicza wynik za pomocą algorytmu DFS.
*/
int zliczanie_DFS( Wezel * graf )
{
	int wynik = 0; // liczba węzłów osiągalna od węzła "start"
	Stack * Stos; // stos wykorzystywany przy DFS
	Init( &Stos ); // inicjalizujemy stos, który wykorzystamy do DFS

	/*
	Inicjalizujemy strukturę danych - wszystkie wierzchołki oznaczamy jako nieodwiedzone,
	poza wierzchołkiem o nazwie "start" - od niego zaczynamy DFS, więc jest od razu odwiedzony
	*/
	Wezel * przed_akt = graf;
	przed_akt->odwiedzone = false;

	if ( graf->nast != NULL )
	{
		Wezel * akt = graf->nast;
		while ( akt != NULL )
		{
			akt->odwiedzone = false;
			if ( !strcmp( akt->nazwa, "start" ) )
			{
				akt->odwiedzone = true;
				Push( &Stos, akt ); // umieszczamy 'start' na stosie
			}

			przed_akt = akt;
			akt = akt->nast;
		}
	}

	// Przechodzimy przez graf za pomocą DFS
	Wezel * akt; // aktualnie przetwarzany przez DFS wierzchołek
	while ( !Pusty( Stos ) )
	{
		akt = Pop( &Stos );
		wynik++; // zwiększamy wynik o 1 po zdjęciu węzła ze stosu - jest osiągalny ze "start"
		Lista * l_koncow = akt->l_sasiadow;

		while ( l_koncow != NULL )
		{
			if ( l_koncow->odp_wezel->odwiedzone == false )
			{
				l_koncow->odp_wezel->odwiedzone = true;
				Push( &Stos, l_koncow->odp_wezel );
			}

			l_koncow = l_koncow->nast_ls;
		}
	}

	return wynik;
}

/**
  IN: Wejście standardowe, w nim opis pojedynczego grafu skierowanego za pomocą podzbioru
  języka DOT.
  FUN: Tworzy reprezentację grafu za pomocą list sąsiedztwa oraz oblicza wynik działania programu
  OUT: Wypisuje na wyjście std. jedną liczbę całkowitą będącą liczbą węzłów osiągalnych z węzła
  o nazwie "start"  
*/
int main( void )
{
	int wynik = 1; // liczba węzłów osiągalna od węzła "start" - zawsze co najmniej 1
	Wezel * graf = NULL; // reprezentacja grafu jako list sąsiedztwa
	char znak;
	char * nazwa = NULL; // przechowuje nazwę obecnie przetwarzanego wierzchołka
	Wezel * wezel_pocz = NULL; // wsk. na rekord węzła będącego początkiem przetwarzanej krawędzi
	Wezel * wezel_kon = NULL; // wsk. na rekord węzła będącego końcem przetwarzanej krawędzi

	pomin_biale_znaki(); // pomijamy białe znaki przed wyrażeniem "digraph"

	// Pomijamy wyrażenie "digraph"
	for ( unsigned int i = 0; i < strlen( "digraph" ); i++ )
	{
		getchar();
	}

	pomin_biale_znaki(); // pomijamy białe znaki przed '{'
	getchar(); // pomijamy '{'
	pomin_biale_znaki(); // pomijamy białe znaki przed 1. nazwą węzła

	// Tworzymy reprezentację grafu danego na wejściu za pomocą list sąsiedztwa
	znak = (char) getchar();
	while ( znak != '}' )
	{
		ungetc( znak, stdin ); // pobrany znak był różny od '}', więc "oddajemy" na wejście

		// Wczytujemy nazwę węzła będącego początkiem przetwarzanej krawędzi
		wczytaj_nazwe_wezla( &nazwa );

		wezel_pocz = czy_istnieje_wezel( graf, nazwa );
		if ( wezel_pocz == NULL ) // dodajemy wierzchołek, bo nie ma go na głównej liście grafu
		{
			dodaj_wezel( &graf, &wezel_pocz );
			wezel_pocz->l_sasiadow = NULL;
		}

		wezel_pocz->nazwa = nazwa;

		pomin_biale_znaki(); // pomijamy białe znaki między początkiem krawędzi a "->"
		getchar();
		getchar(); // pomijamy strzałkę - "->"
		pomin_biale_znaki(); // pomijamy białe znaki między "->" a końcem krawędzi

		// Wczytujemy nazwę węzła będącego końcem przetwarzanej krawędzi
		wczytaj_nazwe_wezla( &nazwa );

		/* 
		Jeśli koniec i początek krawędzi to ten sam wierzchołek (== mają te same nazwy), to ta
		krawędź nie wpływa na ostateczny wynik działania programu (liczbę wierzchołków osiągalnych
		ze startu).
		*/
		if ( strcmp( nazwa, wezel_pocz->nazwa ) )
		{
			wezel_kon = czy_istnieje_wezel( graf, nazwa );
			if ( wezel_kon == NULL ) // dodajemy wierzchołek, bo nie ma go na głównej liście grafu
			{
				dodaj_wezel( &graf, &wezel_kon );
				wezel_kon->l_sasiadow = NULL;
			}

			wezel_kon->nazwa = nazwa;

			// Dodajemy grawędź do reprezentacji grafu, jeśli nie istnieje już identyczna
			if ( !czy_istnieje_krawedz( wezel_pocz, wezel_kon ) )
			{
				if ( wezel_pocz->l_sasiadow == NULL )
				{
					wezel_pocz->l_sasiadow = dodaj_krawedz( wezel_kon );
				}
				else
				{
					wezel_pocz->l_sasiadow->nast_ls = dodaj_krawedz( wezel_kon );
				}
			}
		}

		// Pomijamy białe znaki po przeczytaniu nazwy wierzchołka będącego końcem krawędzi
		pomin_biale_znaki();
		znak = (char) getchar();
	}

	wynik = zliczanie_DFS( graf ); // obliczamy liczbę wierzchołków osiągalnych od "start"

	destruktor( graf ); // czyścimy pamięć wykorzystaną do reprezentacji grafu

	printf( "%d\n", wynik ); // wypisanie wyniku na wyjście standardowe

	return 0;
}