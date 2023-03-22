/*
Karol Szwed
7.12.2021 r.
Projekt zaliczeniowy nr 2 - Poziomka
Program grający jako Prawy w Poziomkę - dwuosobową grę rozgrywaną na prostokątnej planszy
podzielonej na wiersze i kolumny (podobne do Domineering)
*/

#include <stdio.h>

// Szerokość bloku stawianego przez graczy na planszy
#ifndef POLA
# define POLA 5
#endif

// Liczba wierszy, na jakie podzielona jest plansza
#ifndef WIERSZE
# define WIERSZE 26
#endif

// Liczba kolumn, na jakie podzielona jest plansza
#ifndef KOLUMNY
# define KOLUMNY 26
#endif

// Określenie, który ruch z maksymalizujących ocenę planszy wybieramy
#ifndef WYBOR
# define WYBOR 1000
#endif

int czy_ruch_mozliwy( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol );
int ocena_planszy( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol );
void zeruj( int plansza[WIERSZE][KOLUMNY] );
void p_stawia_blok( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol );
void l_stawia_blok( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol );
void p_usuwa_blok( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol );
int gra_prawy( int plansza[WIERSZE][KOLUMNY] );

/*
 * IN: 'tab[][]' - tab. 2d o wymiarach planszy
 * FUN: ustawia wartości wszystkich el. tablicy 'tab[][]' na zero
 */
void zeruj( int tab[WIERSZE][KOLUMNY] )
{
	for( int i = 0; i < WIERSZE; i++ )
	{
		for( int j = 0; j < KOLUMNY; j++ )
		{
			tab[i][j] = 0;
		}
	}
}

/*
 * IN: 'plansza' - tab. 2d z planszą, 'wiersz' - nr wiersza z przedziału [0, WIERSZE - POLA + 1] i
 * 'kol' - nr kolumny z przedziału [0, KOLUMNY - POLA + 1]
 * FUN: zmienia pola odpowiadające ruchowi Prawego z pustych (zero) na zajete (jeden)
 */
void p_stawia_blok( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol )
{
	for( int i = kol; i < kol + POLA; i++ )
	{
		plansza[wiersz][i] = 1;
	}
}

/*
 * IN: 'plansza' - tab. 2d z planszą, 'wiersz' - nr wiersza z przedziału [0, WIERSZE - POLA + 1] i
 * 'kol' - nr kolumny z przedziału [0, KOLUMNY - POLA + 1] bloku, którego postawienie cofamy
 * FUN: cofa ruch Prawego (w ramach szukania najlepszego ruchu), tj. ustawia odp. wartości
 * 'plansza[][]' na zero
 */
void p_usuwa_blok( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol )
{
	for( int i = kol; i < kol + POLA; i++ )
	{
		plansza[wiersz][i] = 0;
	}
}

/*
 * IN: 'plansza[][]' - tab. 2d z planszą, 'wiersz' - nr wiersza z przedziału [0, WIERSZE - POLA + 1] i
 * 'kol' - nr kolumny z przedziału [0, KOLUMNY - POLA + 1] stawianego bloku
 * FUN: zmienia pola odpowiadające ruchowi Lewego z pustych (zero) na zajete (jeden)
 */
void l_stawia_blok( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol )
{
	for( int i = wiersz; i < wiersz + POLA; i++ )
	{
		plansza[i][kol] = 1;
	}
}

/*
 * IN: 'plansza[][]' - tab. 2d z plansza, 'wiersz' - nr wiersza z przedziału [0, WIERSZE - POLA + 1] i
 * 'kol' - nr kolumny z przedziału [0, KOLUMNY - POLA + 1] sprawdzanego ruchu
 * FUN: stawia blok w zadanym miejscy, liczy ocenę planszy dla Prawego, cofa wykonny ruch
 * OUT: liczba całkowita '(ile_prawy - ile_lewy)' odp. ocenie planszy dla Prawego po danym ruchu
 */
