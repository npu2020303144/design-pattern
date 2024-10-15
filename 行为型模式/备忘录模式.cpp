#include<iostream>
#include<vector>
#include<string>
#include<stack>

using namespace std;

/*
备忘录模式：属于行为型模式，可在不暴露对象实现的情况下，
让外界捕获对象的内部状态并在对象外保存，以便稍后还原到先前状态。

分为三部分：
发起人Originator： 需要还原状态的那个对象，负责创建一个“备忘录”，并使用备忘录记录当前时刻的内部状态。
备忘录Memento: 存储发起人对象的内部状态，包含发起人的部分或全部状态信息，但对外部不可见，只有发起人能访问备忘录对象状态。
管理者Caretaker: 负责存储备忘录对象，但并不了解其内部结构，管理者可以存储多个备忘录对象。
*/

//备忘录
class Memento{
private:
    int value;
public:
    explicit Memento(int value):value(value){}
    int getValue() const{
        return this->value;
    }
};

//发起人
class Counter{
private:
    int value=0;
    stack<Memento> undoStack;
    stack<Memento> redoStack;
public:
    int getValue() const{
        return this->value;
    }
    void addValue(){
        this->redoStack=stack<Memento>();//清空redoStack
        this->undoStack.push(Memento(this->value));
        ++this->value;
    }
    void subValue(){
        this->redoStack=stack<Memento>();//清空redoStack
        this->undoStack.push(Memento(this->value));
        --this->value;
    }
    //撤销操作
    void undo(){
        if(!this->undoStack.empty()){
            this->redoStack.push(Memento(this->value));
            this->value=this->undoStack.top().getValue();
            this->undoStack.pop();
        }
    }
    //重做操作
    void redo(){
        if(!this->redoStack.empty()){
            this->undoStack.push(Memento(this->value));
            this->value=this->redoStack.top().getValue();
            this->redoStack.pop();
        }
    }
};

int main(){
    string operation;
    Counter counter;
    while(cin>>operation){
        if(operation=="Increment"){
            counter.addValue();
        }else if(operation=="Decrement"){
            counter.subValue();
        }else if (operation=="Undo"){
            counter.undo();
        }else if(operation=="Redo"){
            counter.redo();
        }
        cout<<counter.getValue()<<endl;
    }

    return 0;
}