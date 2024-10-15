#include <iostream>

/*
 * 抽象工厂模式：属于创建型模式
 * 每个工厂可以创建多种相关的产品，而不只是一种产品。
 *
 * 主要角色为：
 * 抽象产品接口：定义产品的接口，可以定义多个抽象产品接口，比如说沙发、椅子、茶几都是抽象产品。
 * 具体产品类：实现抽象产品接口，产品的具体实现，古典风格和沙发和现代风格的沙发都是具体产品。
 * 抽象工厂接口：声明一组用于创建产品的方法，每个方法对应一个产品。
 * 具体工厂类：实现抽象工厂接口，负责创建一组具体产品的对象，生产古典风格的工厂和生产现代风格的工厂都是具体实例。
 * */

class Sofa{
public:
    virtual void showSofa()=0;
    virtual ~Sofa()=default;
};
class Chair{
public:
    virtual void showChair()=0;
    virtual ~Chair()=default;
};

class ModernSofa:public Sofa{
public:
    void showSofa() override{
        std::cout<<"modern sofa"<<std::endl;
    }
};
class ClassicalSofa:public Sofa{
public:
    void showSofa() override{
        std::cout<<"classical sofa"<<std::endl;
    }
};

class ModernChair:public Chair{
public:
    void showChair() override{
        std::cout<<"modern chair"<<std::endl;
    }
};
class ClassicalChair:public Chair{
public:
    void showChair() override{
        std::cout<<"classical chair"<<std::endl;
    }
};

//抽象工厂接口
class Factory{
public:
    virtual Chair* createChair()=0;
    virtual Sofa* createSofa()=0;
    virtual ~Factory()=default;
};

class ModernFactory:public Factory{
public:
    Chair * createChair() override{
        return new ModernChair();
    }
    Sofa * createSofa() override{
        return new ModernSofa();
    }
};
class ClassicalFactory:public Factory{
public:
    Sofa* createSofa() override{
        return new ClassicalSofa();
    }
    Chair* createChair() override{
        return new ClassicalChair();
    }
};

int main(){
    int N;
    std::cin>>N;
    Factory* factory;
    for (int i = 0; i < N; ++i) {
        std::string type;
        std::cin>>type;
        if (type=="modern"){
            factory=new ModernFactory();
        }else if (type=="classical"){
            factory=new ClassicalFactory();
        }else{
            throw std::invalid_argument("Invalid furniture type: "+type);
        }
        Chair* chair= factory->createChair();
        Sofa* sofa=factory->createSofa();
        chair->showChair();
        sofa->showSofa();
        delete factory;
        delete chair;
        delete sofa;
    }
    return 0;
}