/**
 * @file BST.h
 * @author M. A. Weiss (you@domain.com)
 * @brief 课本代码的注释和改进
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException {
};

class IllegalArgumentException {
};

class ArrayIndexOutOfBoundsException {
};

class IteratorOutOfBoundsException {
};

class IteratorMismatchException {
};

class IteratorUninitializedException {
};

/**
 * @brief 二叉搜索树模板类
 *
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template<typename Comparable>
class BinarySearchTree {
public:
    /**
     * @brief 默认构造函数
     *
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{nullptr} {}

    /**
     * @brief 拷贝构造函数
     *
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     *
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{clone(rhs.root)} {}

    /**
     * @brief 移动构造函数
     *
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     *
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept: root{rhs.root} {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     *
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     *
     * 这是一个公有接口，它调用了私有的递归函数。
     *
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if (isEmpty())
            throw UnderflowException{};
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     *
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if (isEmpty())
            throw UnderflowException{};
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     *
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     *
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     *
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     *
     * @param out 输出流，默认为 std::cout
     */
    void printTree() const {
        if (isEmpty()) {
            std::cout << "Empty tree" << std::endl;
        } else {
            printTreeHelper(root, "", false);
        }
    }

    /**
     * @brief 清空树中的所有元素
     *
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 插入一个常量引用元素到树中
     *
     * @param x 要插入的元素
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    int getMaxHeight() {
        return getHeight(root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     *
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * @brief 从树中移除指定的元素
     *
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    /**
     * @brief 拷贝赋值运算符
     *
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     *
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }


    /**
     * @brief 移动赋值运算符
     *
     * 将一个树的资源移动到当前树中。
     *
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height = 1;              ///< 节点高度

        /**
         * @brief 构造函数，接受常量引用
         *
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
                : element{theElement}, left{lt}, right{rt} {}

        /**
         * @brief 构造函数，接受右值引用
         *
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
                : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     *
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        /// 从一个空节点开始查找，返回空指针
        if (t == nullptr) {
            return nullptr;
        }
        /// 向左无路了，当前节点就是最小元素
        if (t->left == nullptr) {
            return t;
        }
        /// 否则继续向左查找
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     *
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        /// 这里没有使用递归，而是使用循环，更高效
        /// findMin 也可以改成循环实现
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     *
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        /// 这是递归版本，也可以有循环版本
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } else if (x > t->element) {
            return contains(x, t->right);
        } else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     *
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTreeHelper(BinaryNode *node, const std::string &prefix, bool isLeft) const {
        if (node == nullptr) {
            return;
        }

        // 打印当前节点的值
        std::cout << prefix;
        std::cout << (isLeft ? "|------ " : "`------ ");
        std::cout << node->element << std::endl;

        // 递归打印左子树和右子树，更新前缀和方向
        std::string newPrefix = prefix + (isLeft ? "|   " : "    ");
        printTreeHelper(node->left, newPrefix, true);  // 打印左子树
        printTreeHelper(node->right, newPrefix, false); // 打印右子树
    }

    /**
     * @brief 递归清空树中的所有元素
     *
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode *&t) {
        /// 这必须是一个后序遍历，为什么？
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            /// delete 并不会自动将指针置空，这里需要手动置空
            t = nullptr;
        }
    }

    /**
     * @brief 递归插入一个常量引用元素到树中
     *
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(const Comparable &x, BinaryNode *&t) {
        /// 这句话乍一看不可思异，怎么能对一个空指针赋值呢？
        /// 但是这里是引用，所以实际上是对指针 t 的引用，t 现在存了 nullptr,
        /// 所以可以修改指针 t 的值
        if (t == nullptr) {
            /// 创建一个新节点，包含 x 的值，左右子节点为空
            /// 挂在 t 指向的节点上
            /// 而在递归过程中，t 总是会指向父节点的左子节点或右子节点
            /// 所以这里实际上是将新节点挂在父节点的左子节点或右子节点上
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        } else {
            /// 如果元素已存在，则不进行插入
            /// 这种情况不可遗漏，严格的规则中也可以抛出异常
        }
        //插入后维持平衡
        t = balance(t);
    }

    /**
     * @brief 递归插入一个右值引用元素到树中
     *
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(Comparable &&x, BinaryNode *&t) {
        /// 一样的逻辑
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
            // 如果元素已存在，则不进行插入
        }
        //插入后维持平衡
        t = balance(t);
    }

    /**
     * @brief 从树中移除指定的元素（AVL版）
     *
     * @param x 要移除的元素
     * @param t 当前节点指针
     */
    void remove(const Comparable &x, BinaryNode *&_root) {
        BinaryNode *targetNode = _root;
        BinaryNode *parentNode = nullptr;

        bool is_target_found = false;
        //查找节点，并保持对其父节点的追踪
        while (targetNode != nullptr) {
            if (x < targetNode->element) {
                parentNode = targetNode;
                targetNode = targetNode->left;
            } else if (x > targetNode->element) {
                parentNode = targetNode;
                targetNode = targetNode->right;
            } else {
                is_target_found = true;
                break;
            }
        }
        if (!is_target_found) return;

        //现在找到了待删除的目标节点，下面执行删除操作
        BinaryNode *replaceNode;
        if (targetNode->right == nullptr) {
            //若不存在右子树，则直接替换为左节点
            replaceNode = targetNode->left;
        } else {
            //若存在右子树，则替换为右子树最小节点
            BinaryNode *parentNodeOfMin = targetNode;
            replaceNode = targetNode->right;
            while (replaceNode->left != nullptr) {
                parentNodeOfMin = replaceNode;
                replaceNode = replaceNode->left;
            }
            //如果要替换上来的节点不是待删节点的右节点，则要继承待删节点的右子树
            if (parentNodeOfMin != targetNode) {
                parentNodeOfMin->left = replaceNode->right;
                replaceNode->right = targetNode->right;
            }
            //无论如何，都要继承左子树
            replaceNode->left = targetNode->left;
        }
        //重新连接上级，当然如果父节点为空则说明已经为根节点，要更新根节点指针
        if (parentNode == nullptr) {
            _root = replaceNode;
        } else if (parentNode->left == targetNode) {
            parentNode->left = replaceNode;
        } else {
            parentNode->right = replaceNode;
        }
        delete targetNode;
        //下面是自平衡部分
        BinaryNode* currentNode = parentNode;
        while (currentNode != nullptr) {
            BinaryNode *oldCurrentNode = currentNode;
            int oldHeight = getHeight(oldCurrentNode);
            currentNode = findParent(oldCurrentNode->element);
            BinaryNode *balancedCurrentNode = balance(oldCurrentNode);
            if (currentNode != nullptr) {
                if (currentNode->left == oldCurrentNode) {
                    currentNode->left = balancedCurrentNode;
                } else {
                    currentNode->right = balancedCurrentNode;
                }
            }
            if (oldHeight == getHeight(balancedCurrentNode)) {
                break;
            }
        }
    }

    BinaryNode *findParent(const Comparable &x) {
        BinaryNode *parentNode = nullptr;
        BinaryNode *currentNode = root;
        while (currentNode != nullptr) {
            if (currentNode->element == x) {
                break;
            } else if (x < currentNode->element) {
                parentNode = currentNode;
                currentNode = currentNode->left;
            } else {
                parentNode = currentNode;
                currentNode = currentNode->right;
            }
        }
        return parentNode;
    }

    /**
     * @param t 当前节点
     * @return 获取高度，判空时约定为0（依作业要求）
     */
    int getHeight(BinaryNode *t) const {
        return t == nullptr ? 0 : t->height;
    }

    /**
     * @brief 更新高度值（依作业要求）
     * @param t
     */
    void updateHeight(BinaryNode *t) {
        if (t != nullptr) {
            t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1;
        }
    }

    /**
     * @param t
     * @return 平衡值，大于1或小于-1分别对应左边偏重和右边偏重，需要对应采取平衡措施
     */
    int getBalance(BinaryNode *t) const {
        return t == nullptr ? 0 : getHeight(t->left) - getHeight(t->right);
    }

    /**
     * @brief 核心部分：平衡树结构
     * @param t 平衡后的新局部根节点
     * @return
     */
    BinaryNode *balance(BinaryNode *t) {
        if (t == nullptr) return t;
        updateHeight(t);
        if (getBalance(t) > 1) {
            //左边偏重
            if (getBalance(t->left) < 0) {
                //左子树右边偏重，先拧到左边
                t->left = rotateLeft(t->left);
            }
            //右旋
            t = rotateRight(t);
        } else if (getBalance(t) < -1) {
            if (getBalance(t->right) > 0) {
                t->right = rotateRight(t->right);
            }
            t = rotateLeft(t);
        }
        return t;
    }

    /**
     * @param t 要旋转的局部根节点
     * @return 右旋后的新局部根节点
     */
    BinaryNode *rotateRight(BinaryNode *&t) {
        BinaryNode *newRoot = t->left;
        t->left = newRoot->right;
        newRoot->right = t;
        updateHeight(t);
        updateHeight(newRoot);
        if (t == root) {
            root = newRoot;
        }
        return newRoot;
    }

    /**
     * @param t 要旋转的局部根节点
     * @return 左旋后的新局部根节点
     */
    BinaryNode *rotateLeft(BinaryNode *&t) {
        BinaryNode *newRoot = t->right;
        t->right = newRoot->left;
        newRoot->left = t;
        updateHeight(t);
        updateHeight(newRoot);
        if (t == root) {
            root = newRoot;
        }
        return newRoot;
    }


    /**
     * @brief 递归克隆树的结构
     *
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};

