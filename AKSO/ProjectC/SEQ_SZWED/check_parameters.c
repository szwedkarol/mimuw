/*
 * Karol Szwed
 * 15.04.2023 r.
 * AKSO — Projekt w C
 * Zadanie — zbiory równoważnych ciągów złożonych z {0, 1, 2}*
 */

#include "check_parameters.h"
#include <errno.h>
#include <stdlib.h>

int is_seq_only_012(char const *string);
int is_char_012(char c);
int is_string_non_empty(char const *string);

/*
 * Sprawdza, czy podany napis reprezentujący ciąg składa się wyłącznie
 * z {0, 1, 2}.
 * Zwraca liczbę całkowitą oznaczającą:
 * Długość napisu, jeśli jest on poprawny;
 * Zero — napis jest pusty;
 * -1 - napis zawiera niedozwolony znak (spoza {0, 1, 2}).
 */
int is_seq_only_012(char const *string) {
    if (string == NULL) {
        errno = EINVAL;
        return 0;
    }

    int i = 0;
    while (string[i] != '\0') {
        if (is_char_012(string[i]) == -1) {
            return -1;
        }

        i++;
    }

    return i;
}

/*
 * Sprawdza, czy podany znak jest ze zbioru {0, 1, 2}.
 * Zwraca:
 * 1 - znak jest ze zbioru {0, 1, 2};
 * -1 - w p. p.
 */
int is_char_012(char c) {
    if (c == '0' || c == '1' || c == '2') {
        return 1;
    } else {
        errno = EINVAL;
        return -1;
    }
}

/*
 * Sprawdza, czy podany napis jest niepusty oraz wskaźnik różny od NULL.
 * Zwraca:
 * Długość napisu, kiedy jest niepusty;
 * 0 - napis jest pusty lub string == NULL.
 */
int is_string_non_empty(char const *string) {
    if (string == NULL || string[0] == '\0') {
        errno = EINVAL;
        return 0;
    }

    int i = 0;
    while (string[i] != '\0') {
        i++;
    }

    return i;
}