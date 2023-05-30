/*
 * Karol Szwed
 * 15.04.2023 r.
 * AKSO — Projekt w C
 * Zadanie — zbiory równoważnych ciągów
 *
 * Implementacja klasy abstrakcji w zbiorze ciągów jako listy jednokierunkowej.
 */

#include "my_list.h"
#include "trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

/*
 * Lista jednokierunkowa ze wskaźnikami na wierzchołki w drzewie.
 */
typedef struct list list_t;

struct list {
    list_t *next; // Następny element na liście.
    node_t *nodeInAbstractClass; // Lista wskaźników na wierzchołki w drzewie
    // należące do klasy abstrakcji.
};

list_t* new_list_element(list_t *begOfList, node_t *node);
void delete_list_element(list_t **list, list_t **elementToDelete);
list_t* find_list_element_by_node(list_t *list, node_t *node);
list_t *init_new_list(node_t *node);
list_t *get_next(list_t *listEl);
node_t *get_node(list_t *listEl);

/*
 * Inicjuje nową listę i zwraca wskaźnik na jej początek.
 */
list_t *init_new_list(node_t *node) {
    if (node != NULL) {
        list_t *newList = (list_t *) malloc(sizeof(list_t));

        // Sprawdzanie błędu alokacji pamięci
        if (newList == NULL) {
            errno = ENOMEM;
            perror("Error in function init_new_list()");
            return NULL;
        }

        newList->next = NULL;
        newList->nodeInAbstractClass = node;

        return newList;
    } else {
        return NULL;
    }
}

/*
 * Zwraca następny element na liście.
 */
list_t *get_next(list_t *listEl) {
    assert(listEl != NULL);

    if (listEl != NULL) {
        return listEl->next;
    } else {
        return NULL;
    }
}

/*
 * Zwraca węzeł z drzewa, na który wskazuje element listy.
 */
node_t *get_node(list_t *listEl) {
    assert(listEl != NULL);

    if (listEl != NULL) {
        return listEl->nodeInAbstractClass;
    } else {
        return NULL;
    }
}

/*
 * Tworzy nowy element listy za węzłem "*begOfList". Nowy el. listy wskazuje na
 * węzeł w drzewie "*node".
 */
list_t* new_list_element(list_t *begOfList, node_t *node) {
    if (begOfList == NULL || node == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return NULL;
    }

    list_t *newListEl =
            (list_t*)malloc(sizeof(list_t));

    // Sprawdzanie błędu alokacji pamięci
    if (newListEl == NULL ) {
        errno = ENOMEM;
        perror("Error in function new_list_element()");
        return NULL;
    }

    list_t *afterNewListElement = begOfList->next;
    begOfList->next = newListEl;

    newListEl->next = afterNewListElement;
    newListEl->nodeInAbstractClass = node;

    return newListEl;
}

/*
 * Usuwa element listy podany jako argument i zwalnia zaalokowaną pamięć.
 */
void delete_list_element(list_t **list,
                         list_t **elementToDelete) {
    // Jeśli element do usunięcia lub lista, z której usuwamy, to NULL,
    // to nic nie robimy.
    if (*elementToDelete != NULL && *list != NULL) {
        list_t *curr, *prev;
        curr = *list;
        prev = NULL;

        while (curr != *elementToDelete && curr != NULL) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == *elementToDelete) {
            if (prev == NULL) {
                // Usuwamy ostatni element na liście.
                *list = NULL;
            } else {
                prev->next = curr->next;
            }

            free(curr);
            *elementToDelete = NULL;
        }
        // W p. p. nie znaleziono na liście elementu "*elementToDelete", więc
        // nic nie robimy.
    }
}

/*
 * Znajduje na liście "*list" węzeł, który wskazuje na "*node" i zwraca wskaźnik
 * na ten węzeł listy.
 * Jeśli nie udało się znaleźć takiego węzła na liście, zwraca NULL.
 */
list_t* find_list_element_by_node(list_t *list,
                                  node_t *node) {
    if (list == NULL || node == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return NULL;
    }

    // Na pustej liście nie ma żadnego elementu.
    if (list == NULL ) {
        return NULL;
    }

    list_t *curr = list;

    while (curr->nodeInAbstractClass != node && curr != NULL ) {
        curr = curr->next;
    }

    if (curr->nodeInAbstractClass == node) {
        return curr;
    } else {
        return NULL;
    }
}

/*
 * Usuwa całą listę i zwalnia zaalokowaną pamięć.
 */
void delete_list_all(list_t *list) {
    if (list != NULL) {
        list_t *curr, *prev;
        prev = NULL;
        curr = list;

        while (curr != NULL) {
            prev = curr;
            free(prev);
            curr = curr->next;
        }
    }
}

/*
 * Wypisuje całą zawartość listy podanej jako argument.
 */
void print_list_all(list_t *list) {
    list_t *curr = list;

    while (curr != NULL) {
        node_t *node = curr->nodeInAbstractClass;
        list_t *next = curr->next;

        printf("Na co wskazuje: %p\n", curr);
        printf("Na co wskazuje w drzewie: %p\n", node);
        printf("Co jest po mnie: %p\n", next);

        printf("\n");

        curr = curr->next;
    }
}

