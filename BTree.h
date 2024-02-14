#ifndef EXPOARBOLESBYB__BTREE_H
#define EXPOARBOLESBYB__BTREE_H // NOLINT(bugprone-reserved-identifier)

#include "BTreeNode.h"

class BTree {
    BTreeNode* root;

public:
    BTree() : root(nullptr) {}
    void traverse();
    BTreeNode* search(int key);
    void insert(int key);

    BTreeNode* insertionNode(int key);
    BTreeNode* insertionNode(int key, BTreeNode* currentNode);
    void split(BTreeNode* currentNode);
};

#endif //EXPOARBOLESBYB__BTREE_H