int ocena_planszy( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol )
{
	p_stawia_blok( plansza, wiersz, kol );// do spr. danego ruchu modyfikujemy planszę

	int ile_lewy = 0;// ile bloków jednocześnie może teraz Lewy umieścić na planszy
	int ile_prawy = 0;// ile bloków jednocześnie może teraz Prawy umieścić na planszy

	// zliczamy, ile bloków może postawić Lewy (z jego perspektywy wiersze i kolumny sa zamienione)
	for( int i = 0; i < KOLUMNY; i++ )
	{
		for (int j = 0; j < WIERSZE; j++)
		{
			if( !plansza[j][i] )// dane pole jest puste
			{
				int k;// indeks
				for( k = j; k < j + POLA && k < WIERSZE && !plansza[k][i]; k++ );// void
				k--;// na koniec pętli k zostanie ostatni raz zwiększone

				// jeśli mamy spójny segment pustych pól o dł. POLA, to można tam postawić blok
				if( k - j + 1 == POLA )
				{
					ile_lewy++;
				}
				j = k;
			}
		}
	}

	// zliczamy, ile pól może postawić Prawy
	for( int i = 0; i < WIERSZE; i++ )
	{
		for (int j = 0; j < KOLUMNY; j++)
		{
			if( !plansza[i][j] )// dane pole jest puste
			{
				int k;// indeks
				for( k = j; k < j + POLA && k < KOLUMNY && !plansza[i][k]; k++ );// void
				k--;// na koniec pętli k zostanie ostatni raz zwiększone
				

				// jeśli mamy spójny segment pustych pól o dł. POLA, to można tam postawić blok
				if( k - j + 1 == POLA )
				{
					ile_prawy++;
				}
				j = k;
			}
		}
	}

	p_usuwa_blok( plansza, wiersz, kol );// cofamy ruch po obliczeniu dla niego oceny planszy

	return (ile_prawy - ile_lewy);
}

/*
 * IN: 'plansza[][]' - tab. 2d z planszą, 'wiersz' - indeks wiersza i 'kol' - indeks kolumny
 * FUN: sprawdzenie, czy Prawy może postawić blok o współrzędnych danych na wejściu
 * OUT: zmienna 'wynik' o wartościach: 0 - nie może, 1 - może postawić blok
 */
int czy_ruch_mozliwy( int plansza[WIERSZE][KOLUMNY], int wiersz, int kol )
{
	int ile_pustych = 0;// liczba pustych pól w spójnym segmencie dł. 'POLA' w danym wierszu
	int wynik = 0;

	for( int i = kol; i < kol + POLA && i < KOLUMNY; i++ )
	{
		if( plansza[wiersz][i] == 0 )
		{
			ile_pustych++;
		}
	}

	// Jeśli w danym wierszu od pola (wiersz, kol) mamy POLA pustych pól, to Prawy może tam
	// postawić blok
	if( ile_pustych == POLA )
	{
		wynik = 1;
	}

	return wynik;
}

/*
 * IN: 'plansza[][]' - tab. 2d z aktualnym stanem planszy
 * FUN: wykonuje turę Prawego, tj. szuka ciągu najlepszych ruchów spośród ruchów możliwych,
 * wybiera odpowiedni, zmienia stan planszy oraz wypisuje wybrany ruch na wyjście standardowe
 * OUT: Jeśli nie istnieje legalny ruch Prawego, zwraca 0, w p. p. zwraca 1
 */
