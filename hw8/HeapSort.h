#include <vector>
#include <algorithm>

/**
 * 对传入的容器执行堆排序操作，过程全部由STL提供的函数实现
 * @tparam T 泛型
 * @param vec 传入的容器
 */
template<typename T>
void mySort(std::vector<T> &vec) {
    std::make_heap(vec.begin(), vec.end());//构建堆结构
    for (auto it = vec.end(); it != vec.begin(); --it) {
        /*
         * 原理：局部尾指针从全局尾指针开始，每次遍历通过pop_heap将堆顶元素（最大元）移到局部的尾部（并随之自动恢复堆性），并将局部尾指针前移一位
         * 重复操作，直到碰到头指针，这样就得到了升序
        */
        std::pop_heap(vec.begin(), it);
    }
}
