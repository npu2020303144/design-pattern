#include<iostream>
#include<string>
#include <memory>

using namespace std;

/*
模板方法模式：属于行为型模式，使得子类可以在不改变算法结构的情况下，重新定义算法中的某些步骤。

举个简单的例子，做一道菜通常都需要包含至少三步：
准备食材
亨饪过程
上菜

不同菜品的亨饪过程是不一样的，但可先定义一个”骨架”，包含这三个步骤，
亨饪过程的过程放到具体的炒菜类中去实现，无论炒什么菜，都可以沿用相同的炒菜算法，只需在子类中实现具体的炒菜步骤，从而提高了代码的复用性。

分为两部分：
模板类AbstractClass：由一个模板方法和若干个基本方法构成，模板方法定义了逻辑的骨架，
基本方法通常是一些抽象方法，由子类去实现。还可包含一些具体方法，是算法的一部分且已有默认实现，在具体子类中可继承或者重写。
具体类ConcreteClass：继承自模板类，实现了在模板类中定义的抽象方法，以完成算法中特定步骤的具体实现。
*/

class CoffeeMakeSystem{
private:
    string coffeeName;
public:
    explicit CoffeeMakeSystem(const string& coffeeName):coffeeName(coffeeName){}

    virtual void grindCoffeeBeans()=0;
    virtual void brewCoffee()=0;

    //默认添加的调料
    virtual void addCondiments(){
        cout<<"Adding condiments"<<endl;
    }

    //模板方法定义咖啡制作的全过程
    virtual void makeCoffee(){
        cout<<"Making "<< this->coffeeName<<":"<<endl;
        grindCoffeeBeans();
        brewCoffee();
        addCondiments();
        cout<<endl;
    }

    virtual ~CoffeeMakeSystem()=default;
};

class AmericanCoffee:public CoffeeMakeSystem{
public:
    AmericanCoffee(): CoffeeMakeSystem("American Coffee"){}
    void grindCoffeeBeans() override {
        cout << "Grinding coffee beans"<<endl;
    }
    void brewCoffee() override {
        cout << "Brewing coffee"<<endl;
    }
};

class LatteCoffeeMaker : public CoffeeMakeSystem {
public:
    // 构造函数传递咖啡名称
    LatteCoffeeMaker() : CoffeeMakeSystem("Latte") {}

    void grindCoffeeBeans() override {
        cout << "Grinding coffee beans"<<endl;
    }

    void brewCoffee() override {
        cout << "Brewing coffee"<<endl;
    }

    // 添加调料的特定实现
    void addCondiments() override {
        cout << "Adding milk"<<endl;
        cout << "Adding condiments"<<endl;
    }
};


int main() {
    int coffeeType;
    unique_ptr<CoffeeMakeSystem> coffeemaker;
    while (cin>>coffeeType){
        if (coffeeType==1){
            coffeemaker = make_unique<AmericanCoffee>();
        }else if (coffeeType==2){
            coffeemaker = make_unique<LatteCoffeeMaker>();
        }else{
            cout<<"Invalid coffee type"<<endl;
            continue;
        }
        coffeemaker->makeCoffee();
    }
    return 0;
}