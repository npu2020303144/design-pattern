#include<iostream>
#include<string>
#include <vector>

using namespace std;

/*状态模式：一种行为型设计模式
 * 一个对象在不同的状态下有不同的行为，
 * 状态模式将每个状态的行为封装在一个具体状态类中，使得每个状态类相对独立，
 * 并将对象在不同状态下的行为进行委托，从而使得对象的状态可以在运行时动态改变，
 *
 * 状态模式包括以下几个重要角色：
 * State（状态）： 定义一个接口，用于封装与Context的一个特定状态相关的行为。
 * ConcreteState（具体状态）： 负责处理Context在状态改变时的行为, 每一个具体状态子类实现一个与Context的某个状态的相关行为。
 * Context（上下文）: 维护一个具体状态子类的实例，这个实例定义当前的状态。
*/

//状态接口
class State{
public:
    virtual void operation()=0;
    virtual ~State()=default;
};

//具体状态
class OnState:public State{
public:
    void operation() override{
        cout<< "Light is ON"<<endl;
    }
};
class OffState:public State{
public:
    void operation() override{
        cout<< "Light is OFF"<<endl;
    }
};
class BlinkState:public State{
public:
    void operation() override{
        cout<< "Light is Blinking"<<endl;
    }
};

//上下文类
class Light{
private:
    State* currentState;
public:
    Light():currentState(new OffState()){}//台灯初始状态是关闭的
    void operate(State* newState){
        delete this->currentState;
        this->currentState=newState;
        this->currentState->operation();
    }
//    void operate(){
//        this->currentState->operation();
//    }

    ~Light(){
        delete currentState;
    }
};

int main() {
    int quantity;
    cin >> quantity;
    Light light;
    while (quantity--) {
        string order;
        cin>>order;
        if (order=="ON"){
            light.operate(new OnState());
        }else if (order=="OFF"){
            light.operate(new OffState());
        }else if(order=="BLINK"){
            light.operate(new BlinkState());
        }else {
            cout<<"Invalid command:"<<order<<endl;
        }
    }
    return 0;
}