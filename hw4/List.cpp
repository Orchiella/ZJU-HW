#include "List.h"
#include <iostream>

template<typename T>
void showData(const List<T> &lst, const std::string &title, const std::string &expected, bool reversed = false) {
    std::cout << "[" << title << "]" << std::endl << "Expected:" << expected << std::endl << "Actual:  ";
    if (lst.empty()) {
        std::cout << "<empty>" << std::endl;
    } else {
        //这里在更新it时，自增、自减都用了后置符号，我知道后置的效率稍低，但后续我会给出这么做的缘由
        if (reversed)
            for (List<int>::const_iterator it = --lst.end(); it != --lst.begin(); it--)
                std::cout << *it << " ";
        else
            for (List<int>::const_iterator it = lst.begin(); it != lst.end(); it++)
                std::cout << *it << " ";
        std::cout << std::endl;
    }
}

int main() {
    //测试：初始化列表构造函数
    List<int> lst1{1, 2, 3};
    showData(lst1, "Initial lst1", "1 2 3");

    //测试：拷贝构造函数
    List<int> lst2 = lst1;
    showData(lst2, "Copy lst2 from lst1", "1 2 3");

    //测试：赋值运算符传递
    List<int> lst3;
    lst3 = lst2;
    showData(lst3, "Assign lst3 from lst2", "1 2 3");

    //测试：移动构造函数
    List<int> lst4 = std::move(lst3);
    showData(lst4, "Move lst4 from lst3", "1 2 3");
    showData(lst3, "Moved lst3", "<empty>");

    //测试：通过front()函数和back()函数获取头部和尾部数据
    std::cout << "[Retrieve data for head and tail]" << std::endl;
    std::cout << "Expected:1 3" << std::endl;
    std::cout << "Actual:  " << lst4.front() << " " << lst4.back() << std::endl;

    //测试：通过push_front函数在头部插入数据
    lst4.push_front(100);
    showData(lst4, "Insert data into the head of lst4", "100 1 2 3");

    //测试：通过push_back函数在头部插入数据
    lst4.push_back(2333);
    showData(lst4, "Insert data into the tail of lst4", "100 1 2 3 2333");

    //测试：通过pop_front函数移除头部数据
    lst4.pop_front();
    showData(lst4, "Remove data from the head of lst4", "1 2 3 2333");

    //测试：通过pop_back函数移除尾部数据
    lst4.pop_back();
    showData(lst4, "Remove data from the tail of lst4", "1 2 3");

    //测试：通过自增运算符移动一次迭代器指针，并通过insert函数插入数据
    List<int>::iterator it = lst4.begin();
    ++it;
    it = lst4.insert(it, 666);
    showData(lst4, "Insert data at the second pos of lst4", "1 666 2 3");

    //测试：通过erase函数刚插入的删除数据
    it = lst4.erase(it);
    showData(lst4, "Remove the data at the second pos of lst4", "1 2 3");

    /*
     * 直观验证：迭代器的前、后置自减操作
     * 因为后置操作函数使用了前置操作函数，所以前置操作的有效性蕴含在后置操作中
     * 而本类的showData函数用的都是后置操作，所以只要结果有效，即可同时证明前置操作的有效性
     * 对于加法，在前面的多次输出已验证，故现在只需要把showData的reversed参数设为true，观察结果是否符合预期（即逆序输出），即可验证前后置自减操作的有效性
    */
    showData(lst4, "Reversed lst4(Not actually modified)", "3 2 1", true);

    //测试：更新当前指向节点的数据（当前仍是第二个）
    lst4.update(it, 999);
    showData(lst4, "Update the data of the second pos of lst4", "1 999 3");

    //测试：查找元素，若存在，则返回首个匹配节点的迭代器，反之返回结尾哨兵节点迭代器。这里查找一个已知存在的元素
    List<int>::iterator _it = lst4.find(999);
    std::cout << "[Find existing data from lst4]" << std::endl;
    std::cout << "Expected:Found" << std::endl;
    std::cout << "Actual:  " << (_it == lst4.end() ? "Missed" : "Found") << std::endl;

    //测试：查找一个已知不存在的元素
    List<int>::iterator _it2 = lst4.find(0);
    std::cout << "[Find non-existing data from lst4]" << std::endl;
    std::cout << "Expected:Missed" << std::endl;
    std::cout << "Actual:  " << (_it2 == lst4.end() ? "Missed" : "Found") << std::endl;

    //测试：通过clear()函数清空所有数据
    lst4.clear();
    showData(lst4, "Clear lst4", "<empty>");

    //让窗口停留
    std::cin.get();
    return 0;
}
