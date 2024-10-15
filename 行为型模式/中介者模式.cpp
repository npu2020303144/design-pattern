#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>

using namespace std;

// 中介者模式：也是调停者模式，属于行为型模式。

/*
通过一个中介对象封装一组对象之间的交互。分为以下部分：
抽象中介者（Mediator）：定义中介者的接口，用于各个具体同事对象之间的通信。
具体中介者（Concrete Mediator）：实现抽象中介者接口，负责协调各个具体同事对象的交互关系，它需要知道所有具体同事类，并从具体同事接收消息，向具体同事对象发出命令。
抽象同事类（Colleague）：定义同事类的接口，维护一个对中介者对象的引用，用于通信。
具体同事类（Concrete Colleague）：实现抽象同事类接口，每个具体同事类只知道自己的行为，而不了解其他同事类的情况，因为它们都需要与中介者通信，通过中介者协调与其他同事对象的交互。
*/


#include <iostream>
#include <vector>
#include <map>
#include <list>

// 抽象中介者
class ChatRoomMediator;

// 抽象同事类
class ChatUser {
private:
    std::string name;
    ChatRoomMediator* mediator;
    std::list<std::string> receivedMessages;

public:
    ChatUser(const std::string& name, ChatRoomMediator* mediator);

    std::string getName() const {
        return name;
    }

    void sendMessage(const std::string& message);

    virtual void receiveMessage(const std::string& sender, const std::string& message) = 0;

    std::list<std::string> getReceivedMessages() const {
        return receivedMessages;
    }

protected:
    void addReceivedMessage(const std::string& message) {
        receivedMessages.push_back(message);
    }
};

// 具体同事类
class ConcreteChatUser : public ChatUser {
public:
    ConcreteChatUser(const std::string& name, ChatRoomMediator* mediator); 

    void receiveMessage(const std::string& sender, const std::string& message) override;
};

ConcreteChatUser::ConcreteChatUser(const std::string& name, ChatRoomMediator* mediator) : ChatUser(name, mediator) {}

void ConcreteChatUser::receiveMessage(const std::string& sender, const std::string& message) {
    std::string receivedMessage = getName() + " received: " + message;
    addReceivedMessage(receivedMessage);
    std::cout << receivedMessage << std::endl; 
}

// 抽象中介者
class ChatRoomMediator {
public:
    virtual void sendMessage(const std::string& sender, const std::string& message) = 0;
    virtual void addUser(ChatUser* user) = 0;
    virtual std::map<std::string, ChatUser*> getUsers() = 0;
    virtual ~ChatRoomMediator() = default;
};

// 具体中介者
class ChatRoomMediatorImpl : public ChatRoomMediator {
private:
    std::map<std::string, ChatUser*> users;

public:
    void sendMessage(const std::string& sender, const std::string& message) override {
        for (const auto& userPair : users) {
            if (userPair.first != sender) {
                userPair.second->receiveMessage(sender, message);
            }
        }
    }

    void addUser(ChatUser* user) override {
        users[user->getName()] = user;
    }

    std::map<std::string, ChatUser*> getUsers() override {
        return users;
    }
};

// 实现 ChatUser 类的成员函数
ChatUser::ChatUser(const std::string& name, ChatRoomMediator* mediator) : name(name), mediator(mediator) {
    mediator->addUser(this);
}

void ChatUser::sendMessage(const std::string& message) {
    mediator->sendMessage(name, message);
}

int main() {
    std::vector<std::string> userNames;
    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        std::string userName;
        std::cin >> userName;
        userNames.push_back(userName);
    }

    ChatRoomMediator* mediator = new ChatRoomMediatorImpl();

    // 创建用户对象
    for (const auto& userName : userNames) {
        new ConcreteChatUser(userName, mediator);
    }

    // 发送消息并输出
    std::string sender, message;
    while (std::cin >> sender >> message) {
        ChatUser* user = mediator->getUsers()[sender];
        if (user != nullptr) {
            user->sendMessage(message);
        }
    }

    delete mediator; // 释放中介者对象

    return 0;
}