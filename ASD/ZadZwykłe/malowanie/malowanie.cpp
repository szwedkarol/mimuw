#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    // Suma wartości w liściach w poddrzewie wierzchołka
    int value;

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

/*
//int sum_leaves( node tree[], int left, int right, int i, int B ) {
//
//    if ( i > B ) {
//        return 0;
//    }
//
//    if ( tree[i].right < left || tree[i].left > right ) {
//        return 0;
//    }
//
//    // Spr, czy przedział w wierzchołku zawiera sie w [left, right]
//    if ( tree[i].left >= left && tree[i].right <= right ) {
//        return tree[i].value;
//    } else {
//        return sum_leaves(tree, left, right, 2 * i, B )+
//               sum_leaves(tree, left, right, 2 * i + 1, B);
//    }
//}
*/

void updateTree( node tree[], int B, int left, int right, int i, int color ) {
    if ( i > B ) {
        return;
    }

    if ( tree[i].right < left || tree[i].left > right ) {
        return;
    }

    if ( tree[i].left >= left && tree[i].right <= right ) {
        // Wszystkie liście, za które odpowiada wierzchołek 'i' stają się jednokolorowe
        int newvalue = 0;
        if ( color == 'B' ) {
            // Długość przedziału, za jaki odpowiada wierzchołek 'i'
            newvalue = tree[i].right - tree[i].left + 1;
        }
        tree[i].value = newvalue;
    } else {
        // Warunek (spr, czy przedział dł. 1) może być niepotrzebny
        if ( tree[i].value == tree[i].right - tree[i].left + 1 ) {
            // Musimy zepchnąć aktualizację w dół - do lewego i prawego syna
            tree[2*i].value = tree[2*i].right - tree[2*i].left + 1;
            tree[2*i+1].value = tree[2*i+1].right - tree[2*i+1].left + 1;
        } else if ( tree[i].value == 0 ) {
            tree[2*i].value = 0;
            tree[2*i+1].value = 0;
        }

        updateTree(tree, B, left, right, 2*i, color );
        updateTree(tree, B, left, right, 2*i+1, color );
        tree[i].value = tree[2*i].value + tree[2*i+1].value; // czy działa?
    }
}

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

	int n; // długość autostrady
	int m; // liczba dni malowań

	cin >> n >> m;

	int B = 1; // najmniejsza potęga dwójki większa od n
    for ( ; B < n; B *= 2 );
    B = 2 * B - 1;

    node tree[B+1]; // drzewo indeksujemy od 1 w celu ułatwienia obliczeń
    set_intervals(tree, B); // czyszczenie drzewa wrzucone w ustawianie przedziałów

    for ( int i = 0; i < m; i++ ) {
        int start;
        int koniec;
        char kolor;

        cin >> start >> koniec >> kolor;

        updateTree(tree, B, start, koniec, 1, kolor );

        cout << tree[1].value << "\n";
    }

	return 0;
}
