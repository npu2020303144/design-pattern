#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <iterator>
#include <regex>


/*
 * 解释器模式：属于行为型设计模式
 * 它定义了一个语言的文法，并且建立一个[解释器]来解释该语言中的句子
 *
 * 主要包含以下几个角色：
 * 抽象表达式（Abstract Expression）： 定义了解释器的接口，包含了解释器的方法interpret。
 * 终结符表达式（Terminal Expression）： 在语法中为最小单元的符号。
 * 非终结符表达式（Non-terminal Expression）： 文法中的复杂表达式，由终结符和其他非终结符组成。
 * 上下文（Context）： 包含解释器之外的一些全局信息，可存储解释器中间结果，也可向解释器传递信息。
 * */

//抽象表达式类
class Expression{
public:
    virtual int interpret()=0;
    virtual ~Expression()=default;
};

//终结符表达式--数字
class NumberExpression:public Expression{
private:
    int value;
public:
    explicit NumberExpression(int val):value(val){}

    int interpret() override{
        return this->value;
    }
};

//非终结符表达式类--运算符号类（又分加法和乘法）
class AddExpression:public Expression{
private:
    Expression* left;
    Expression* right;
public:
    explicit  AddExpression(Expression* l, Expression* r):left(l),right(r){}

    int interpret() override{
        return this->left->interpret()+this->right->interpret();
    }
};

//非终结符表达式类
class MultiplyExpression:public Expression{
private:
    Expression* left;
    Expression* right;
public:
    explicit  MultiplyExpression(Expression* l, Expression* r):left(l),right(r){}

    int interpret() override{
        return this->left->interpret()* this->right->interpret();
    }
};

//非终结符表达式类--操作符类（包括运算符与数字）
class OperatorExpression:public Expression{
private:
    std::string oper;
public:
    explicit OperatorExpression(const std::string& op):oper(op){}

    int interpret() override{
        throw std::runtime_error("OperationExpression does not support interpretation");
    }

    std::string getOperator() const{
        return this->oper;
    }
};

//解析表达式字符串
int parseExpression(const std::string& expressionStr){
    //istringstream:获取当前输入字符串流，并自动根据空格分割出各个非空格字符串元素
    std::istringstream iss(expressionStr);
    
    //istream_iterator:迭代器类，对分出的非空格元素使用迭代器遍历访问，将其装入vector<string>容器中
    std::vector<std::string> elements(std::istream_iterator<std::string>{iss},
                                      std::istream_iterator<std::string>());
    std::stack<Expression*> st;
    for (const auto& element: elements) {
        if (std::regex_match(element, std::regex("\\d+"))){
            //regex():正则表达式构造函数；regex_match(str,匹配规则)
            st.push(new NumberExpression(std::stoi(element)));//stoi(str)字符串转int型函数
        } else if(element=="+"||element=="*"){
            st.push(new OperatorExpression(element));
        } else {
            throw std::invalid_argument("Invalid element in expression: "+ element);
        }
    }
    while(st.size()>1){
        Expression* right = st.top();
        st.pop();
        Expression* operatorExp = st.top();
        st.pop();
        Expression* left = st.top();
        st.pop();
        if (auto* opExp=dynamic_cast<OperatorExpression*>(operatorExp)){
            std::string op = opExp->getOperator();
            if (op=="+"){
                st.push(new AddExpression(left, right));
            }else if(op=="*"){
                st.push(new MultiplyExpression(left, right));
            } else{
                throw std::invalid_argument("Invalid operator type in expression");
            }
        }
    }
    int result = st.top()->interpret();
    delete st.top();
    return result;
}

int main(){
    std::vector<std::string> inputLines;
    std::string line;
    //getline(cin, line):获取cin中一行的输入
    while (std::getline(std::cin, line)&&!line.empty()){
        inputLines.emplace_back(line);
    }
    for (const auto & inputLine : inputLines){
        try {
            int result= parseExpression(inputLine);
            std::cout<<result<<std::endl;
        }catch (const std::exception& e){
            //捕获try中抛出的错误，并将其打印
            std::cout<<"Error-"<<e.what()<<std::endl;
        }
    }
    return 0;
}