#include <iostream>
#include <cstring>

class Chicken {
private:
    int age = 24;
    char *name = nullptr;

public:
    Chicken() {}

    Chicken(int _age) : age(_age) {}

    Chicken(int _age, const char *_name) : age(_age) {
        int len = strlen(_name) + 1;
        name = new char[len];
        for (int i = 0; i < len; i++)
            name[i] = _name[i];
    }

    //复制操作
    Chicken(const Chicken &source) : age(source.age) {
        if (source.name == nullptr) {
            name = nullptr;
            return;
        }
        int len = strlen(source.name) + 1;
        name = new char[len];
        for (int i = 0; i < len; i++)
            name[i] = source.name[i];
    }

    //赋值操作（重载）
    Chicken &operator=(const Chicken &source) {
        if (this != &source) {
            age = source.age;
            char *temp_name = nullptr;
            if (source.name != nullptr) {
                int len = strlen(source.name) + 1;
                temp_name = new char[len];
                for (int i = 0; i < len; i++)
                    temp_name[i] = source.name[i];
            }
            delete[] name;
            name = temp_name;
        }
        return *this;
    }

    ~Chicken() {
        if (name != nullptr)
            delete[] name;
    }

    void setAge(int _age) {
        age = _age;
    }

    //群里说参数如果属于本对象则会报错，所以我改了一下
    void setName(const char *_name) {
        if (name == _name) {
            //让同一地址的数据等于自己，没有实际意义，直接return掉，规避了c.setName(c.getName())的报错
            return;
        }
        char *temp_name;//这里也改了改，先给临时变量分配内存，确认分配并赋值好后再让name指向这个新的内存。上面的赋值操作也是如此
        int len = strlen(_name) + 1;
        temp_name = new char[len];
        for (int i = 0; i < len; i++)
            temp_name[i] = _name[i];
        delete[] name;
        name = temp_name;
    }

    const char *getName() const {
        return name;
    }

    const int &getAge() const {
        return age;
    }
};

//int main() {
//    //树枝666
//}