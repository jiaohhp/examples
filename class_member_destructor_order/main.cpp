/*
 * 结论：初始化顺序是定义的顺序，跟列表顺序无关；析构顺序与构造顺序相反。
 */

#include <iostream>
#include <memory>

#define Trace()  do{ std::cout << __PRETTY_FUNCTION__ << std::endl; } while(0)
class A
{
public:
    A()
    {
        Trace();
    }
    ~A()
    {
        Trace();
    }
};

class B
{
public:
    B()
    {
        Trace();
    }
    ~B()
    {
        Trace();
    }
};

class Default
{
public:
    Default(){}
    ~Default(){}
private:
    A a;
    B b;
};

class ManualConstructor
{
public:
    ManualConstructor() : b(), a(){}
    ~ManualConstructor(){}
private:
    A a;
    B b;
};

class ManualPtrConstructor
{
public:
    ManualPtrConstructor() : pB(new B()), pA(new A()){}
    ~ManualPtrConstructor(){}
private:
    std::shared_ptr<A> pA;
    std::shared_ptr<B> pB;
};

int main()
{
    std::cout << "Default constructor - Default destructor" << std::endl;
    {
        Default();
    }
    std::cout << std::endl;

    std::cout << "Manual constructor - Default destructor" << std::endl;
    {
        ManualConstructor();
    }
    std::cout << std::endl;

    std::cout << "Manual ptr constructor - Default destructor" << std::endl;
    {
        ManualPtrConstructor();
    }

    return 0;
}
