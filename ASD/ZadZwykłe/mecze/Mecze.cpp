#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // liczba zawodników
    int m; // liczba meczy;
    cin >> n;
    cin >> m;

    int player;
    bool game_player[m][n];
    // Obsługa wejścia
    for ( int i = 0; i < m; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            cin >> player;
            if ( j < n / 2 ) {
                game_player[i][player-1] = 0;
            } else {
                game_player[i][player-1] = 1;
            }
        }
    }

    //debug
//    cout << "\n";
//    for ( int i = 0; i < m; i++ ) {
//        for ( int j = 0; j < n; j++ ) {
//            cout << game_player[i][j] << ", ";
//        }
//        cout << "\n";
//    }
//    cout << "\n";
    //debug

    unsigned long long int hash_tab[n]; // el. tablicy to kolumny tablicy "game_player"

    for ( int i = 0; i < n; i++ ) {
        hash_tab[i] = 0uLL;
    }

    for ( int i = 0; i < m; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            if ( game_player[i][j] ) {
                hash_tab[j] += ( 1uLL << i );
            }
        }
    }

    sort( hash_tab, hash_tab+n);

    bool res = true;
    for ( int i = 1; i < n; i++ ) {
        if ( hash_tab[i] == hash_tab[i-1] ) {
            res = false;
        }
    }

    if ( res ) {
        cout << "TAK";
    } else {
        cout << "NIE";
    }

    return 0;
}

