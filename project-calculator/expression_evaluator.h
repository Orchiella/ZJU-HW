#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <iostream>

class ExpressionEvaluator {
public:
    static double eval(const std::string &enter) {
        return evalTranslation(translate(enter));
    }

private:
    //获取运算符优先级
    static int getPrecedence(char op) {
        switch (op) {
            case '*':
            case '/':
                return 2;
            case '+':
            case '-':
                return 1;
            default:
                return 0;
        }
    }

    //执行二元基本运算
    static double calculate(double a, double b, char op) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                if (b == 0) throw std::runtime_error("Error: Division by zero");
                return a / b;
            default:
                return 0;
        }
    }

    //识别运算符
    static bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    //将人类阅读的中缀表达式翻译成便于机器阅读的后缀表达式
    static std::string translate(const std::string &enter) {
        std::ostringstream output;
        std::stack<char> operators;
        bool operandExpected = true;//用于指示下一个是否必须读取一个数字或前括号
        for (size_t i = 0; i < enter.length(); ++i) {
            char c = enter[i];
            if (std::isspace(c)) continue;
            if (!std::isdigit(c) && !isOperator(c) && c != '(' && c != ')' && c != '.' && c != 'e')
                throw std::runtime_error("Error: Invalid character found");

            //处理常规数字和以负号开头的数字
            if (std::isdigit(c) || c == '.' || (c == '-' && operandExpected)) {
                output << c;
                //只要遇到数字表达相关的字符，就继续读取
                while (i + 1 < enter.length() &&
                       (std::isdigit(enter[i + 1]) || enter[i + 1] == '.' || enter[i + 1] == 'e')) {
                    output << enter[++i];
                    //处理科学计数法表达式，即读到e后一连下去读完
                    if (enter[i] == 'e') {
                        output << enter[++i];
                        //如果e后面紧挨着的是运算符，则再向后读取一位（数字）
                        if (enter[i] == '+' || enter[i] == '-') {
                            output << enter[++i];
                        }
                    }
                }
                output << ' ';
                operandExpected = false;
            } else {
                if (output.str().back() != ' ') output << ' ';

                if (c == '(') {
                    //当前发现左括号，先加入栈中，方便后续右括号匹配
                    operators.push(c);
                    operandExpected = true;
                } else if (c == ')') {
                    //发现右括号，从栈顶向下遍历直到找到匹配的左括号，期间按遍历顺序把运算符加入到后缀表达式中
                    while (!operators.empty() && operators.top() != '(') {
                        output << operators.top() << ' ';
                        operators.pop();
                    }
                    if (operators.empty()) {
                        //如果把栈弹完了，说明始终没找到左括号，表达式非法
                        throw std::runtime_error("Error: Where is your left parenthesis??");
                    }
                    operators.pop();//弹出左括号
                    operandExpected = false;
                } else if (isOperator(c)) {
                    //当字符是运算符时，弹出运算符并加进表达式，直到遇到比自己低级的运算符
                    while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(c)) {
                        output << operators.top() << ' ';
                        operators.pop();
                    }
                    operators.push(c);
                    operandExpected = true;//指示下一个字符必须是数字或左括号
                }
            }
        }

        //依次弹出剩下的所有低级运算符
        while (!operators.empty()) {
            if (operators.top() == '('){
                //发现有未匹配过的左括号，
                throw std::runtime_error("Error: Where is your right parenthesis??");
            }
            output << operators.top() << ' ';
            operators.pop();
        }

        return output.str();
    }

    //计算后缀表达式
    static double evalTranslation(const std::string &translation) {
        std::stack<double> operands;
        std::istringstream input(translation);
        std::string token;

        while (input >> token) {
            if (std::isdigit(token[0]) || token[0] == '.' || (token[0] == '-' && token.size() > 1)) {
                //为数字（包括小数、负数、科学计数法表示的数）时，交给C++自带的stod函数来处理
                operands.push(std::stod(token));
            } else if (isOperator(token[0]) && token.size() == 1) {
                if (operands.size() == 1) {
                    //发现了单独存在的运算符，说明后缀表达式错了
                    throw std::runtime_error("Error: Isolated operator");
                }
                //弹出两个运算数执行二元基本计算，再作为结果重新入栈
                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();
                operands.push(calculate(a, b, token[0]));
            }
        }
        if (operands.size() != 1) {
            throw std::runtime_error("Error: No result?");
        }
        return operands.top();
    }
};