int gra_prawy( int plansza[WIERSZE][KOLUMNY] )
{
	int czy_istnieje_ruch = 0;// wartość 1, jeśli Prawy może wykonać jakikolwiek ruch

	/*
	Jeśli na polu (i, j) Prawy może postawić blok, to wtedy ocena_ruchu[i][j] przyjmuje
	wartość równą ocenie planszy dla wykonanego tam ruchu; w p. p. przyjmuje wartość równą
	(-1) * WIERSZE * KOLUMNY - 1, co jest poniżej min. wartości oceny planszy dla jednego ruchu
	*/
	int ocena_ruchu[WIERSZE][KOLUMNY];
	
	zeruj( ocena_ruchu );
	int maks_ocena = (-1) * WIERSZE * KOLUMNY - 1;// szukamy też, jaka jest największa ocena planszy
	// spośród możliwych do wykonania ruchów
	for( int i = 0; i < WIERSZE; i++ )
	{
		// Prawy stawia bloki poziomo, więc '(POLA - 1)' pól od prawej strony planszy nie może już
		// postawić żadnego bloku
		for( int j = 0; j < KOLUMNY - POLA + 1; j++ )
		{
			if( czy_ruch_mozliwy( plansza, i, j ) )
			{
				czy_istnieje_ruch = 1;
				ocena_ruchu[i][j] = ocena_planszy( plansza, i, j );
			}
			else
			{
				ocena_ruchu[i][j] = (-1) * WIERSZE * KOLUMNY - 1;
			}

			if( ocena_ruchu[i][j] > maks_ocena )
			{
				maks_ocena = ocena_ruchu[i][j];
			}
		}
	}

	if( czy_istnieje_ruch )
	{

		// zliczamy, ile jest ruchów maksymalizujących ocenę planszy
		int ile_maks_ocen = 0;
		for( int i = 0; i < WIERSZE; i++ )
		{
			for( int j = 0; j < KOLUMNY - POLA + 1; j++ )
			{
				if( ocena_ruchu[i][j] == maks_ocena )
				{
					ile_maks_ocen++;
				}
			}
		}

		// wybieramy ruch spośród ciągu maksymalizujących ocenę planszy
		int ktory_ruch = (WYBOR % ile_maks_ocen) + 1;// wartość z przedziału [1, ile_maks_ocen]

		int i = 0;
		int j = 0;// i, j po wyjściu z zewn. pętli przechowują współrzędne wybranego ruchu
		for( i = 0; i < WIERSZE && ktory_ruch > 0; i++ )
		{
			for( j = 0; j < KOLUMNY - POLA + 1 && ktory_ruch > 0; j++ )
			{
				// przechodzimy tylko po ruchach maksymalizujących ocenę planszy
				if( ocena_ruchu[i][j] == maks_ocena )
				{
					ktory_ruch--;
				}
			}
		}
		i--;
		j--;//indeksy i, j przy wychodzeniu z pętli zostaną zwiększone 1 dodatkowy raz

		p_stawia_blok( plansza, i, j );
		printf( "%c%c\n", i + 'a', j + 'A' );
		// zamieniamy indeksy wierszy/kolumn na odp. im litery (a-z i A-Z odpowiednio)
	}
	else
	{
		printf( ".\n" );// Prawy się poddaje, bo nie może wykonać żadnego ruchu
	}

	return czy_istnieje_ruch;
}

/*
 * FUN: Inicjalizuje planszę do gry w Poziomkę; określa, który gracz zaczyna; aktualizuje stan
 * planszy po każdym ruchu; wykonuje ruchy Prawego póki jeden z graczy się nie podda;
 */
int main(void)
{
	int plansza[WIERSZE][KOLUMNY];// tab. zawiera obecny stan planszy - wartość 0 dla pól pustych
	// a 1 dla pól zajętych

	zeruj(plansza);// na poczatku na planszy są same puste pola

	int koniec_gry = 0;// jeśli wartosc 1, to jeden z graczy przegrał lub poddał się
	int a = 0;
	int b = 0;
	int c = 0;// a, b, c to kolejne 3 znaki z danych wejściowych
	int lewy_kol, lewy_wiersz;// znaki odpowiadające kolumnie/wierszowi obecnego ruchu Lewego
	
	a = getchar();
	if( a == '.' )// Lewy się natychmiast poddał, więc Prawy nie wykonuje żadnego ruchu
	{
		koniec_gry = 1;
	}
	else if( a == '-' )// Prawy zaczyna, więc najpierw wykonujemy jego ruch
	{
		gra_prawy( plansza );
		getchar();// kolejny znak po '-' to zawsze '\n', który pomijamy
		a = getchar();
		b = getchar();
		c = getchar();
	}
	else
	{
		b = getchar();
		c = getchar();
	}

	while( a != EOF && b != EOF && c != EOF && !(koniec_gry) )
	{
		if( a == '.' )// Lewy się poddaje
		{
			koniec_gry = 1;
		}
		else
		{
			// zamiana wartości ASCII znaku na numer kolumny/wiersza (z przedziału [0; 26])
			lewy_kol = a - 'A';
			lewy_wiersz = b - 'a';
			// zmienna 'c' to znak nowej linii '\n'

			l_stawia_blok( plansza, lewy_wiersz, lewy_kol );
			if( !gra_prawy( plansza ) )
			{
				koniec_gry = 1;
			}
		}

		if( !koniec_gry )
		{
			a = getchar();
			b = getchar();
			c = getchar();
		}
	}

	return 0;
}