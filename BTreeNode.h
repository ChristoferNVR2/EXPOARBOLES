#ifndef EXPOARBOLESBYB__BTREENODE_H
#define EXPOARBOLESBYB__BTREENODE_H // NOLINT(bugprone-reserved-identifier)

const int TREE_LEVEL = 3;
const int MAX_KEYS = TREE_LEVEL - 1;
const int MIN_KEYS = MAX_KEYS / 2;

class BTreeNode {
    int keys[MAX_KEYS + 1]{};
    BTreeNode* children[TREE_LEVEL + 1]{};
    BTreeNode* parent;
    int numKeys;

public:
    explicit BTreeNode();

    bool isLeaf();

    int childInsertionIndex(BTreeNode* child);
    static int insertionIndex(int value, const int array[], int size);

    void addChild(BTreeNode* child);

    static void insert(int value, int array[], int& size);
    void insert(int key);

    [[nodiscard]] bool shouldSplit() const;

    void traverse();
    BTreeNode* search(int key);

    friend class BTree;
};


#endif //EXPOARBOLESBYB__BTREENODE_H
