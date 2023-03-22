// Karol Szwed
// ASD, Zad. zaliczeniowe nr 2 - Choinka
// 27.12.2022 r.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
 * Wierzchołki drzewa z wejścia — na nich jest wykonywany DFS
 */
struct basic_node {
    vector<int> sons;

    int color; // kolor wierzchołka
    int size = 1; // rozmiar poddrzewa wierzchołka
    int dfs_ptr; // wskazuje na siebie w tablicy utworzonej w kolejności DFS
};

/*
 * Wierzchołki drzewa przedziałowego — reprezentowanego za pomocą tablicy
 * (dzieci wierzchołka i to wierzchołki 2*i, 2*i+1).
 * Liście drzewa to wierzchołki choinki.
 */
struct node {
    int color = -1; // Kolor węzła
    // Wartość -1 w drzewie przedziałowym dla nie-liści

    int mincolor = -1; // kolor o najniższym nr w poddrzewie
    int maxcolor = -1; // kolor o najwyższym nr w poddrzewie

    int count_min = 0; // krotność koloru o najniższym nr w poddrzewie
    int count_max = 0; // krotność koloru o najwyższym nr w poddrzewie

    // Przedział liści w poddrzewie wierzchołka
    int left;
    int right;
};

int tree_size( basic_node input_tree[], basic_node & w ) {
    if ( w.sons.empty() ) {
        return 1;
    }

    w.size = 1;
    for ( int i = 0; i < w.sons.size(); i++ ) {
        w.size += tree_size(input_tree, input_tree[w.sons[i]]);
    }

    return w.size;
}

/*
 * DFS na choince
 */
void dfs(basic_node input_tree[], basic_node & basicNode, node dfsNodes[], int & i ) {
    dfsNodes[i].color = basicNode.color;
    basicNode.dfs_ptr = i;

    for (int son : basicNode.sons) {
        i++;
        dfs(input_tree, input_tree[son], dfsNodes, i);
    }
}

void set_intervals( node tree[], int B ) {
    tree[1].left = 1;
    tree[1].right = B/2 + 1;

    for ( int i = 2; i <= B; i++ ) {
        if ( i % 2 == 0 ) {
            tree[i].left = tree[i/2].left;
            tree[i].right = (tree[i/2].right + tree[i/2].left) / 2;
        } else {
            tree[i].left = (tree[i/2].right + tree[i/2].left) / 2 + 1;
            tree[i].right = tree[i/2].right;
        }
    }

    // Dodajemy przesunięcie, aby tree[i].left/right odpowiadało indeksom w tablicy tree[]
    int shift = B / 2;
    for ( int i = 1; i <= B; i++ ) {
        tree[i].left += shift;
        tree[i].right += shift;
    }
}

/*
 * Funkcja, która sprawdza, czy wierzchołek 'w' ma być brany pod uwagę przy mergowaniu informacji o
 * kolorach w poddrzewach rodzica wierzchołka 'w'
 */
bool notUpdatedSubtree( node w ) {
    bool result = false;

    if ( w.mincolor == -1 && w.maxcolor == -1 ) {
        result = true;
    }

    return result;
}

// Sprawdzone po przepisaniu, działa na 95%
void mergeNodes( node & parent, const node & left_son, const node & right_son ) {
    if (notUpdatedSubtree(left_son) && notUpdatedSubtree(right_son)) return;

    if (notUpdatedSubtree(left_son)) {
        return mergeNodes(parent, right_son, left_son);
    } else if (notUpdatedSubtree(right_son)) {
        parent.count_min = left_son.count_min;
        parent.count_max = left_son.count_max;
        parent.mincolor = left_son.mincolor;
        parent.maxcolor = left_son.maxcolor;

        return;
    }

    parent.maxcolor = max(right_son.maxcolor, left_son.maxcolor);
    parent.mincolor = min(right_son.mincolor, left_son.mincolor);

    parent.count_min = (parent.mincolor == left_son.mincolor) * left_son.count_min;
    parent.count_min += (parent.mincolor == right_son.mincolor) * right_son.count_min;

    parent.count_max = (parent.maxcolor == left_son.maxcolor) * left_son.count_max;
    parent.count_max += (parent.maxcolor == right_son.maxcolor) * right_son.count_max;
}

/*
 * Inicjacja drzewa przedziałowego (po skopiowaniu kolorów liści) oraz
 * aktualizacja drzewa po zmianie koloru jednego z liści.
 */
void updateTree( node tree[], int B, int i) {
    if ( i > B || i == 0 ) return;

    if ( i % 2 == 0 ) {
        // Ojciec, lewy syn, prawy syn
        mergeNodes(tree[i/2], tree[i], tree[i+1]);
    } else {
        // Ojciec, lewy syn, prawy syn
        mergeNodes(tree[i/2], tree[i-1], tree[i]);
    }

    updateTree(tree, B, i / 2);
}

