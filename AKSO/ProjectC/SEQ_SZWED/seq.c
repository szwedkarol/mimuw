/*
 * Karol Szwed
 * 15.04.2023 r.
 * AKSO — Projekt w C
 * Zadanie — zbiory równoważnych ciągów złożonych z {0, 1, 2}*
 */

#include "seq.h"
#include "trie.h"
#include "check_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct seq seq_t;

/*
 * Zbiór ciągów reprezentujemy za pomocą drzewa typu trie.
 */
struct seq {
    node_t * root; // Wskaźnik na korzeń drzewa trie.
    // Korzeń reprezentuje pusty ciąg.
};

seq_t * seq_new();
int seq_add(seq_t *p, char const *s);
int seq_valid(seq_t *p, char const *s);
void seq_delete(seq_t *p);
char const * seq_get_name(seq_t *p, char const *s);
int seq_set_name(seq_t *p, char const *s, char const *n);

/*
 * Tworzy nowy pusty zbiór ciągów.
 */
seq_t * seq_new() {
    seq_t * new_seq_set = (seq_t*)malloc(sizeof(seq_t));

    // Sprawdzanie błędu alokacji pamięci
    if (new_seq_set == NULL ) {
        errno = ENOMEM;
        perror("Error in function seq_new()");
        return NULL;
    }

    new_seq_set->root = init_trie();

    if (errno == ENOMEM && new_seq_set->root == NULL) {
        // Przywracanie zbioru ciągów do stanu sprzed wywołania funkcji.
        seq_delete(new_seq_set);
        return NULL;
    }

    return new_seq_set;
}

/*
 * Usuwa zbiór ciągów i zwalnia całą używaną przez niego pamięć.
 */
void seq_delete(seq_t *p) {
    // Funkcja nic nie robi, jeśli zostanie wywołana ze wskaźnikiem NULL.
    if (p != NULL) {
        node_delete(p->root, NULL);
        free(p);
    }
}

/*
 * Usuwa ze zbioru ciągów podany ciąg "*s" i wszystkie ciągi, których jest on
 * prefiksem.
 */
int seq_remove(seq_t *p, char const *s) {
    if (p == NULL || s == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return -1;
    }

    if (is_seq_only_012(s) <= 0) {
        // Ciąg "*s" jest niepoprawny (pusty napis lub zawiera znak spoza
        // {0, 1, 2}).
        errno = EINVAL;
        return -1;
    }

    node_t *prev;
    node_t *node = find_sequence_in_tree(p->root, s, &prev);
    if (node == NULL) {
        // Nie znaleziono ciągu "*s" w zbiorze, więc nic nie robimy.
        return 0;
    }

    node_delete(node, prev);

    return 1;
}

/*
 * Dodaje do zbioru ciągów podany ciąg i wszystkie niepuste podciągi będące jego
 * prefiksem.
 */
int seq_add(seq_t *p, char const *s) {
    if (p == NULL || s == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return -1;
    }

    if (is_seq_only_012(s) <= 0) {
        // Ciąg "*s" jest niepoprawny (pusty napis lub zawiera znak spoza
        // {0, 1, 2}).
        errno = EINVAL;
        return -1;
    }

    int res = add_seq_to_tree(p->root, s);
    if (errno == ENOMEM) {
        // Przywracamy zbiór ciągów do stanu sprzed wywołania funkcji.
        seq_remove(p, s);

        return -1;
    }

    return res;
}

/*
 * Sprawdza, czy podany ciąg należy do zbioru ciągów "*p".
 */
int seq_valid(seq_t *p, char const *s) {
    if (p == NULL || s == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return -1;
    }

    if (is_seq_only_012(s) <= 0) {
        // Ciąg "*s" jest niepoprawny (pusty napis lub zawiera znak spoza
        // {0, 1, 2}).
        errno = EINVAL;
        return -1;
    }

    int found = 0;
    node_t *prev = NULL;
    if (find_sequence_in_tree(p->root, s, &prev) != NULL) {
        found = 1;
    }

    return found;
}

