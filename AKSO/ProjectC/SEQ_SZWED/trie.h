/*
 * Karol Szwed
 * 15.04.2023 r.
 * AKSO — Projekt w C
 * Zadanie — zbiory równoważnych ciągów
 *
 * Interfejs drzewa trie, reprezentującego zbiór ciągów {0, 1, 2}* wraz
 * z klasami abstrakcji ciągów.
 */

#ifndef SEQ_TRIE_H
#define SEQ_TRIE_H

typedef struct node node_t;
typedef struct abstractClass abstractClass_t;

node_t * new_node();
void node_delete(node_t *node, node_t *prev);
node_t *find_sequence_in_tree(node_t *root, char const *string, node_t **prev);
node_t * init_trie();
int add_seq_to_tree(node_t *root, char const *string);
char const * get_abstractClass_name_by_node(node_t *node);
void set_abstractClass_name_by_node(node_t *node, char *name);
abstractClass_t * merge_abstractClasses(node_t *node1, node_t *node2);
void set_abstractClass(node_t *node, abstractClass_t *abstractClass);

#endif // SEQ_TRIE_H
