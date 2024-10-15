#include<iostream>
#include<vector>
#include <list>

using namespace std;

/*观察者模式：属于行为型模式，定义了一对多的关系，
 * 多个观察者对象同时监听一主题个对象
 * 主题对象的状态发生变化时，
 * 所有依赖于它的观察者都得到通知并被自动更新。
 * 分为：
 * 主题（Subject）：被观察的对象，当主题本身发生改变时就会通知观察者。
 * 观察者（Observer）：进行观察的对象，当主题发生变化时，观察者就会得到通知并执行相应的处理。

 主题Subject， 一般定义成一个接口，提供方法用于注册、删除和通知观察者，通常也包含一个状态，当状态发生改变时，通知所有的观察者。
 观察者Observer: 观察者也需要实现一个接口，包含一个更新方法，在接收主题通知时执行对应的操作。
 具体主题ConcreteSubject: 主题的具体实现, 维护一个观察者列表，包含了观察者的注册、删除和通知方法。
 具体观察者ConcreteObserver: 观察者接口的具体实现，每个具体观察者都注册到具体主题中，当主题状态变化并通知到具体观察者，具体观察者进行处理。
 */

class Observer {
public:
    virtual void update(int hour) = 0;

    virtual ~Observer() = default;
};

class Subject {
public:
    virtual void addObserver(Observer *observer) = 0;

    virtual void deleteObserver(Observer *observer) = 0;

    virtual void notifyObservers() = 0;

    virtual ~Subject() = default;
};

//具体主题实现
class Clock : public Subject {
private:
    list<Observer *> observers;
    int hour;
public:
    Clock() : hour(0) {}

    void addObserver(Observer *observer) override {
        this->observers.emplace_back(observer);
    }

    void deleteObserver(Observer *observer) override {
        //删除list中某个元素，用其成员函数remove
        this->observers.remove(observer);
    }

    void notifyObservers() override {
        for (auto observer: this->observers) {
            observer->update(this->hour);
        }
    }

    const list<Observer *> &getObservers() const {
        return this->observers;
    }

    //更新时间并通知观察者
    void tick() {
        this->hour = (this->hour + 1) % 24;
        notifyObservers();
    }

    ~Clock() override = default;
};

//具体观察者实现
class Student : public Observer {
private:
    string name;
public:
    explicit Student(const string &name) : name(name) {}

    void update(int hour) override {
        cout << this->name << ' ' << hour << endl;
    }
};

int main() {
    int N;
    cin >> N;
    Clock clock;
    while (N--) {
        string name;
        cin >> name;
        clock.addObserver(new Student(name));
    }

    int updates;
    cin >> updates;
    for (int j = 0; j < updates; ++j) {
        clock.tick();
    }

    for (auto observer: clock.getObservers()) {
        delete observer;
    }
    return 0;
}