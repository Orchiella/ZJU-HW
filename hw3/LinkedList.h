#include <initializer_list>
#include <iostream>

template<typename T>
class SingleLinkedList {
private:
    class Node {
    private:
        T data;
        Node *next = nullptr;

        Node(T _val) { data = _val; }

        friend class SingleLinkedList<T>;
    };

    Node *head = nullptr;
    int size = 0;
    Node *currentPos = nullptr;

    void _emptyList();

    void _copy(const SingleLinkedList<T> &_l);

public:
    /// 返回当前位置的值
    T getCurrentVal() const;

    /// 设置当前位置的值
    void setCurrentVal(const T &_val);

    /// 如果链表为空，返回 true；否则返回 false。
    // 代码刚下载到IDE时函数名有typo，已更正
    bool isEmpty() const;

    int getSize() const;

    void emptyList();

    bool find(const T &_val);

    SingleLinkedList() {};

    ~SingleLinkedList();

    SingleLinkedList(std::initializer_list<T> _l);

    void printList() const;

    SingleLinkedList(const SingleLinkedList<T> &_l);

    SingleLinkedList<T> &operator=(const SingleLinkedList<T> &_l);

    /// 在 currentPos 后面插入一个元素，数据为 _val
    void insert(T _val);

    /// 如果找到，返回 ture, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    bool find(const T &_val) const;

    /// 删除 currentPos 后面的元素
    void remove();

    /// 删除 currentPos 的数据
    void removeCurrent();
};

//作业：获取当前节点的数据
template<typename T>
T SingleLinkedList<T>::getCurrentVal() const {
    if (currentPos == nullptr) {
        //判空并抛出异常
        throw std::invalid_argument("Empty current position! Can't get value!");
    }
    return currentPos->data;
}

//作业：设置当前节点的值
template<typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val) {
    if (currentPos == nullptr) {
        //判空并抛出异常
        throw std::invalid_argument("Empty current position! Can't set value!");
    }
    currentPos->data = _val;
}

//作业：判断链表是否为空
template<typename T>
bool SingleLinkedList<T>::isEmpty() const {
    return size == 0;
}

//作业：插入数据
template<typename T>
void SingleLinkedList<T>::insert(T _val) {
    Node *newNode = new Node(_val);
    if (head == nullptr) {
        head = newNode;
        currentPos = newNode;
    } else {
        Node *originalNext = currentPos->next;
        currentPos->next = newNode;
        newNode->next = originalNext;
        currentPos = newNode; //将currentPos更新为新插入的节点
    }
    ++size;
}

//作业：删除当前节点的下一节点的数据
template<typename T>
void SingleLinkedList<T>::remove() {
    if (currentPos == nullptr || size == 0) {
        //判空，但没让抛出异常就直接return掉
        return;
    }
    if (size == 1) {
        delete head;
        head = nullptr;
        currentPos = nullptr;
    } else {
        Node *next_p = currentPos->next;
        if (next_p == nullptr) {
            //如果当前节点就是末尾了，直接return掉
            return;
        }
        currentPos->next = next_p->next;
        delete next_p;
        //对于这种类型的remove，currentPos没必要更新
    }
    --size;
}

/*
 * 作业（选做）：删除当前节点的数据
 * 这个事情对于单向链表来说其实是相对不容易的，因为我们手上的currentPos只包含下一节点的信息，而不包含上一节点的信息。（这时候双向链表的优势就出来了）
 * 所以如果currentPos前头还有节点，那么删除currentPos后，我们是没法直接让currentPos前一节点连上currentPos后一节点的
 * 要实现删除当前节点的功能，得从头开始遍历，并且确保遍历到currentPos时手握其上一节点，便于删除后的节点重连
 * 我已测试过本函数，助教可以参考我写的测试代码
 *
    SingleLinkedList<double> c4{1, 2, 3, 4};
    std::cout << "The complete single linked list:" << std::endl;
    c4.printList();
    std::cout << "Test for removing the middle, head, and tail nodes of the single linked list separately:"
              << std::endl;
    c4.find(2);
    c4.removeCurrent();
    c4.printList();
    c4.find(1);
    c4.removeCurrent();
    c4.printList();
    c4.find(4);
    c4.removeCurrent();
    c4.printList();
    c4.find(3);
    c4.removeCurrent();
    std::cout << "Is list empty after removing the only node:" << std::endl;
    std::cout << (c4.isEmpty() ? "Yes" : "No") << std::endl;
*/
template<typename T>
void SingleLinkedList<T>::removeCurrent() {
    if (currentPos == nullptr || size == 0) {
        return;
    }
    if (currentPos == head) {
        //如果当前是头节点，不用考虑节点重连问题
        Node *temp = head;
        head = head->next;
        delete temp;
        currentPos = head;
    } else {
        //如果当前节点不在头部，则需要考虑节点重连问题，也就是遍历过程中要时刻手握当前节点与其上一节点
        Node *prev = head;
        while (prev->next != currentPos) {
            prev = prev->next;
        }
        prev->next = currentPos->next;
        delete currentPos;
        currentPos = prev->next;  //让删除位置的下一个节点顶替原先的currentPos，当然这时候有可能为nullptr了，这种情况下是否要多写一步让current设为prev本身取决于业务要求，这里无妨
    }
    --size;
}

template<typename T>
bool SingleLinkedList<T>::find(const T &_val) {
    Node *p = head;
    while (p != nullptr) {
        if (p->data == _val) {
            currentPos = p;
            return true;
        }
        p = p->next;
    }
    return false;
}

//非作业：带const修饰符的find函数。用于纯粹地判断数据存在性，而不改变currentPos。我看下载下来的代码没写，我给补充一下
template<typename T>
bool SingleLinkedList<T>::find(const T &_val) const {
    const Node *p = head;
    while (p != nullptr) {
        if (p->data == _val) {
            return true;
        }
        p = p->next;
    }
    return false;
}

template<typename T>
int SingleLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l) {
    for (auto i = _l.begin(); i != _l.end(); ++i) {
        Node *newNode = new Node(*i);
        if (head == nullptr) {
            head = newNode;
            currentPos = head;
        } else {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template<typename T>
void SingleLinkedList<T>::_emptyList() {
    Node *p = head;
    while (p != nullptr) {
        Node *t = p;
        p = p->next;
        delete t;
    }
}

template<typename T>
void SingleLinkedList<T>::printList() const {
    Node *p = head;
    while (p != nullptr) {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;
}

template<typename T>
SingleLinkedList<T>::~SingleLinkedList() {
    _emptyList();
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l) {
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList() {
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l) {
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template<typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l) {
    Node *p = _l.head;
    while (p != nullptr) {
        Node *newNode = new Node(p->data);
        if (head == nullptr) {
            head = newNode;
            currentPos = head;
        } else {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}