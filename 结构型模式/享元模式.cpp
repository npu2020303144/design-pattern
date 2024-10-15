#include<iostream>
#include <sstream>
#include<vector>
#include <unordered_map>

using namespace std;

//享元模式：一种结构型设计模式，对象被设计为可共享的，可以被多个上下文使用，而不必在每个上下文中都创建新的对象。
//内部状态：指那些可以被多个对象共享的状态，它存储在享元对象内部，并且对于所有享元对象都是相同的，这部分状态通常是不变的。
//外部状态：享元对象依赖的、可能变化的部分。这部分状态不存储在享元对象内部，而是在使用享元对象时通过参数传递给对象。

/*分为：
享元接口Flyweight: 所有具体享元类的共享接口，通常包含对外部状态的操作。
具体享元类ConcreteFlyweight: 继承Flyweight类或实现享元接口，包含内部状态。
享元工厂类FlyweightFactory: 创建并管理享元对象，当用户请求时，提供已创建的实例或者创建一个。
客户端Client: 维护外部状态，在使用享元对象时，将外部状态传递给享元对象。
*/

/*
 一个简单的图形编辑器，用户可以在画布上绘制不同类型的图形，
 图形就是所有图形对象的内部状态（不变的），
 图形的坐标位置就是图形对象的外部状态（变化的）。

 如果图形编辑器中有成千上万的图形对象，每个图形对象都独立创建并存储其内部状态，
 那么系统的内存占用可能会很大，在这种情况下，享元模式共享相同类型的图形对象，
 每种类型的图形对象只需创建一个共享实例，然后通过设置不同的坐标位置个性化每个对象，
 通过共享相同的内部状态，降低了对象的创建和内存占用成本。
*/

enum ShapeType {
    CIRCLE, RECTANGLE, TRIANGLE
};

string shapeToString(ShapeType type) {
    switch (type) {
        case CIRCLE:
            return "CIRCLE";
        case RECTANGLE:
            return "RECTANGLE";
        case TRIANGLE:
            return "TRIANGLE";
        default:
            return "UNKNOWN";
    }
}

class Position {
private:
    int x;
    int y;
public:
    explicit Position(const int &x, const int &y) : x(x), y(y) {}

    int getX() const {
        //当const放在成员函道数"尾巴"上修饰成员函数时，则该成员函数被称为“常成员函数”，
        // 表示该成员函数不可以修改类内的成员变量，这是为了保护类的成员变量不被修改。
        return this->x;
    }

    int getY() const {
        return this->y;
    }

    friend ostream &operator<<(ostream &output, const Position &position) {
        output << "(" << position.x << ", " << position.y << ")";
        return output;
    }
};

//享元接口类
class Shape {
public:
    virtual void draw(const Position &position) = 0;

    virtual ~Shape() = default;
};

//具体享元类
class ConcreteShape : public Shape {
private:
    ShapeType shapeType;
    bool isCreated;
public:
    explicit ConcreteShape(ShapeType shapeType) : shapeType(shapeType), isCreated(true) {}

    void draw(const Position &position) override {
        cout << shapeToString(this->shapeType) << " "<<
        (this->isCreated ? "drawn" : "shared") << " at " << position << endl;
    }

    void setCreated(bool firstTime) {
        this->isCreated = firstTime;
    }
};

//享元工厂类
class ShapeFactory {
private:
    unordered_map<ShapeType, Shape *> shapes;
public:
    Shape *getShape(ShapeType type) {
        if (shapes.find(type) == shapes.end()) {
            shapes[type] = new ConcreteShape(type);
        }
        return shapes[type];
    }

    ~ShapeFactory() {
        for (const auto &element: shapes) {
            delete element.second;
        }
    }
};


int main() {
    string command;
    ShapeFactory factory;
    while (getline(cin, command)) {
        istringstream iss(command);
        string typeStr;
        int x, y;
        iss >> typeStr >> x >> y;
        ShapeType type;
        if (typeStr == "CIRCLE") {
            type = CIRCLE;
        } else if (typeStr == "RECTANGLE") {
            type = RECTANGLE;
        } else if (typeStr == "TRIANGLE") {
            type = TRIANGLE;
        } else {
            cerr << "Invalid shape type: " << typeStr << endl;
            exit(0);
        }

        Shape *shape = factory.getShape(type);
        shape->draw(Position(x, y));

        //static_cast实现C++种内置基本数据类型之间的相互转换，不能用于两个不相关类型进行转换。
        //dynamic_cast用于将一个父类对象的指针/引用转换为子类对象的指针或引用（动态转换）,只能用于含有虚函数的类；
        //会先检查是否能转换成功，如果能则转换，不能则返回0,
        //进行上行转换的时候，与static_cast 的作用一样。下行转换的时候，具有类型检查的功能，比static_cast更安全。
        //上行转换：把派生类的指针或引用转换成基类表示
        //下行转换：把基类的指针或引用转换成派生类表示
        dynamic_cast<ConcreteShape *>(shape)->setCreated(false);
    }
    return 0;
}