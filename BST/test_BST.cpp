#include <iostream>
#include "BST.h"

void testBinarySearchTree() {
    BinarySearchTree<int> bst;
    //测试用例同原本的代码
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    std::cout << "Original Tree:" << std::endl;
    bst.printTree();
    //测试思路请见report
    bst.remove(3);
    std::cout << "Tree after removing 3:" << std::endl;;
    bst.printTree();
    bst.remove(5);
    std::cout << "Tree after removing 5:" << std::endl;;
    bst.printTree();
    bst.remove(15);
    std::cout << "Tree after removing 15:" << std::endl;;
    bst.printTree();
    bst.remove(10);
    std::cout << "Tree after removing 10:" << std::endl;
    bst.printTree();
}

int main() {
    testBinarySearchTree();
    //让窗口停留
    std::cin.get();
    return 0;
}