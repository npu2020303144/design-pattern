#include <iostream>

/*
 * 代理模式：属于结构型设计模式，允许一个对象（代理）充当另一个对象（真实对象）的接口，以控制对这个对象的访问。
 * 通常用于在访问某个对象时引入一些间接层(中介的作用)，这样可以在访问对象时添加额外的控制逻辑，比如限制访问权限，延迟加载。
 *
 * 主要角色有：
 * 抽象主题：抽象类，通过接口或抽象类声明真实主题和代理对象实现的业务方法。
 * 真实主题：定义了代理类所代表的真实对象，是客户端最终要访问的对象。
 * 代理：包含一个引用，该引用可以是真实主题的实例，控制对真实主题的访问，并可能负责创建和删除真实主题的实例。
 * */

// 抽象主题
class HousePurchase {
public:
    virtual void requestHouse(int area) = 0;

    virtual ~HousePurchase() = default;
};

//真实主题
class HouseBuyer : public HousePurchase {
public:
    void requestHouse(int area) override {
        std::cout << "YES" << std::endl;
    }
};

//代理
class Proxy : public HousePurchase {
private:
    HouseBuyer client;
public:
    void requestHouse(int area) override {
        if (area > 100) {
            client.requestHouse(area);
        } else {
            std::cout << "NO" << std::endl;
        }
    }

};

int main() {
    int N;
    std::cin >> N;
    HouseBuyer client;
    auto *proxy = new Proxy();
    for (int i = 0; i < N; ++i) {
        int area;
        std::cin >> area;
        proxy->requestHouse(area);
    }
    delete proxy;
    return 0;
}