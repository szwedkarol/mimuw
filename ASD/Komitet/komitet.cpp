/*
Karol Szwed
ASD - Projekt zaliczeniowy I
Komitet strajkowy
MIMUW, 20-11-2023 r.
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// MOD 10^9 + 7
#define MOD 1000000007

inline uint64_t mod(uint64_t a) {
    return (((a + MOD) % MOD) + MOD) % MOD;
}

/*
 * Oblicza liczbę minimalnych komitetów oraz rozmiar minimalnego komitetu
 */
uint64_t committeeCount( int n, uint64_t results[], bool covers[], unsigned int posm[], unsigned int& smallest ) {
    uint64_t total = 0; // Zwracany wynik

    int i = 0;
    while ( i < n ) {
        if ( covers[i] && results[i] ) break;
        i++;
    }
    smallest = posm[i];

    while ( posm[i] == smallest ) {
        total = mod( total + results[i] );
        i++;
    }

    total = mod(total);
    return total;
}

/*
 * Wypełnia pomocniczą tablicę, która określa, który z kolei w komitecie może być dany pracownik
 * (w komitecie o najmniejszym rozmiarze)
 */
void fillPossibleMembers( int r[], unsigned int posm[], int n, int k ) {
    unsigned int lastPin = 0; // koniec poprzedniego segmentu
    unsigned int notRep = 0; // 1. niereprezentowany pracownik przez pracownika r[lastPin]
    unsigned int member = 0; // najdalszy na prawo pracownik, który jeszcze reprezentuje notRep

    unsigned int posC = 1; // możliwy nr pracownika wewnątrz Komitetu
    while ( member < n && r[member] - r[notRep] <= k ) {
        posm[member] = posC;
        member++;
    }
    posC++;
    lastPin = member - 1;
    notRep = member;

    while ( notRep < n && member < n ) {
        while ( notRep < n && r[notRep] - r[lastPin] <= k ) {
            posm[notRep] = posC;
            notRep++;
        } // teraz notRep jest 1. nie reprezentowanym przez 'lastPin'
        if (notRep < n) posm[notRep] = posC;
        member = notRep;

        while ( member < n && r[member] - r[notRep] <= k ) {
            posm[member] = posC;
            member++;
        }

        lastPin = member - 1;
        notRep = lastPin + 1;
        posC++;
    }
}

/*
 * Wypełnia tabelę results[], zawierającą częściowe wyniki liczby możliwych komitetów do utworzenia,
 * które potem wykorzystamy do obliczenia ostatecznego wyniku, ile jest komitetów o minimalnym rozmiarze
 */
void fillResults( uint64_t results[], int r[], unsigned int posm[], int segsum[][2], int n, int k, int l ) {
    // TYMCZASOWE ROZWIĄZANIE Z SUMAMI — zmiana typu na 64-bitowy
    uint64_t sumpref[n]; // Sumy prefiksowe po tablicy results[]

    for ( int i = 0; i < n; i++ ) sumpref[i] = 1;

    unsigned int prev_start = 0; // początek poprzedniego segmentu o stałej wartości w posm[]
    unsigned int prev_end = 0; // koniec poprzedniego segmentu o stałej wartości w posm[]
    int i = 0; // indeks aktualnie rozpatrywanego pracownika jako potencjalnego członka komitetu

    while ( posm[i] == 1 && i < n ) {
        results[i] = 1;
        sumpref[i] = i+1;
        prev_end++;
        i++;
    }
    prev_end--; // prev_end zostało o raz za dużo zwiększone w pętli

    int curr_start; // początek obecnie rozpatrywanego segmentu (wyznaczone przez posm[])
    while ( i < n ) {
        curr_start = i;
        unsigned int curr_candn = posm[i]; // nr w komisji, jaki mogą mieć obecnie rozpatrywani pracownicy
        while ( posm[i] == curr_candn && i < n ) {
            if ( segsum[i][0] != -1 ) {
                if ( segsum[i][0] == 0 ) {
                    // Sumujemy od początku tablicy, więc nic nie odejmujemy
                    results[i] = mod( sumpref[ segsum[i][1] ] );
                    results[i] = mod(results[i]);
                } else {
                    results[i] = mod( sumpref[ segsum[i][1] ] - sumpref[ segsum[i][0] - 1 ] );
                    results[i] = mod( results[i] );
                }
            } else {
                results[i] = 0;
            }

            sumpref[i] = mod( sumpref[i-1] ) + mod( results[i] );
            sumpref[i] = mod( sumpref[i] );

            i++;
        }

        prev_end = i - 1;
        prev_start = curr_start;
    }
}

void coversRightmost( bool cover[], int r[], int n, int k ) {
    for ( int i = n - 1; i >= 0; i-- ) {
        if ( abs(r[i] - r[n-1]) <= k ) {
            cover[i] = 1;
        } else {
            cover[i] = 0;
        }
    }
}

/*
 * Wypełnia tablicę ls[], gdzie ls[i] określa, jak daleko na lewo (patrząc na indeksy pracowników)
 * reprezentuje robotników pracownik 'i'
 */
