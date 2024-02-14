#include <iostream>
#include "BTreeNode.h"

using namespace std;

BTreeNode::BTreeNode() : numKeys(0) {
    for(auto & child : children) {
        child = nullptr;
    }
    parent = nullptr;
}

bool BTreeNode::isLeaf() {
    return children[0] == nullptr;
}

int BTreeNode::childInsertionIndex(BTreeNode* child) {
    if(children[0] == nullptr) {
        return 0;
    } else {
        int i = 0;
        for(; children[i] != nullptr && i < TREE_LEVEL; i++) {
            if(child->keys[child->numKeys - 1] < keys[i]) {
                return i;
            }
        }
        return i;
    }
}

int BTreeNode::insertionIndex(int value, const int array[], int size) {
    if(size == 0) {
        return 0;
    } else {
        int i = 0;
        for(; i < size; i++) {
            if(value < array[i]) {
                return i;
            }
        }
        return i; //
    }
}

void BTreeNode::addChild(BTreeNode* child) {
    int insertionIndex = childInsertionIndex(child);

    for(int i = numKeys; i >= insertionIndex; i--) {
        children[i+1] = children[i];
    }
    children[insertionIndex] = child;
    child->parent = this;
}

void BTreeNode::insert(int value, int array[], int& size) {
    int index = insertionIndex(value, array, size);
    for(int i = size; i >= index; i--) {
        array[i + 1] = array[i];
    }
    array[index] = value;
    size++;
}

void BTreeNode::insert(int key) {
    insert(key, keys, numKeys);
}

bool BTreeNode::shouldSplit() const {
    return numKeys == TREE_LEVEL;
}

void BTreeNode::traverse() { // NOLINT(misc-no-recursion)
    int i;
    for (i = 0; i < numKeys; i++) {
        if (!isLeaf()) {
            children[i]->traverse();
        }
        cout << " " << keys[i];
    }
    if (!isLeaf()) children[i]->traverse();
}

BTreeNode* BTreeNode::search(int key) { // NOLINT(misc-no-recursion)
    int i = 0;
    while (i < numKeys && key > keys[i]) {
        i++;
    }

    if (keys[i] == key) {
        return this;
    }

    if (isLeaf()) {
        return nullptr;
    }

    return children[i]->search(key);
}
