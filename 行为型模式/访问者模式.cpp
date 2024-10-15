#include <iostream>
#include <vector>
#include <cmath>

/*
 * 访问者模式：属于行为型设计模式
 * 在不改变对象结构的前提下，对对象中的元素进行新的操作。
 *
 * 主要包含以下几个角色：
 * 抽象访问者（Visitor）： 声明了访问者可以访问哪些元素，以及如何访问它们的方法visit。
 * 具体访问者（ConcreteVisitor）： 实现了抽象访问者定义的方法，不同的元素类型可能有不同的访问行为。
 * 抽象元素（Element）： 定义了一个accept方法，用于接受访问者的访问
 * 具体元素（ConcreteElement）： 实现了accept方法，是访问者访问的目标。
 * 对象结构（Object Structure）： 包含元素的集合，可以是一个列表、一个集合或者其他数据结构。负责遍历元素，并调用元素的接受方法。
 *
 *
 * 访问者模式将同一类操作封装在一个访问者中，使得相关的操作彼此集中。
 * 常用于对象结构比较稳定，但经常需要在此对象结构上定义新操作的情况，因此无需修改现有的元素类，只需要定义新的访问者来添加新的操作。
 * */

//访问者接口
class Visitor{
public:
    virtual void visit(class Circle& circle)=0;
    virtual void visit(class Rectangle& rectangle)=0;
};

//元素接口
class Shape{
public:
    virtual void accept(Visitor& visitor)=0;
    virtual ~Shape()=default;
};

//具体元素类
class Circle:public Shape{
private:
    int radius;
public:
    explicit Circle(int rad):radius(rad){}
    int getRadius() const{
        return this->radius;
    }
    void accept(Visitor &visitor) override{
        visitor.visit(*this);
    }
};
class Rectangle:public Shape{
private:
    int width;
    int height;
public:
    explicit Rectangle(int wid, int hei):width(wid), height(hei){}
    int getWidth() const{
        return this->width;
    }
    int getHeight() const{
        return this->height;
    }
    void accept(Visitor &visitor) override{
        visitor.visit(*this);
    }
};

//具体访问者类
class AreaCalculator:public Visitor{
public:
    void visit(class Circle &circle) override{
        double area = 3.14*std::pow(circle.getRadius(),2);
        std::cout<<area<<std::endl;
    }
    void visit(class Rectangle &rectangle) override{
        int area = rectangle.getHeight()*rectangle.getWidth();
        std::cout<<area<<std::endl;
    }
};

//对象结构类
class Drwaing{
private:
    std::vector<Shape*> shapes;
public:
    explicit Drwaing(const std::vector<Shape*>& shapes):shapes(shapes){}

    void accept(Visitor& visitor){
        for (auto* shape:this->shapes) {
            shape->accept(visitor);
        }
    }
};


int main(){
    int n;
    std::cin>>n;
    std::vector<Shape*> shapes;
    for (int i = 0; i < n; ++i) {
        std::string type;
        std::cin>>type;
        if (type=="Circle"){
            int radius;
            std::cin>>radius;
            shapes.emplace_back(new Circle(radius));
        }else if(type=="Rectangle"){
            int width,height;
            std::cin>>width>>height;
            shapes.emplace_back(new Rectangle(width,height));
        }else{
            std::cout<<"Invalid input"<<std::endl;
            return 1;
        }
    }
    Drwaing drwaing(shapes);//调用对象结构类
    AreaCalculator areaCalculator;//调用具体访问者
    drwaing.accept(areaCalculator);//调用对象结构类中的accept方法

    for (auto* shape: shapes) {
        delete shape;
    }
    return 0;
}