void fillLS( int r[], int ls[], int n, int k ) {
    ls[0] = 0; // warunek początkowy

    int i = 1;
    int idls = 0;
    while ( i < n ) {
        // Niezmiennik: i >= idls
        while ( r[i] - r[idls] > k ) {
            idls++;
        }

        ls[i] = idls;
        i++;
    }
}

/*
 * Wypełnia tablicę right_end[], gdzie right_end[i] określa, jak daleko na prawo (patrząc na indeksy pracowników)
 * reprezentuje robotników pracownik 'i'
 */
void fillRE( int r[], int t[], int n, int k ) {
    t[n-1] = n - 1; // warunek początkowy

    int i = n - 2;
    int idre = n - 1;
    while ( i >= 0 ) {
        // Niezmiennik: idre >= i
        while ( r[idre] - r[i] > k ) {
            idre--;
        }

        t[i] = idre;
        i--;
    }
}

/*
 * Wypełnia segsum[n][2] przedziałami, po jakich będziemy sumowali, aby uzyskać częściowe wyniki
 * w tablicy results[].
 * segsum[i][0] - lewy koniec odcinka; segsum[i][1] - prawy koniec odcinka; (odcinki domknięte)
 * segsum[i][0] == segsum[i][1] == -1 -> przedział pusty
 */
void fillSegSum( int n, int r[], int segsum[][2], int lefts[], int rights[], unsigned int posm[],
                 int k, int l ) {
    int prev_start = 0; // początek poprzedniego segmentu o stałej wartości w posm[]
    int prev_end = 0; // koniec poprzedniego segmentu o stałej wartości w posm[]
    int i = 0; // indeks aktualnie rozpatrywanego pracownika

    while ( i < n && posm[i] == 1 ) {
        segsum[i][0] = -1; // Przez -1 ozn. przedział pusty
        segsum[i][1] = -1;
        prev_end++;
        i++;
    }
    prev_end--; // O raz za daleko w prawo przesunięty został koniec poprzedniego segmentu w posm[]

    int curr_start; // Początek obecnie rozpatrywanego segmentu
    while ( i < n ) {
        int curr_candn = posm[i]; // którego z kolei członka komitetu rozpatrujemy
        curr_start = i;

        int ileft = prev_start;
        int iright = prev_end;

        // Chcemy, aby wewnątrz głównej pętli indeksy ileft oraz iright były niemalejące,
        // Dlatego przed jej startem zmniejszamy 'iright'
        while ( r[i] - r[iright] < l && iright >= 0) {
            iright--;
        }

        while ( curr_candn == posm[i] && i < n ) {

            while ( r[i] - r[iright+1] >= l && iright < prev_end ) {
                iright++;
            }

            while ( lefts[i] > rights[ileft] + 1 && ileft <= prev_end ) {
                ileft++;
            }

            if ( ileft > iright ) {
                segsum[i][0] = -1;
                segsum[i][1] = -1;
            } else {
                segsum[i][0] = ileft;
                segsum[i][1] = iright;
            }

            i++;
        }
        prev_end = i - 1;
        prev_start = curr_start;
    }
}

int main()
{
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int smallestCommittee; // Najmniejszy możliwy rozmiar Komitetu
    int n, k, l;
    cin >> n >> k >> l;

    int ranga[n];
    for ( int i = 0; i < n; i++ ) {
        cin >> ranga[i];
    }

    sort( ranga, ranga + n );

    unsigned int posMember[n]; // Pracownik i-ty może być posMember[i]-tym członkiem Komitetu
    bool cover[n]; // 1, jeśli i-ty pracownik reprezentuje n-1 robotnika, 0 w p. p.
    uint64_t results[n]; // Tabela częściowych wyników

    for ( int i = 0; i < n; i++ ) {
        results[i] = 0;
        cover[i] = 0;
        posMember[i] = 1;
    } // TEST

    // Dwie poniższe tabele uwzgl. tylko parametr 'k'
    int left_start[n]; // ls[i] określa, jak daleko na lewo (patrząc na indeksy pracowników)
                       // reprezentuje robotników pracownik i
    int right_end[n]; // re[i] określa, jak daleko na prawo (patrząc na indeksy pracowników)
                      // reprezentuje robotników pracownik i

    int segsum[n][2]; // Przedziały, po jakich sumujemy, aby stopniowo uzupełniać 'results[]'

    fillPossibleMembers(ranga, posMember, n, k);
    coversRightmost(cover, ranga, n, k);
    fillLS(ranga, left_start, n, k);
    fillRE(ranga, right_end, n, k);
    fillSegSum(n, ranga, segsum, left_start, right_end, posMember, k, l);
    fillResults(results, ranga, posMember, segsum, n, k, l);

    // Liczba minimalnych komitetów
    uint64_t total = committeeCount(n, results, cover, posMember, smallestCommittee);
    cout << smallestCommittee << " " << total;

    return 0;
}
