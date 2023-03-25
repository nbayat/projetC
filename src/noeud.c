#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "noeud.h"

// cree un nouveau noeud et initialise ses champs
noeud* create_node(bool est_dossier, char nom[100], noeud* pere) {
    // alloue de la memoire pour le nouveau noeud
    noeud* node = (noeud*)malloc(sizeof(noeud));
    if (node == NULL) {
        assert("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Initialise les champs du noeud
    node->est_dossier = est_dossier;
    strncpy(node->nom, nom, sizeof(node->nom));
    // si le noeud a un parent, on definit son noeud racine comme etant le noeud 
    // racine du parent, sinon on definit son noeud racine comme etant lui meme
    node->fils = NULL;
    return node;
}

// cree un noeud racine qui pointe sur lui meme
noeud* create_root_node() {
    // cree un noeud avec le nom "/" et definit son parent comme etant lui meme
    noeud* root = create_node(true, "/", NULL);
    root->pere = root;
    return root;
}


// ajoute un noeud enfant a un noeud parent
void add_child(noeud* parent, noeud* child) {
    //: alloue de la memoire pour le nouveau noeud enfant
    liste_noeud* new_child_list = (liste_noeud*)malloc(sizeof(liste_noeud));
    if (new_child_list == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // initialise les champs du nouveau noeud enfant
    new_child_list->no = child;
    new_child_list->succ = NULL;
    // ajoute le nouveau noeud enfant a la liste des noeuds enfants du noeud parent
    if (parent->fils == NULL) {
        parent->fils = new_child_list;
    } else {
        liste_noeud* curr = parent->fils;
        while (curr->succ != NULL) {
            curr = curr->succ;
        }
        curr->succ = new_child_list;
    }
}

// supprime un noeud enfant d'un noeud parent
void remove_child(noeud* parent, noeud* child) {
    // Find the child node in the parent's list of children
    liste_noeud* prev = NULL;
    liste_noeud* curr = parent->fils;
    while (curr != NULL) {
        if (curr->no == child) {
            break;
        }
        prev = curr;
        curr = curr->succ;
    }
    // si le noeud enfant n'est pas trouve, on ne fait rien
    if (curr == NULL) {
        return;
    }
    // supprime le noeud enfant de la liste des noeuds enfants du noeud parent
    if (prev == NULL) {
        parent->fils = curr->succ;
    } else {
        prev->succ = curr->succ;
    }
    free(curr);
}

// libere la memoire allouee pour un noeud et ses enfants recursivement
void free_node(noeud* node) {
    // libere la memoire allouee pour les noeuds enfants du noeud courant et ses enfants recursivement
    liste_noeud* curr = node->fils;
    while (curr != NULL) {
        free_node(curr->no);
        liste_noeud* temp = curr;
        curr = curr->succ;
        free(temp);
    }
    // libere la memoire allouee pour le noeud courant
    free(node);
}
