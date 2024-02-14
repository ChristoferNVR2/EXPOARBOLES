#include <iostream>
#include "BTreeNode.h"
#include "BTree.h"

using namespace std;

int main() {
    BTree tree;

    int keys[] = {10, 7, 20, 3 , 25, 27, 29, 5, 1, 30, 37, 38, 40, 50};

    for (int key : keys) {
        tree.insert(key);
    }

    cout << "Inorder traversal:" << endl; // Display
    tree.traverse();
    cout << endl;

    int searchKey = 29;

    BTreeNode* found = tree.search(searchKey);

    if (found != nullptr) {
        cout << "Key " << searchKey << " found in the tree." << endl;
    }
    else {
        cout << "Key " << searchKey << " not found in the tree." << endl;
    }

    return 0;
}
