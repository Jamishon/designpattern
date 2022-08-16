/**
 * @file factory_method.cc
 * @author Jamishon
 * @brief Roles: AbstractFactory, ConcreteFactory, AbstractProduct,
 *               ConcreteProduct, Client.
 *        Tips: Delay the class instance into the subclass.
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string.h>

using namespace std;

class Product {

public:
    virtual void name() = 0;    
    virtual ~Product();
};

Product::~Product() {

}

class ConcreteProductA : public Product {

public:
    void name() {
        std::cout << "ConcreteProductA" << std::endl;
    }

};

class ConcreteProductB : public Product {

public:
    void name() {
        std::cout << "ConcreteProductB" << std::endl;
    }

};

class ConcreteProductC : public Product {

public:
    void name() {
        std::cout << "ConcreteProductC" << std::endl;
    }

};


class Creator {
public:
    virtual Product* factory_method() = 0;
    virtual ~Creator();

    Product* get_product() {
      Product* p = factory_method();
      return p;      
    }    
};

Creator::~Creator() {

}

class ConcreteCreatorA : public Creator {
public:
  Product* factory_method() {
    return new ConcreteProductA;
  }    
};

class ConcreteCreatorB : public Creator {
public:
  Product* factory_method() {
    return new ConcreteProductB;
  }    
};

class ConcreteCreatorC : public Creator {
public:
  Product* factory_method() {
    return new ConcreteProductC;
  }    
};


//factory method, template version
template <class T>
class Creator_T {
public:    
    virtual Product* get_product() {
        return new T;
    }
};

int main() {

    Creator* pc = new ConcreteCreatorA;
    Product* pp = pc->get_product();
    pp->name();
    delete pc;
    delete pp;

    pc = new ConcreteCreatorB;
    pp = pc->get_product();
    pp->name();
    delete pc;
    delete pp;

    pc = new ConcreteCreatorC;
    pp = pc->get_product();
    pp->name();
    delete pc;
    delete pp;

    //template
    Creator_T<ConcreteProductA> a_t;
    pp= a_t.get_product();
    pp->name();
    delete pp;

    Creator_T<ConcreteProductB> b_t;
    pp = b_t.get_product();
    pp->name();
    delete pp;

    Creator_T<ConcreteProductC> c_t;
    pp = c_t.get_product();
    pp->name();
    delete pp;


    
    
}



