#include "BTree.h"
#include <iostream>

using namespace std;

void BTree::traverse() {
    if (root != nullptr) {
        root->traverse();
    }
}

BTreeNode *BTree::search(int key) {
    return (root == nullptr) ? nullptr : root->search(key);
}

void BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode();
        root->insert(key);
    } else {
        BTreeNode* nodeToInsert = insertionNode(key);
        // if there is space enough for a new element
        nodeToInsert->insert(key);
        if(nodeToInsert->shouldSplit()) {
            split(nodeToInsert);
        }
    }
}

void BTree::split(BTreeNode* currentNode) { // NOLINT(misc-no-recursion)
    int floatingKey = currentNode->keys[MIN_KEYS];
    auto* child1 = new BTreeNode();
    auto* child2 = new BTreeNode();

    // Split keys
    for (int index = 0; index < MIN_KEYS; index++) {
        child1->insert(currentNode->keys[index]);
    }
    for (int index = MIN_KEYS + 1; index < (MAX_KEYS + 1); index++) {
        child2->insert(currentNode->keys[index]);
    }

    // Split children
    if(!currentNode->isLeaf()) {
        for (int index = 0; index < MIN_KEYS + 1; index++) {
            child1->addChild(currentNode->children[index]);
        }
        for (int index = MIN_KEYS + 1; index < (TREE_LEVEL + 1); index++) {
            child2->addChild(currentNode->children[index]);
        }
    }

    if (currentNode->parent == nullptr) {
        auto *newRoot = new BTreeNode();
        newRoot->addChild(child1);
        newRoot->addChild(child2);
        newRoot->insert(floatingKey);
        delete currentNode;
        root = newRoot;
    } else {
        int i = 0;
        for(; currentNode->parent->children[i] != nullptr; i++) {
            if (currentNode->parent->children[i] == currentNode) {
                break;
            }
        }
        for(i = i; i < TREE_LEVEL; i++) {
            currentNode->parent->children[i] = currentNode->parent->children[i+1];
        }

        currentNode->parent->addChild(child1);
        currentNode->parent->addChild(child2);
        currentNode->parent->insert(floatingKey);
        if(currentNode->parent->shouldSplit()) {
            split(currentNode->parent);
        }
        delete currentNode;
    }
}

BTreeNode* BTree::insertionNode(int key) {
    if(root == nullptr) {
        cerr << "Precondition failure: root should be different from nullptr" << endl;
        return nullptr;
    }
    return insertionNode(key, root);
}

BTreeNode* BTree::insertionNode(int key, BTreeNode* currentNode) { // NOLINT(misc-no-recursion)
    if(currentNode->isLeaf()) {
        return currentNode;
    }
    int keyIndex = 0;

    for(; keyIndex < currentNode->numKeys; keyIndex++) {
        if(key < currentNode->keys[keyIndex]) {
            return insertionNode(key, currentNode->children[keyIndex]);
        }
    }
    return insertionNode(key, currentNode->children[keyIndex]);
}
