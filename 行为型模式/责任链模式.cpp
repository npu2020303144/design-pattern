#include<iostream>
#include<string>
#include <vector>

using namespace std;

/*
 * 责任链模式：一种行为型设计模式
 * 构建一条对象链，将请求对象从一端进入，
 * 在链上依次处理，直到链上的某个对象能处理请求。
 * 在生活中很常见，就是一个逐层向上递交的过程，最终的请求要么被处理者所处理，要么处理不了，这也因此可能导致请求无法被处理。
 *
 * 组成结构：
 * 处理者Handler ：定义一个处理请求的接口，包含一个处理请求的抽象方法和一个指向下一个处理者的链接。
 * 具体处理者ConcreteHandler: 实现处理请求的方法，并判断能否处理请求，如果能够处理请求则进行处理，否则将请求传递给下一个处理者。
 * 客户端：创建并组装处理者对象链，并将请求发送到链上的第一个处理者。
 */

//处理者
class Handler{
public:
    virtual void request(const string& name, const int& days)=0;
    virtual ~Handler()=default;
};

//具体处理者
class Supervisor:public Handler{
private:
    static const int MAX_SUPERVISOR_HANDLE_DAYS = 3;
    Handler* nextHandler;
public:
    explicit Supervisor(Handler* nextHandler):nextHandler(nextHandler){}
    void request(const string& name, const int& days) override{
        if (days <= MAX_SUPERVISOR_HANDLE_DAYS) {
            cout << name << " Approved by Supervisor." << endl;
        } else if (nextHandler != nullptr) {
            nextHandler->request(name, days);
        } else {
            cout << name << " Denied by Supervisor." << endl;
        }
    }
    ~Supervisor() override =default;
};

class Manager:public Handler{
private:
    static const int MAX_MANAGER_HANDLE_DAYS = 7;
    Handler* nextHandler;
public:
    explicit Manager(Handler* nextHandler):nextHandler(nextHandler){}
    void request(const string& name, const int& days) override{
        if (days <= MAX_MANAGER_HANDLE_DAYS) {
            cout << name << " Approved by Manager." << endl;
        } else if (nextHandler != nullptr) {
            nextHandler->request(name, days);
        } else {
            cout << name << " Denied by Manager." << endl;
        }
    }
    ~Manager() override =default;
};

class Director:public Handler{
private:
    static const int MAX_DIRECTOR_HANDLE_DAYS = 10;
public:
    void request(const string& name, const int& days) override{
        if (days <= MAX_DIRECTOR_HANDLE_DAYS) {
            cout << name << " Approved by Director." << endl;
        } else {
            cout << name << " Denied by Director." << endl;
        }
    }
    ~ Director() override =default;
};

//请求对象
class Request{
private:
    string name;
    int days;
public:
    Request(const string& name, const int& days):name(name),days(days){}
    string getName() const{
        return this->name;
    }
    int getDays() const {
        return this->days;
    }
};


int main() {
    int quantity;
    cin >> quantity;
    Handler* director = new Director();
    Handler* manager = new Manager(director);
    Handler* supervisor = new Supervisor(manager);
    for (int i = 0; i < quantity; ++i) {
        string name;
        int days;
        cin>>name>>days;
        Request request(name, days);
        supervisor->request(name, days);
    }
    delete director;
    delete manager;
    delete supervisor;
    return 0;
}