void copy_dfsNodes( node dfsNodes[], node tree[], int B, int n ) {
    int itree = (B+1) / 2;
    for ( int i = 1; i <= n; i++ ) {
        tree[itree].color = dfsNodes[i].color;
        tree[itree].mincolor = tree[itree].color;
        tree[itree].maxcolor = tree[itree].color;
        tree[itree].count_max = 1;
        tree[itree].count_min = 1;

        itree++;
    }

    for ( int i = itree; i <= B; i++ ) {
        tree[i].color = -1;
        tree[i].mincolor = tree[i].color;
        tree[i].maxcolor = tree[i].color;
        tree[i].count_max = 0;
        tree[i].count_min = 0;
    }
}

/*
 * Output: czy powiodła się aktualizacja zmiennych color1/2
 */
bool updateColorsInSegment( int & color1, int & color2, int & count1, int & count2, int newcolor, int newcount ) {
    if ( color1 == -1 || color2 == -1 ) {
        if ( color1 == newcolor ) {
            count1 += newcount;
        } else if ( color2 == newcolor ) {
            count2 += newcount;
        } else if ( color1 == -1 ) {
            color1 = newcolor;
            count1 = newcount;
        } else if ( color2 == -1 ) {
            color2 = newcolor;
            count2 = newcount;
        }

        return true;
    }

    if ( newcolor != color1 && newcolor != color2 ) {
        return false;
    }

    if ( newcolor == color1 ) {
        count1 += newcount;
        return true;
    }

    if ( newcolor == color2 ) {
        count2 += newcount;
        return true;
    }

    return true;
}

/*
 * Sprawdza poprawność pokolorowania poddrzewa choinki (tylko 1 bombka w innym kolorze)
 */
bool checkColoring( node tree[], int B, int i, int left, int right, int & color1, int & color2,
                    int & count_color1, int & count_color2) {
    if ( i > B ) return true;

    if ( tree[i].right < left || tree[i].left > right ) return true;

    // Spr, czy przedział w wierzchołku zawiera się w [left, right]
    if ( tree[i].left >= left && tree[i].right <= right ) {
        if ( tree[i].mincolor == tree[i].maxcolor ) {
            // Poddrzewo jednokolorowe

            return updateColorsInSegment(color1, color2, count_color1, count_color2, tree[i].mincolor, tree[i].count_min);
        }

        if ( tree[i].right - tree[i].left + 1 == tree[i].count_min + tree[i].count_max &&
            (tree[i].count_min <= 1 || tree[i].count_max <= 1) ) {
            return updateColorsInSegment(color1, color2, count_color1, count_color2, tree[i].mincolor, tree[i].count_min) &&
                    updateColorsInSegment(color1, color2, count_color1, count_color2, tree[i].maxcolor, tree[i].count_max);
        } else {
            return false;
        }
    } else {
        return checkColoring( tree, B, 2 * i, left, right, color1, color2, count_color1, count_color2 ) &&
        checkColoring( tree, B, 2 * i + 1, left, right, color1, color2, count_color1, count_color2 );
    }
}

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; // liczba wierzchołków w drzewie ("choince")
    int q; // liczba zapytań

    cin >> n >> q;

    basic_node input_tree[n+1];

    // Budowa choinki
    for ( int i = 2; i <= n; i++ ) {
        int parent;
        cin >> parent;

        input_tree[parent].sons.push_back(i);
    }

    // Kolorowanie choinki
    for ( int i = 1; i <= n; i++ ) {
        cin >> input_tree[i].color;
    }

    tree_size(input_tree, input_tree[1]); // Ustala rozmiar poddrzewa każdego wierzchołka choinki
    node dfsNodes[n+1]; // wierzchołki choinki w kolejności DFS
    int start = 1;
    dfs(input_tree, input_tree[1], dfsNodes, start);

    int B = 1; // najmniejsza potęga dwójki większa od n
    for ( ; B < n; B *= 2 );
    B = 2 * B - 1;

    node tree[B+1]; // drzewo indeksujemy od 1 w celu ułatwienia obliczeń
    set_intervals(tree, B); // ustawianie przedziału liści, jakie są w poddrzewie danego wierzchołka
    copy_dfsNodes(dfsNodes, tree, B, n);

    for ( int i = (B + 1) / 2; i <= (B + 1) / 2 + n - 1; i++ ) {
        updateTree(tree, B, i);
    }

    // Rozpatrywanie zapytań
    for ( int index = 0; index < q; index++ ) {
        char query_type;
        cin >> query_type;
        int node_input_tree;
        cin >> node_input_tree;
        int i = (B + 1) / 2 + input_tree[node_input_tree].dfs_ptr - 1;
        if ( query_type == 'z' ) {
            int newcolor;
            cin >> newcolor;

            tree[i].color = newcolor;
            tree[i].mincolor = newcolor;
            tree[i].maxcolor = newcolor;
            updateTree(tree, B, i);
        } else {
            int color1 = -1;
            int color2 = -1;
            int count_color1 = 0;
            int count_color2 = 0;

            int size = input_tree[node_input_tree].size;
            bool result = checkColoring(tree, B, 1, i, i + size - 1,
                                        color1, color2, count_color1, count_color2);

            if (!( count_color1 + count_color2 == size && (count_color1 <= 1 || count_color2 <= 1) )) {
                result = false;
            }

            if ( result ) {
                cout << "TAK" << '\n';
            } else {
                cout << "NIE" << '\n';
            }
        }
    }

    return 0;
}
