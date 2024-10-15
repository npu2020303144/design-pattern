#include<iostream>
#include<string>
#include <memory>
#include <vector>

using namespace std;

/*
 * 迭代器模式：属于行为型模式。
 * 提供一种统一的方式来访问一个聚合对象中的各个元素，而不需要暴露该对象的内部表示。
 * 通过迭代器，客户端可以顺序访问聚合对象的元素，而无需了解底层数据结构。
 *
 * 分为四部分：
 * 迭代器接口Iterator：定义访问和遍历元素的接口, 通常会包括hasNext()方法用于检查是否还有下一个元素，以及next()方法用于获取下一个元素。
 * 具体迭代器ConcreateIterator：实现迭代器接口，实现遍历逻辑对聚合对象进行遍历。
 * 抽象聚合类：定义了创建迭代器的接口，包括一个createIterator方法用于创建一个迭代器对象。
 * 具体聚合类：实现在抽象聚合类中声明的createIterator()方法，返回一个与具体聚合对应的具体迭代器
*/

class Student{
private:
    string name;
    string ID;
public:
    explicit Student(const string& name, const string& ID):name(name), ID(ID){}
    string getName() const{
        return this->name;
    }
    string getID() const{
        return this->ID;
    }
};

// 迭代对象的接口
class StudentArrays{
public:
    virtual ~StudentArrays()=default;
    virtual vector<Student>::iterator begin()=0;
    virtual vector<Student>::iterator end()=0;
};

//实现用来迭代对象的接口
class ConcretStudentArrays:public StudentArrays{
private:
    vector<Student> students;
public:
    void addStudent(const Student& stu){
        this->students.emplace_back(stu);
    }

    vector<Student>::iterator begin() override{
        return this->students.begin();
    }
    vector<Student>::iterator end() override{
        return this->students.end();
    }
};


int main() {
    int N;
    cin>>N;
    ConcretStudentArrays studentArrays;
    for (int i = 0; i < N; ++i) {
        string name,ID;
        cin>>name>>ID;
        studentArrays.addStudent(Student(name, ID));
    }
    for (auto i = studentArrays.begin(); i != studentArrays.end(); ++i) {
        const Student& stu=*i;
        cout<<stu.getName()<<" "<<stu.getID()<<endl;
    }
    return 0;
}