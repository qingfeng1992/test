/*************************************************************************
    > File Name: factory.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年05月15日 星期五 22时46分01秒
 ************************************************************************/

#include<iostream>
using namespace std;

//产品类抽象
class Product
{
	public:
		Product() = default;
		~Product(){}
};

class ConcreteProduct : public Product
{
	public:
		ConcreteProduct() { cout << "ConcreteProduct constructor" << endl;};
		~ConcreteProduct() = default;
		ConcreteProduct(const ConcreteProduct& other) = default;
		ConcreteProduct& operator = (const ConcreteProduct& other) = default;
		
};

class ConcreteProduct1 : public Product
{
	public:
		ConcreteProduct1(){ cout << "ConcreteProduct1 constructor" << endl;}
		~ConcreteProduct1() = default;
};

//单例工场，CreateProduct方法返回的是抽象产品的指针，换句话说，只要是Product的子类都能创建
template <class T>
class Factory
{
	private:
        //单利模式也可以把构造函数设置为protected，这样这个单利类就是可以继承的，如果为私有的就不能有子类
		Factory() = default;

	public:
		~Factory() = default;
		Product* CreateProduct(){ return new T;}
		static Factory<T>*  GetInstance()
		{ 
			static Factory<T> ins;
			return &ins;
		} 
};



template <class T>
Product* GetProductFromFactory(Factory<T> *fat)
{
	return fat->CreateProduct();		
}

int main(int argc, char** argv)
{
	GetProductFromFactory(Factory<ConcreteProduct>::GetInstance());
	GetProductFromFactory(Factory<ConcreteProduct1>::GetInstance());
	return 0;
}






