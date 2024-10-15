#include <iostream>
#include <string>
#include <utility>
#include <vector>

/*
 * 原型模式：属于创建型模式，基于现有的对象创建新的对象，而不是从头开始创建。
 * 原型对象被用作创建新对象的模板。新对象通过复制原型对象的属性和状态来创建，而无需知道具体的创建细节。
 * 如果一个对象的创建过程比较复杂，那每次创建该对象都需要消耗资源，
 * 而通过原型模式就可以复制现有的一个对象来迅速创建/克隆一个新对象，不必关心具体的创建细节，可以降低对象创建的成本。
 *
 * 主要角色为：
 * 抽象原型接口prototype: 声明一个克隆自身的方法clone
 * 具体原型类ConcretePrototype: 实现clone方法，复制当前对象并返回一个新对象。
 * */

//抽象原型类
class Prototype {
public:
    virtual Prototype *clone() const = 0;

    virtual std::string getDetails() const = 0;

    virtual ~Prototype() = default;
};

class Rectangle : public Prototype {
private:
    std::string color;
    int width;
    int height;
public:
    explicit Rectangle(std::string color, int width, int height) : color(std::move(color)), width(width),
                                                                   height(height) {}

    Prototype *clone() const override {
        return new Rectangle(*this);
    }

    std::string getDetails() const override {
        return "Color: " + this->color + ", Width: " + std::to_string(this->width) + ", Height: " +
               std::to_string(height);
    }
};


int main() {
    std::string color;
    int width;
    int height;
    std::cin >> color >> width >> height;
    int N;
    std::cin >> N;
    Prototype *prototype = new Rectangle(color, width, height);
    for (int i = 0; i < N; ++i) {
        Prototype* clonedRectangle = prototype->clone();
        std::cout<<clonedRectangle->getDetails()<<std::endl;
        delete clonedRectangle;
    }
    delete prototype;
    return 0;
}