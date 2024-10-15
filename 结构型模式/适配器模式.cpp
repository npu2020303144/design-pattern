#include <iostream>
#include <string>
#include <utility>
#include <vector>

/*
 * 适配器模式：属于结构型设计模式，可将原来接口不兼容的能一起工作。
 *
 * 主要角色有：
 * 目标接口：客户希望使用的接口
 * 适配器类：实现客户应用的目标接口，拥有一个需要适配的类的实例
 * 被适配者：需要被适配的类
 *
 * 当使用一个已经存在的类，但是它的接口与你的代码不兼容时，可以使用适配器模式。
 * 在系统扩展阶段需要增加新的类时，并且类的接口和系统现有的类不一致时，可以使用适配器模式。
 * */

//客户希望使用的接口
class USB {
public:
    virtual void chargeWithUSB() = 0;

    virtual ~USB() = default;
};

class TypeC {
public:
    virtual void chargeWithTypeC() = 0;

    virtual ~TypeC() = default;
};

//适配器类
class USBAdapter : public USB {
public:
    void chargeWithUSB() override {
        std::cout << "USB Adapter" << std::endl;
    }
};

class Computer : public TypeC {
private:
    USBAdapter *adapter;
public:
    explicit Computer(USBAdapter *adapter) : adapter(adapter) {}

    void chargeWithTypeC() override {
        std::cout << "TypeC" << std::endl;
    }

    void chargeWithUSB() {
        adapter->chargeWithUSB();
    }
    ~Computer() override{
        delete adapter;
    }
};

int main() {
    int N;
    std::cin >> N;
    auto* computer=new Computer(new USBAdapter());
    for (int i = 0; i < N; ++i) {
        int type;
        std::cin >> type;
        try {
            if (type == 1) {
                computer->chargeWithTypeC();
            } else if (type == 2) {
                computer->chargeWithUSB();
            }else {
                throw std::invalid_argument("Invalid charging type: " + std::to_string(type));
            }
        }catch (const std::exception& e){
            //捕获try中抛出的错误，并将其打印
            std::cout<<"Error-"<<e.what()<<std::endl;
        }
    }
    delete computer;
    return 0;
}