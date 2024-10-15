#include<iostream>
#include<vector>
#include <cmath>

using namespace std;

/* 策略模式：属于行为型模式，定义了一系列完成相同工作，实现却不同的算法。
 * 将每个算法封装起来，使它们可以相互替换，让算法的变化不会影响使用算法的客户。
 *
 * 实例：
 * 电商网站对于商品的折扣策略有不同的算法，比如新用户满减优惠，不同等级会员的打折情况不同，
 * 这种情况下会产生大量的if-else语句, 并且如果优惠政策修改时，还需要修改原来的代码。
 * 这就可以将不同的优惠算法封装成独立的类来避免大量的条件语句，如果新增优惠算法，可以添加新的策略类来实现，
 * 客户端在运行时选择不同的具体策略，而不必修改客户端代码改变优惠策略。
 *
 * 分为：
 * 策略类Strategy: 定义所有支持的算法的公共接口。
 * 具体策略类ConcreteStrategy: 实现了策略接口，提供具体的算法实现。
 * 上下文类Context: 包含一个策略实例，并在需要时调用策略对象的方法。
 */

// 抽象优惠策略类
class DiscountStrategy {
public:
    virtual int applyDiscount(int originalPrice) = 0;

    virtual ~DiscountStrategy() = default;
};

// 九折优惠策略类
class NineDiscount : public DiscountStrategy {
public:
    int applyDiscount(int originalPrice) override {
        // round()仅对小数点后一位四舍五入，即只保留整数位
        return static_cast<int>(round(originalPrice * 0.9));
    }
};

// 满减优惠策略类
class subDiscount : public DiscountStrategy {
private:
    int thresholds[4] = {100, 150, 200, 300};
    int discount[4] = {5, 15, 25, 40};
public:
    int applyDiscount(int orinalPrice) override {
        for (int i = 3; i >= 0; --i) {
            if (orinalPrice >= this->thresholds[i]) {
                return orinalPrice - this->discount[i];
            }
        }
        return orinalPrice;
    }
};

// 上下文类，即需要调用策略的对象
class DiscountContext {
private:
    DiscountStrategy *strategy;
public:
    void setDiscountStrategy(DiscountStrategy *discountStrategy) {
        this->strategy = discountStrategy;
    }

    int applyDiscount(int originalPrice) {
        return this->strategy->applyDiscount(originalPrice);
    }
};

int main() {
    int N;
    cin >> N;
    vector<int> ans(N);
    int i=0;
    while (N--) {
        int originalPrice, strategy;
        cin >> originalPrice >> strategy;
        DiscountStrategy* discountStrategy;
        switch (strategy) {
            case 1:
                discountStrategy = new NineDiscount();
                break;
            case 2:
                discountStrategy= new subDiscount();
                break;
            default:
                cout<<"Unknown strategy type"<<endl;
                return 1;
        }
        DiscountContext context{};
        context.setDiscountStrategy(discountStrategy);

        int discountPrice = context.applyDiscount(originalPrice);
        ans[i++]=discountPrice;

        delete discountStrategy;
    }
    for (int an : ans) {
        cout<<an<<endl;
    }
    return 0;
}