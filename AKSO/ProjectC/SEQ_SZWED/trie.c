/*
 * Karol Szwed
 * 15.04.2023 r.
 * AKSO — Projekt w C
 * Zadanie — zbiory równoważnych ciągów
 *
 * Implementacja drzewa typu trie służącego do reprezentacji
 * zbioru ciągów {0, 1, 2}* wraz z klasami abstrakcji ciągów.
 */

#include "my_list.h"
#include "trie.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

/*
 * Reprezentuje węzły drzewa typu trie
 */
typedef struct node node_t;

typedef struct abstractClass abstractClass_t;

struct abstractClass {
    char *name; // Nazwa klasy abstrakcji
    list_t *listOfElements; // lista zawierająca wskaźniki na wierzchołki
    // w drzewie będące elementami klasy abstrakcji
};

struct node {
    // Wskaźniki na kolejne węzły, reprezentujące odp. 0, 1, 2 w ciągu.
    node_t *next[3];

    // Wskaźnik na klasę abstrakcji, do której należy ciąg kończący się w danym
    // węźle, tj. ciąg odpowiadający ścieżce od korzenia drzewa do węzła.
    abstractClass_t *abstractClass;
};

node_t * new_node();
void node_delete(node_t *node, node_t *prev);
node_t *find_sequence_in_tree(node_t *root, char const *string, node_t **prev);
node_t * init_trie();
int add_seq_to_tree(node_t *root, char const *string);
char const * get_abstractClass_name_by_node(node_t *node);
void set_abstractClass_name_by_node(node_t *node, char *name);
abstractClass_t * merge_abstractClasses(node_t *node1, node_t *node2);
void set_abstractClass(node_t *node, abstractClass_t *abstractClass);
void delete_abstractClass(abstractClass_t * abstractClass);

/*
 * Zwraca wskaźnik na korzeń nowego drzewa trie.
 */
node_t * init_trie() {
    node_t *root = (node_t*)malloc(sizeof(node_t));

    // Sprawdzanie błędu alokacji pamięci
    if (root == NULL ) {
        errno = ENOMEM;
        perror("Error in function new_node()");
        return NULL;
    }

    for (int i = 0; i < 3; i++) {
        root->next[i] = NULL;
    }
    root->abstractClass = NULL;

    return root;
}

/*
 * Zwraca wskaźnik na nowo utworzoną klasę abstrakcji, której elementem jest
 * "*node".
 */
abstractClass_t * init_abstractClass(node_t *node) {
    if (node == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return NULL;
    }

    abstractClass_t *abstractClass = (abstractClass_t*)
            malloc(sizeof(abstractClass_t));

    // Sprawdzanie błędu alokacji pamięci
    if (abstractClass == NULL ) {
        errno = ENOMEM;
        perror("Error in function init_abstractClass()");
        return NULL;
    }

    abstractClass->name = NULL;
    abstractClass->listOfElements = init_new_list(node);

    if (abstractClass->listOfElements == NULL && errno == ENOMEM) {
        // Przywracamy zbiór ciągów do stanu sprzed wywołania funkcji.
        return NULL;
    }

    return abstractClass;
}

/*
 * Zwraca wskaźnik na nowy węzeł w drzewie trie.
 */
node_t * new_node() {

    node_t *node = (node_t*)malloc(sizeof(node_t));

    // Sprawdzanie błędu alokacji pamięci
    if (node == NULL ) {
        errno = ENOMEM;
        perror("Error in function new_node()");
        return NULL;
    }

    // Tworzymy klasę abstrakcji dla ciągu odp. ścieżce od korzenia do nowo
    // utworzonego węzła drzewa.
    node->abstractClass = init_abstractClass(node);

    if (errno == ENOMEM && (node->abstractClass == NULL ||
        node->abstractClass->listOfElements == NULL)) {
        // Przywracamy zbiór ciągów do stanu sprzed wywołania.
        return NULL;
    }

    for (int i = 0; i < 3; i++) {
        node->next[i] = NULL;
    }

    return node;
}

/*
 * Dodaje do drzewa ciąg podany przez "*string" wraz z odpowiadającymi ciągowi i
 * jego prefiksami klasami abstrakcji.
 *
 * Zwraca 1, jeśli co najmniej jeden nowy ciąg został dodany do drzewa;
 * 0 - kiedy drzewo pozostało w niezmienionym stanie;
 * -1 - jeden z argumentów jest niepoprawny.
 */
int add_seq_to_tree(node_t *root, char const *string) {
    if (root == NULL || string == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return -1;
    }

    int isSeqSetChanged = 0;
    node_t *prev = NULL;
    if (find_sequence_in_tree(root, string, &prev) != NULL) {
        // Cały ciąg jest reprezentowany w drzewie, więc zwracamy 0;
        return isSeqSetChanged;
    }
    isSeqSetChanged = 1;

    // Ciąg lub pewien jego prefiks nie jest reprezentowany w drzewie, więc
    // szukamy najkrótszego prefiksu, którego nie ma w drzewie.

    char c = string[0];
    int i = 0;
    node_t *node = root;
    while (c != '\0' && node->next[c - '0'] != NULL) {
        node = node->next[c - '0'];
        i++;
        c = string[i];
    }

    // Ciąg kończący się na "*node" jest najdłuższym w pełni reprezentowanym
    // prefiksem ciągu "*string".

    while (c != '\0') {
        if (node->next[c - '0'] == NULL) {
            node->next[c - '0'] = new_node();

            if (errno == ENOMEM && node->next[c - '0'] == NULL) {
                // Przywracamy stan zbioru ciągów sprzed wywołania funkcji.
                return 0;
            }
        }

        node = node->next[c - '0'];
        i++;
        c = string[i];
    }

    return isSeqSetChanged;
}

