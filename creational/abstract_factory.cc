/**
 * @file abstract_factory.cc
 * 
 * @author Jamihon
 * @brief 5 roles: AbstractFactory,ConcreteFactory,AbstractProduct,ConcreProduct,client
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

class AbstractProductA {
public:
  AbstractProductA() {
    std::cout << "AbstractProductA" << std::endl;
  }    

};

class AbstractProductB {
public:
  AbstractProductB() {
    std::cout << "AbstractProductB" << std::endl;
  }    

};

class ProductA1 : public AbstractProductA {
public:
  ProductA1() {
    std::cout << "ProductA1" << std::endl;
  }    
};

class ProductA2 : public AbstractProductA {
public:
  ProductA2() {
    std::cout << "ProductA2" << std::endl;
  }    
};

class ProductB1 : public AbstractProductB {
public:
  ProductB1() {
    std::cout << "ProductB1" << std::endl;
  }  
};

class ProductB2 : public AbstractProductB {
public:
  ProductB2() {
    std::cout << "ProductB2" << std::endl;
  }  
};


class AbstractFactory {
public:
  AbstractFactory() {
    std::cout << "AbstractFactory" << std::endl;
  }
  virtual AbstractProductA *CreateProductA() {}
  virtual AbstractProductB *CreateProductB() {}
};

class ConcreteFactory1 : public AbstractFactory {
public:
  ConcreteFactory1() {
    std::cout << "ConcreteFactory1" << std::endl;
  }
  AbstractProductA *CreateProductA() {
    std::cout << "ConcreteFactory1 produce -->" << std::endl;
    return new ProductA2;
  }

  AbstractProductB *CreateProductB() {
     std::cout << "ConcreteFactory1 produce -->" << std::endl;
    return new ProductB1;
  }
};


class ConcreteFactory2 : public AbstractFactory {
public:
  ConcreteFactory2() {
    std::cout << "ConcreteFactory2" << std::endl;
  }

  AbstractProductA *CreateProductA() {
    std::cout << "ConcreteFactory2 produce -->" << std::endl;
    return new ProductA1;
  }

  AbstractProductB *CreateProductB() {
     std::cout << "ConcreteFactory2 produce -->" << std::endl;
    return new ProductB2;
  }
};

int main() {
   AbstractFactory* p = new ConcreteFactory1;
   AbstractProductA* pa = p->CreateProductA();
   AbstractProductB* pb = p->CreateProductB();
   delete p;
   delete pa;
   delete pb;

   p = new ConcreteFactory2;
   pa = p->CreateProductA();
   pb = p->CreateProductB();

   delete p;
   delete pa;
   delete pb;
}