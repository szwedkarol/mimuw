#include <iostream>
#include <vector>

#define MOD 1000000007
#define PRIME 29

using namespace std;

// Wektor potęg liczby PRIME używanej przy haszowaniu
vector<long long> primes;

long long get_hash(long long h[], int beg, int end );
long long mod(long long x);
char binsearch_1st_diff_char( const char word[], long long h[], int a, int b, int c, int d );

/*
 * Bezpieczna funkcja modulo.
 * Zawsze zwraca wynik z zakresu [0, MOD - 1].
 */
long long mod(long long x) {
    return ((x % MOD) + MOD) % MOD;
}

char binsearch_1st_diff_char( const char word[], long long h[], int a, int b, int c, int d ) {
    int shorter_word_len = min(b - a + 1, d - c + 1);
    int left = 0;
    int right = shorter_word_len;
    int mid;
    while ( right - left > 0 ) {
        mid = (left + right) / 2;
        if (get_hash(h, a, a + mid) == get_hash(h, c, c + mid) ) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if ( right == shorter_word_len ) {
        if ( b - a < d - c ) {
            return '<';
        } else {
            return '>';
        }
    } else {
        if ( word[a + right] < word[c + right] ) {
            return '<';
        } else {
            return '>';
        }
    }
}

long long get_hash(long long h[], int beg, int end ) {
    return mod( h[end] - h[beg - 1] * primes[end - beg + 1]);
}

/*
 * Wypełnij tablicę haszującą dla słowa z wejścia.
 * Haszowane są podsłowa będące prefiksami wejścia.
 */
void hash_word( long long h[], int n, char word[] ) {
    h[1] = word[1] - 'a' + 1;

    for (int i = 2; i <= n; i++ ) {
        h[i] = mod(PRIME * h[i-1] + word[i] - 'a' + 1);
    }
}

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // Długość słowa z wejścia
    int m; // Liczba zapytań
    cin >> n >> m;

    primes.push_back(1); // PRIME^0 = 1, więc primes[0] = 1
    for ( int i = 1; i <= n; i++ ) {
        primes.push_back(mod(primes[i-1] * PRIME));
    }

    char word[n+1];
    for ( int i = 1; i <= n; i++ ) {
        cin >> word[i];
    }

    long long hashed[n+1]; // Tablica z haszami prefiksów słowa z wejścia
    hash_word(hashed, n, word);

    // Rozpatrywanie zapytań
    for ( int i = 0; i < m; i++ ) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        if (get_hash(hashed, a, b) == get_hash(hashed, c, d) ) {
            cout << '=';
        } else {
            cout << binsearch_1st_diff_char(word, hashed, a, b, c, d);
        }

        cout << '\n';
    }

    return 0;
}