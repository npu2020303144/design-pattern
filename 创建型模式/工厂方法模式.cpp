#include <iostream>
#include <vector>

/*
 * 工厂方法模式：属于创建型设计模式
 * 在简单工厂模式（将产品的创建过程封装在一个工厂类里）的基础上区分了抽象工厂和具体工厂，
 * 每个具体工厂生产一种产品，添加新产品只需添加新具体工厂类，无需修改原来的代码
 *
 * 主要有以下几个角色：
 * 抽象工厂：一个接口，包含一个抽象的工厂方法（用于创建产品对象）。
 * 具体工厂：实现抽象工厂接口，创建具体的产品。
 * 抽象产品：定义产品的接口。
 * 具体产品：实现抽象产品接口，是工厂创建的对象。
 * */

//抽象产品接口
class Prodcut{
public:
    virtual void show()=0;
    virtual ~Prodcut()=default;
};

//具体产品
class Circle:public Prodcut{
public:
    void show() override{
        std::cout<<"Circle Block"<<std::endl;
    }
};

class Square:public Prodcut{
public:
    void show() override{
        std::cout<<"Square Block"<<std::endl;
    }
};

//抽象工厂接口
class Factory{
public:
    virtual Prodcut* createProduct()=0;
    virtual ~Factory()=default;
};

//具体工厂接口
class CircleFactory:public Factory{
public:
    Prodcut* createProduct() override{
        return new Circle();
    }
};

class SquareFactory:public Factory{
public:
    Prodcut* createProduct() override{
        return new Square();
    }
};


int main(){
    int N;
    std::cin>>N;
    for (int i = 0; i < N; ++i) {
        std::string line;
        int quantity;
        std::cin>>line>>quantity;
        Factory* factory = nullptr;
        Prodcut* product = nullptr;
        if (line=="Circle") {
            for (int j = 0; j < quantity; ++j) {
                factory = new CircleFactory();
                product = factory->createProduct();
                product->show();
            }
        }else if (line=="Square"){
            for (int j = 0; j < quantity; ++j) {
                factory = new SquareFactory();
                product = factory->createProduct();
                product->show();
            }
        }
        delete factory;
        delete product;
    }
    return 0;
}