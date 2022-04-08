#include <iostream>
#include <vector>

using namespace std;

template <typename valType>
class BTnode {
public:
private:
    valType _val;
    int _cnt;
    BTnode* _lchild;
    BTnode* _rchild;
};

template <typename elemType>
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree&);

    bool empty() { return _root == 0; }
    void clear();

private:
    BTnode<elemType>* _root;

    void copy(BTnode<elemType>* dst, BTnode<elemType>* src);
};

template <typename elemType>
inline BinaryTree<elemType>::BinaryTree(const BinaryTree& rhs) {
    copy(_root, rhs._root);
}

template <typename elemType>
inline BinaryTree<elemType>::~BinaryTree() {
    clear();
}

template <typename elemType>
inline BinaryTree<elemType>& BinaryTree<elemType>::operator=(
    const BinaryTree& rhs) {
    if (this != &rhs) {
        clear();
        copy(_root, rhs._root);
        return *this;
    }
}

int main(int argc, char** argv) {
    return 0;
}