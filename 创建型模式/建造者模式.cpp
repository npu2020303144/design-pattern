#include <iostream>
#include <string>

/*
 * 建造者模式：属于创建型模式，将对象的构建过程分为多个步骤，并未每个步骤定义抽象接口，
 * 由一个指导者协调建造者们的工作，按一定次序生成产品。
 *
 * 主要角色有：
 * 产品：被构建的复杂对象, 包含多个组成部分。
 * 抽象建造者：定义构建产品各个部分的抽象接口和一个返回复杂产品的方法getResult。
 * 具体建造者：实现抽象建造者接口，构建产品的各个组成部分，并提供一个方法返回最终的产品。
 * 指导者：调用具体建造者的方法，按照一定的顺序或逻辑来构建产品。
 * */

//产品
class Bike{
public:
    std::string frame;
    std::string tires;

    void setFrame(const std::string& frame){
        this->frame=frame;
    }
    void setTires(const std::string& tires){
        this->tires=tires;
    }
    friend std::ostream& operator<<(std::ostream& output, const Bike& bike){
        output<<bike.frame<<" "<<bike.tires;
        return output;
    }
};

//抽象建造者
class Builder{
public:
    virtual void build()=0;
    virtual Bike getResult()=0;
    virtual ~Builder()=default;
};

//具体建造者
class MountainBuilder:public Builder{
private:
    Bike bike;
public:
    void build() override{
        bike.setFrame("Aluminum Frame");
        bike.setTires("Knobby Tires");
    }
    Bike getResult() override{
        return this->bike;
    }
};
class RoadBuilder:public Builder{
private:
    Bike bike;
public:
    void build() override{
        bike.setFrame("Carbon Frame");
        bike.setTires("Slim Tires");
    }
    Bike getResult() override{
        return this->bike;
    }
};

//指导者
class Director{
public:
    static Bike construct(Builder& builder){
        builder.build();
        return builder.getResult();
    }
};

int main(){
    int N;
    std::cin>>N;
    for (int i = 0; i < N; ++i) {
        std::string type;
        std::cin>>type;
        Builder* builder;
        if (type == "mountain") {
            builder = new MountainBuilder();
        } else {
            builder = new RoadBuilder();
        }
        Bike bike=Director::construct(*builder);
        std::cout<<bike<<std::endl;
        delete builder;
    }
    return 0;
}