/*
 * Daje wskaźnik na napis zawierający nazwę klasy abstrakcji,
 * do której należy podany ciąg.
 */
char const * seq_get_name(seq_t *p, char const *s) {
    if (p == NULL || s == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return NULL;
    }

    if (is_seq_only_012(s) <= 0) {
        // Ciąg "*s" jest niepoprawny (pusty napis lub zawiera znak spoza
        // {0, 1, 2}).
        errno = EINVAL;
        return NULL;
    }

    node_t *prev = NULL;
    node_t *node = find_sequence_in_tree(p->root, s, &prev);
    char const *name = get_abstractClass_name_by_node(node);

    if (name == NULL) {
        errno = 0;
    }

    return name;
}

/*
 * Ustawia lub zmienia nazwę klasy abstrakcji, do której należy ciąg.
 */
int seq_set_name(seq_t *p, char const *s, char const *n) {
    if (p == NULL || s == NULL || n == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return -1;
    }

    if (is_seq_only_012(s) <= 0) {
        // Ciąg "*s" jest niepoprawny (pusty napis lub zawiera znak spoza
        // {0, 1, 2}).
        errno = EINVAL;
        return -1;
    }

    // Długość ciągu "*n"
    int name_length = is_string_non_empty(n);

    if (name_length <= 0) {
        // Napis przekazany jako nowa nazwa klasy abstrakcji jest niepoprawny
        // (jest pusty).
        errno = EINVAL;
        return -1;
    }

    char *new_name = (char*)malloc(sizeof(char) * name_length);

    // Sprawdzanie błędu alokacji pamięci
    if (new_name == NULL ) {
        errno = ENOMEM;
        perror("Error in function seq_set_name()");
        return -1;
    }

    // Podaną nazwę należy skopiować, gdyż napis wskazywany przez "*n" może
    // przestać istnieć po zakończeniu działania funkcji.
    strcpy(new_name, n);

    node_t *prev = NULL; // Węzeł przed węzłem reprezentującym ciag "*s".

    // Węzeł w drzewie reprezentujący ciąg "*s".
    node_t *node_reps = find_sequence_in_tree(p->root, s, &prev);

    if (node_reps == NULL) {
        // Podany ciąg "*s" nie należy do zbioru ciągów "*p".
        return 0;
    }

    if (seq_get_name(p, s) == new_name) {
        // Nowa nazwa kl. abstrakcji jest identyczna z obecną, więc nic nie
        // zmieniamy.
        return 0;
    }

    // Wprowadzamy zmianę nazwy klasy abstrakcji.
    set_abstractClass_name_by_node(node_reps, new_name);

    return 1;
}

/*
 * Łączy w jedną klasę abstrakcji klasy abstrakcji reprezentowane przez podane
 * ciągi "*s1" oraz "*s2".
 */
int seq_equiv(seq_t *p, char const *s1, char const *s2) {
    if (p == NULL || s1 == NULL || s2 == NULL) {
        // Każdy wskaźnik przekazany jako parametr musi być różny od NULL.
        errno = EINVAL;
        return -1;
    }

    if (is_seq_only_012(s1) <= 0 || is_seq_only_012(s2) <= 0) {
        // Ciąg "*s1" lub "*s2" jest niepoprawny (pusty napis lub zawiera znak
        // spoza {0, 1, 2}).
        errno = EINVAL;
        return -1;
    }

    node_t *prev1, *prev2;
    node_t *node_s1 = find_sequence_in_tree(p->root, s1, &prev1);
    node_t *node_s2 = find_sequence_in_tree(p->root, s2, &prev2);
    if (node_s1 == NULL || node_s2 == NULL) {
        // Jeden z ciągów nie należy do zbioru, więc zbiór ciągów pozostaje
        // bez zmian.
        return 0;
    }

    // Łączenie list klas abstrakcji

    set_abstractClass(node_s1,
                      merge_abstractClasses(node_s1, node_s2));

    // Nadanie nazwy powstałej klasie abstrakcji.

    return 1;
}