/*
 * =====================================================================================
 *
 *       Filename:  TwoFourTree.c
 *
 *    Description:  Implementation of Two Four Tree
 *
 *        Version:  1.0
 *        Created:  01/01/2015 23:59:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Devan Patel (), devanp92@ufl.edu
 *
 * =====================================================================================
 */
#include "TwoFourTree.h"

void init(tft* t) {
    printf("Initializing Two Four Tree\n");
    t = calloc(1, sizeof(t));
    t->size = 0;
}

node* insertFirst(tft* t, int element) {
    node* temp = t->root;
    if(temp->numChildren == 3) {
        node* temp1 = calloc(1, sizeof(node));
        temp1->children[0] = t->root;
        temp1->isLeaf = 0;
        t->root = temp1;
        splitTree(t, temp1, 0);
        return insert(t, temp1, element);
    } else {
        return insert(t, t->root, element);
    }
    t->size++;
}
node* insert(tft* t, node* n, int element) {
    int i = 0;
    while ( i < n->numChildren && element > n->keys[i]) {
        i++;
    }
    if (n->isLeaf) {
        int j;
        for (j = n->numChildren; j > i; j--) {
            n->keys[j] = n->keys[j-1];
        }
        n->keys[j] = element;
        n->numChildren++;
        return n;
    } else {
        if (n->children[i]->numChildren == 1) {
            splitTree(t, n , i);
            if (element > n->keys[i]) {
                i++;
            }
        }
        return insert(t, n->children[i], element);
    }
}

void splitTree(tft* t, node* n, int position) {
    node* temp = n->children[position];
    node* cur = calloc(1, sizeof(node));
    int i;
    for (i = n->numChildren; i > position; i--) {
        n->children[i+1] = n->children[i];
        n->keys[i] = n->keys[i-1];
    }
    n->keys[position] = temp->keys[1];
    n->children[position+1] = cur;
    n->numChildren++;
    if (temp->isLeaf) {
        cur->isLeaf = 1;
        for (i = 0; i < 1; i++) {
            cur->keys[i] = temp->keys[i + 2];
            cur->numChildren++;
        }
        temp->numChildren = 1;
    } else {
        cur->isLeaf = 0;
        for ( i = 0; i < 1; i++) {
            cur->keys[i] = temp->keys[i + 2];
            cur->children[i] = temp->children[i + 2];
            cur->numChildren++;
        }
        cur->children[1] = temp->children[2];
        temp->numChildren = 1;
    }
}

int getSize(tft* t){
    return t->size;
}