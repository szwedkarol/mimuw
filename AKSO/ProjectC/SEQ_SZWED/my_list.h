/*
 * Karol Szwed
 * 15.04.2023 r.
 * AKSO — Projekt w C
 * Zadanie — zbiory równoważnych ciągów
 *
 * Interfejs listy jednokierunkowej.
 */

#ifndef MY_LIST_H
#define MY_LIST_H

typedef struct list list_t;
typedef struct node node_t;

list_t* new_list_element(list_t *begOfList, node_t *node);
void delete_list_element(list_t **list, list_t **elementToDelete);
list_t* find_list_element_by_node(list_t *list, node_t *node);
list_t *init_new_list(node_t *node);
list_t *get_next(list_t *listEl);
node_t *get_node(list_t *listEl);

#endif // MY_LIST_H
