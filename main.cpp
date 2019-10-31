#include "tree.h"
#include <cassert>
using bintree::TNode;

int main() {
    auto node = TNode<int>::createLeaf(1);
    
    assert(!node->getLeft()); //no left elem
    assert(!node->getRight()); // no right elem
    assert(node->getParent() == nullptr); // no parent


    const auto node2 = node; 
    assert(!node2->getLeft()); // no left
    assert(!node2->getRight()); // no right

    node->replaceLeftWithLeaf(5); // set left to 5

    assert(node->getLeft()->getValue() == 5); // left is 5
    assert(node->getLeft()->getParent() == node); // parent of child of node is node

    node->replaceRightWithLeaf(518);

    assert(node->getLeft()->getValue() == 5); // left is 5
    assert(node->getLeft()->getParent() == node); // parent is ok
    assert(node->getRight()->getValue() == 518); // right is 518
    assert(node->getRight()->getParent() == node); //its parent is node

    
    auto leaf = TNode<int>::createLeaf(4); // make leaf
    auto node3 = TNode<int>::fork(0, node, leaf); // fork

    assert(node3->getValue() == 0); // value is 0
    assert(node3->getLeft()->getValue() == 1); // value at left is 1
    assert(node3->getLeft()->getLeft()->getValue() == 5); 
    assert(node3->getLeft()->getRight()->getValue() == 518);
    assert(node3->getRight()->getValue() == 4);

    assert(node3->getLeft()->getParent() == node3); 
}