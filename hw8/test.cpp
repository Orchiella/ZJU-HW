#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "HeapSort.h"

/**
 * 验证是否升序，判据就是遍历过程中发现了减小的变动
 * @tparam T 泛型
 * @param vec 容器
 * @return 是否升序
 */
template<typename T>
bool verify(const std::vector<T> &vec) {
    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) {
            return false;
        }
    }
    return true;
}

/**
 * 生成随机序列
 * @param size
 * @return
 */
std::vector<int> getRandomVec(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i)
        vec[i] = rand();
    return vec;
}

/**
 * 生成有序序列(0,...,size-1)或其反
 * @param size
 * @param reverse 是否降序
 * @return
 */
std::vector<int> getOrderedVec(int size, bool reverse = false) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i)
        vec[i] = reverse ? size - i - 1 : i;
    return vec;
}

/**
 * 生成一定含有重复元素的序列
 * @param size 这里保证大于10000
 * @return
 */
std::vector<int> getRepetitiveVec(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i)
        vec[i] = i > 10000 ? i : i % 100;
    return vec;
}

/**
 * 实例测试函数
 * @tparam T 泛型
 * @param vec1 传给mySort的容器
 * @param vec2 传给std::sort_heap的容器
 * @param caseName 实例名称
 */
template<typename T>
void testCase(std::vector<T> vec1, std::vector<T> vec2, const std::string &caseName) {
    std::cout << "Test the case of " << caseName << ":" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    mySort(vec1);
    auto end = std::chrono::high_resolution_clock::now();
    if (!verify(vec1)) {
        std::cout << "Incorrect sorting occurred!" << std::endl;
    }
    std::chrono::duration<double> duration = end - start;
    std::cout << "mySort() Time:" << duration.count() << "s     |     ";

    std::make_heap(vec2.begin(), vec2.end());
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(vec2.begin(), vec2.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "std::sort_heap() Time:" << duration.count() << "s" << std::endl << std::endl;
}

void testMySort() {
    //随机序列情形
    std::vector<int> randomVec1 = getRandomVec(1000000);
    std::vector<int> randomVec2 = getRandomVec(1000000);
    testCase(randomVec1, randomVec2, "RANDOM");

    //升序序列情形
    std::vector<int> orderedVec1 = getOrderedVec(1000000);
    std::vector<int> orderedVec2 = getOrderedVec(1000000);
    testCase(orderedVec1, orderedVec2, "ORDERED");

    //降序序列情形
    std::vector<int> reverseVec1 = getOrderedVec(1000000, true);
    std::vector<int> reverseVec2 = getOrderedVec(1000000, true);
    testCase(reverseVec1, reverseVec2, "REVERSE");

    //部分重复序列情形
    std::vector<int> repetitiveVec1 = getRepetitiveVec(1000000);
    std::vector<int> repetitiveVec2 = getRepetitiveVec(1000000);
    testCase(repetitiveVec1, repetitiveVec2, "REPETITIVE");
}

int main() {
    testMySort();
    return 0;
}
