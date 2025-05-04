#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    if (new == NULL) return NULL;
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
   
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;
    if (searchTreeMap(tree, key)) return;
    TreeNode * new = createTreeNode(key, value);
    if (new == NULL) return;
    TreeNode * current = tree->root;
    TreeNode * parent = NULL;

    while (current) {
        parent = current;
        if (tree->lower_than(new->pair->key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    new->parent = parent;
    if (tree->lower_than(new->pair->key, parent->pair->key)) {
        parent->left = new;
    } else {
        parent->right = new;
    }

}

TreeNode * minimum(TreeNode * x){
    if(x == NULL) return NULL;

    while(x->left) {
        x = x->left;
    }

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL; 

    TreeNode * current = tree->root;

    while (current != NULL) {
        if (is_equal(tree, key, current->pair->key)) {
            tree->current = current; 
            return current->pair;   
        } else if (tree->lower_than(key, current->pair->key)) {
            current = current->left; 
        } else {
            current = current->right; 
        }
    }

    return NULL; 
}



Pair * upperBound(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root
    
    TreeNode * current = tree->root;
TreeNode * candidate = NULL;

while (current) {
    if (is_equal(tree, key, current->pair->key)) {
        tree->current = current;
        return current->pair;
    } else if (tree->lower_than(key, current->pair->key)) {
        candidate = current; 
        current = current->left; 
    } else {
        current = current->right; 
    }
})
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) return NULL;

    TreeNode *minNode = minimum(tree->root);
    if (minNode != NULL) {
        tree->current = minNode; 
        return minNode->pair; 
    }
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL) return NULL;

    TreeNode * current = tree->current;

     
    if (current->right) {
        TreeNode * successor = minimum(current->right);
        tree->current = successor;
        return successor->pair;
    }

    
    TreeNode * parent = current->parent;
    while (parent && current == parent->right) {
        current = parent;
        parent = parent->parent;
    }

    tree->current = parent; 
    if (parent) return parent->pair;

    return NULL; 
}