/*
 * Zwalnia pamięć zaalokowaną przez klasę abstrakcji "*abstractClass".
 */
void delete_abstractClass(abstractClass_t * abstractClass) {
    // Uwaga: Nie zwalnia pamięci zaalokowanej przez listę wewnątrz
    // klasy abstrakcji "*abstractClass".
    if (abstractClass != NULL) {
        assert(abstractClass->listOfElements == NULL);

        free(abstractClass->name);
        free(abstractClass);
    }
}

/*
 * Usuwa węzeł "*node" w drzewie.
 */
void node_delete(node_t *node, node_t *prev) {
    if (node != NULL) {
        // Usuwając węzeł, musimy również usunąć całe jego poddrzewo.
        for (int i = 0; i < 3; i++) {
            node_delete(node->next[i], node);
            node->next[i] = NULL;
        }

	    if (node->abstractClass != NULL) {
            // Kiedy usuwamy węzeł, usuwamy również element listy jego klasy
            // abstrakcji, który na niego wskazywał.
            list_t *elementToDelete =
                    find_list_element_by_node(
                            node->abstractClass->listOfElements, node);

            delete_list_element(&(node->abstractClass->listOfElements),
                                &elementToDelete);

            if (node->abstractClass->listOfElements == NULL ) {
                // Usuwamy ostatni element klasy abstrakcji, więc musimy też zwolnić
                // pamięć zaalokowaną przez klasę abstrakcji
                delete_abstractClass(node->abstractClass);
                node->abstractClass = NULL;
            }
	    }

        // Szukamy i ustawiamy na NULL wskaźnik w węźle poprzedzającym ten usuwany.
        if (prev != NULL) {
            int j = 0;
            while (prev->next[j] != node && j < 2) j++;
            prev->next[j] = NULL;
        }

        free(node);
    }
}

/*
 * Sprawdza, czy ciąg kluczy (reprezentowany za pomocą napisu "*string")
 * występuje w drzewie "*root".
 *
 * Jeśli tak, to zwraca wskaźnik na węzeł reprezentujący ciąg (tj. ścieżka od
 * korzenia drzewa do zwracanego węzła zadaje szukany ciąg).
 * Jeśli nie, to zwraca NULL;
 *
 * Dodatkowo, ustawia wskaźnik "*prev", aby wskazywał na węzeł bezpośrednio
 * przed znalezionym.
 */
node_t *find_sequence_in_tree(node_t *root, char const *string, node_t **prev) {
    if (root == NULL || string == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return NULL;
    }

    bool found = false;
    char c;
    int i = 0;
    node_t *node;
    node = root;
    *prev = NULL;

    while (node != NULL && !found ) {
        // Szukamy w drzewie kolejno węzłów "string[0]", "string[1]", ..., więc
        // następny węzeł jest zadany przez "string[i]".
        *prev = node;
        node = node->next[string[i] - '0'];

        i++;
        c = string[i];
        if (c == '\0' && node != NULL) {
            found = true;
        }
    }

    if (found) {
        return node;
    } else {
        return NULL;
    }
}

/*
 * Daje wskaźnik na napis zawierający nazwę klasy abstrakcji, do której należy
 * ciąg reprezentowany przez węzeł "*node".
 */
char const * get_abstractClass_name_by_node(node_t *node) {
    if (node != NULL) {
        return node->abstractClass->name;
    } else {
        return NULL;
    }
}

/*
 * Zmienia nazwę klasy abstrakcji, do której należy ciąg reprezentowany przez
 * węzeł "*node".
 */
void set_abstractClass_name_by_node(node_t *node, char *name) {
    if (node == NULL || name == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return;
    }

    node->abstractClass->name = name;
}

/*
 * Zwraca wskaźnik na nową klasę abstrakcji, będącą połączeniem klas abstrakcji,
 * do jakich należą ciągi reprezentowane przez "*node1" oraz "*node2".
 *
 * Funkcja NIE nadaje nazwy nowo utworzonej klasie abstrakcji oraz NIE usuwa
 * łączonych klas abstrakcji — usuwa wyłącznie listę elementów klasy abstrakcji.
 */
abstractClass_t * merge_abstractClasses(node_t *node1, node_t *node2) {
    if (node1 == NULL || node2 == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return NULL;
    }

    abstractClass_t *new_abstractClass = init_abstractClass(node1);

    list_t *curr_list1 = node1->abstractClass->listOfElements;
    while(curr_list1 != NULL) {
        new_list_element(new_abstractClass->listOfElements,
                         get_node(curr_list1));

        curr_list1 = get_next(curr_list1);
    }

    list_t *curr_list2 = node2->abstractClass->listOfElements;
    while(curr_list2 != NULL) {
        new_list_element(new_abstractClass->listOfElements,
                         get_node(curr_list2));

        curr_list2 = get_next(curr_list2);
    }

    return new_abstractClass;
}

/*
 * Zmienia wskaźnik w węźle "*node" określający, do jakiej należy klasy
 * abstrakcji na dany jako parametr "*abstractClass".
 *
 * Funkcja wyłącznie zmienia wartość parametru "*node", nie wprowadza innych
 * zmian w strukturze zbioru ciągów.
 */
void set_abstractClass(node_t *node, abstractClass_t *abstractClass) {
    if (node != NULL && abstractClass != NULL) {
        node->abstractClass = abstractClass;
    }
}

/*
 * Wypisuje całe poddrzewo "*node".
 */
void printAll(node_t *node) {
    if ( node != NULL ) {
        for (int i = 0; i < 3; i++) {
            if (node->next[i] != NULL) {
                printf("%d, ", i);
            }
        }

        printf("\n");

        for (int i = 0; i < 3; i++) {
            printAll(node->next[i]);
        }
    }
}
