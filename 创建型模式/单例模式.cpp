#include<iostream>
#include<string>
#include <vector>
#include <unordered_map>

using namespace std;

/*单例模式
 * 私有构造函数，形成单例模式：
 * 可以避免因打开多个购物车窗口而造成内存资源的浪费，
 * 或出现各个窗口显示内容的不一致等错误
*/

class CartManager{
private:
    vector<string> goodsOrder;
    unordered_map<string ,int> elements;
    CartManager(){}
public:
    // 单例模式必须向外提供一个静态的公有函数用于创建或获取静态实例
    // static成员函数不需要通过类的对象来调用,而是通过类名直接调用
    // 通过 cartManager::getInstance() 来获取购物车的实例，而不用事先创建购物车对象
    // 确保一个类在运行时只有一个实例存在
    static CartManager& getInstance() {
        static CartManager instance;
        return instance;
    }

    void show(){
        for (const auto& ele:this->goodsOrder){
            //当elements[ele]为0（即不存在ele）时，使用at可抛出异常，更符合实际应用
            cout<<ele<<" "<<elements.at(ele)<<endl;
        }
    }

    void addToCart(const string& good, const int& quantity){
        if (this->elements.find(good)== this->elements.end()){
            goodsOrder.emplace_back(good);
        }
          this->elements[good]+=quantity;
    }
};


int main() {
    string itemName;
    int quantity;
    CartManager& cartManager=CartManager::getInstance();
    while(cin>>itemName>>quantity){
        cartManager.addToCart(itemName, quantity);
    }
    cartManager.show();
    return 0;
}