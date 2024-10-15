#include<iostream>
#include<vector>
#include <string>

using namespace std;

/* 命令模式：属于行为型模式，将请求封装为一个命令对象，
 * 将其存在队列中，然后再逐一调用，这些命令可撤销或重做。

 * 分为：
 * 命令接口Command：抽象类，定义执行操作的接口。
 * 具体命令类ConcreteCommand: 实现命令接口，在调用execute方法时使“接收者对象”根据命令完成具体任务，比如遥控器中的“开机”，“关机”命令。
 * 接收者类Receiver: 接受并执行命令的对象，可以是任何对象，遥控器可以控制空调，也可以控制电视机，电视机和空调负责执行具体操作，是接收者。
 * 调用者类Invoker: 发起请求的对象，有一个将命令作为参数传递的方法。它不关心命令的具体实现，只负责调用命令对象的 execute() 方法来传递请求。
 */

//接收者类
class FoodMaker{
public:
    void makeFood(const string& dishName){
        cout<<dishName<<" is ready!"<<endl;
    }
};

//命令接口
class Command {
public:
    virtual void execute() = 0;

    virtual ~Command() = default;
};

// 具体命令类
class OrderFood : public Command {
private:
    string dishName;
    FoodMaker* receiver;//命令接收者
public:
    explicit OrderFood(const string& dishName, FoodMaker* receiver):dishName(dishName), receiver(receiver){}

    void execute() override{
        receiver->makeFood(this->dishName);
    }
};

//调用者类（点餐机）
class OrderMachine{
private:
    Command* command;
public:
    void setCommand(Command* command){
        this->command=command;
    }

    void executeOrder(){
        this->command->execute();
    }
};

int main() {
    int N;
    cin >> N;
    vector<string> dishes(N);
    FoodMaker foodMaker;
    while (N--) {
        string dish;
        cin >> dish;
        Command* command = new OrderFood(dish, &foodMaker);
        OrderMachine orderMachine{};
        orderMachine.setCommand(command);
        orderMachine.executeOrder();
        delete command;
    }
    return 0;
}