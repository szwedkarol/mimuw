#include <iostream>
#include <algorithm>

using namespace std;

#define MOD 1000000000

struct node {
    // Suma wartości w liściach w poddrzewie wierzchołka
    long long int value;

    // Przedział liści w poddrzewie wierzchołka
    int left;
    int right;
};

void clear_tree( node tree[], int B ) {
    for ( int i = 0; i <= B; i++ ) {
        tree[i].value = 0LL;
    }
}

void set_intervals( node tree[], int B ) {
    tree[1].left = 1;
    tree[1].right = B/2 + 1;

    tree[0].value = 0;
    tree[1].value = 0;
    for ( int i = 2; i <= B; i++ ) {
        tree[i].value = 0; // to speed up
        if ( i % 2 == 0 ) {
            tree[i].left = tree[i/2].left;
            tree[i].right = (tree[i/2].right + tree[i/2].left) / 2;
        } else {
            tree[i].left = (tree[i/2].right + tree[i/2].left) / 2 + 1;
            tree[i].right = tree[i/2].right;
        }
    }
}

long long int sum_leaves( node tree[], int left, int right, int i, int B ) {

    if ( i > B ) {
        return 0LL;
    }

    if ( tree[i].right < left || tree[i].left > right ) {
        return 0LL;
    }

    // Spr, czy przedział w wierzchołku zawiera sie w [left, right]
    if ( tree[i].left >= left && tree[i].right <= right ) {
        return tree[i].value % MOD; // 1 mld
    } else {
        return (sum_leaves(tree, left, right, 2 * i, B ) % MOD)+
               (sum_leaves(tree, left, right, 2 * i + 1, B) % MOD); // 1 mld
    }
}

void modify_tree( node tree[], long long int newv, int i ) {
    //tree[i].value = newv % MOD; // REVERSE IF BREAKS
    tree[i].value = newv;

    while ( i >= 2 ) {
        i /= 2;
        //tree[i].value = (tree[2*i].value % MOD) + (tree[2*i+1].value % MOD); REVERSE IF BREAKS
        tree[i].value = tree[2*i].value + tree[2*i+1].value;
        tree[i].value %= MOD; // 1 mld
    }
}

int main()
{
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    int k;
    cin >> n >> k;

    int T[n+1]; // permutacja liczb {1, ..., n}
    for ( int i = 1; i <= n; i++ ) {
        cin >> T[i];
    }

    int B = 1; // najmniejsza potęga dwójki większa od n
    for ( ; B < n; B *= 2 );
    B = 2 * B - 1;

    node tree[B+1]; // drzewo indeksujemy od 1 w celu ułatwienia obliczeń
    set_intervals(tree, B); // czyszczenie drzewa wrzucone w ustawianie przedziałów
    //clear_tree(tree, B);

    //debug - przedziały
//    cout << "\n";
//    for ( int i = 1; i <= B; i++ ) {
//        cout << tree[i].left << ", " << tree[i].right << "\n";
//    }
//    cout << "\n";

    long long int results[n+1][k+1]; // tablica zawierająca pośrednie rezultaty
    // druga kolumna indeksowana od 1, bo mamy co najmniej 1-inwersje

    for ( int i = 1; i <= n; i++ ) {
        results[i][1] = 1LL; //warunek początkowy
    }

//    for ( int i = 1; i <= n; i++ ) {
//        for ( int j = 2; j <= k; j++ ) {
//            results[i][j] = 0LL;
//        }
//    }

    for ( int j = 2; j <= k; j++ ) {
        clear_tree(tree, B);
        for ( int i = 1; i <= n; i++ ) {

            //debug
//            for ( int m = 1; m <= B; m++ ) {
//                cout << tree[m].value << " ";
//            }
//            cout << "\n";

            if ( T[i] + 1 > n ) {
                results[i][j] = 0LL;
            } else {
                // REVERSE IF BREAKS
                //results[i][j] = sum_leaves(tree, T[i]+1, n, 1, B) % MOD;// (suma liści [ T[i] + 1, n ])
                results[i][j] = sum_leaves(tree, T[i]+1, n, 1, B);// (suma liści [ T[i] + 1, n ])
            }

            // tree[ ( T[i]-ty liść ) ] = results[i][j-1];
            // aktualizacja całego drzewa

            // B/2 + 1 -> 1. liść w drzewie

            modify_tree(tree, results[i][j-1], B / 2 + T[i]);
        }
    }

    // debug
//    cout << "\n";
//    for ( int j = 1; j <= k; j++ ) {
//        for ( int i = 1; i <= n; i++ ) {
//            cout << results[i][j] << " ";
//        }
//        cout << "\n";
//    }
//    cout << "\n";

    long long int res = 0LL;

    for ( int i = 1; i <= n; i++ ) {
        res += results[i][k];
        res %= MOD;
    }

    cout << res;

    return 0;
}
