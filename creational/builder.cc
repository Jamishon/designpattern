/**
 * @file builder.cc
 * @author your name (you@domain.com)
 * @brief Roles: Driector, Builder, ConcreteBuilder, Product. 
 *        Summarize: Object creation and performace are separated.
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>

class ProductA {
public:
    std::string product;    

    friend std::ostream& operator<<(std::ostream& os, const ProductA &a) {
      os << a.product;
      return os;
    }
};

class ProductB {
public:
    std::string product;

    friend std::ostream& operator<<(std::ostream& os, const ProductB& b) {
     os << b.product;
     return os;
    }
};

class ProductC {
public:
    std::string product; 

     friend std::ostream& operator<<(std::ostream& os, const ProductC& p) {
     os << p.product;
     return os;
    }
};

class ProductD {
public:
    std::string product; 

     friend std::ostream& operator<<(std::ostream& os, const ProductD& p) {
     os << p.product;
     return os;
    }
};

class Builder {
public:
    virtual void BuildPartA() {}
    virtual void BuildPartB() {}
    virtual void BuildPartC() {}
    virtual void BuildPartD() {}

    virtual ~Builder() { }


};

class ConcreteBuilder1 : public Builder {
public:
    ConcreteBuilder1() : p(new ProductA) {
        p = new ProductA;
    }

    virtual void BuildPartA() {
    
        
        p->product.append("4 5 6 8");
        
    }

    virtual void BuildPartB() {
        p->product.append("\n");
    }

    virtual void BuildPartC() {
    
        p->product.append("7 3 9 2");

    }
    virtual void BuildPartD() {
        p->product.append("0 0 1 7");
    }

    ProductA* GetProductA() {
        return p;
    }
private:
    ProductA* p;
};

class ConcreteBuilder2 : public Builder {
public:
    ConcreteBuilder2() : p(new ProductB) {

    }
     virtual void BuildPartA() {
       
        p->product.append("7 3 9 2");
    }

    virtual void BuildPartB() {
        p->product.append("\n");
    }
    
    virtual void BuildPartC() {
       
        p->product.append("5 6 8 7");

    }
    virtual void BuildPartD() {
         
        p->product.append("4 3 2 1");
    }

    ProductB* GetProductB() {
        return p;
    }

private:
    ProductB* p;
};


class ConcreteBuilder3 : public Builder {
public:
    ConcreteBuilder3() : p(new ProductC) {

    }
     virtual void BuildPartA() {
       
        p->product.append("7 3 9 2 2 9 3 7");
    }

    virtual void BuildPartB() {
        p->product.append("\n");
    }
    
    virtual void BuildPartC() {
       
        p->product.append("5 6 8 7 7 8 6 5");

    }
    virtual void BuildPartD() {
         
        p->product.append("4 3 2 1 1 2 3 4");
    }

    ProductC* GetProductC() {
        return p;
    }

private:
    ProductC* p;
};


class ConcreteBuilder4: public Builder {
public:
    ConcreteBuilder4() : p(new ProductD) {

    }
     virtual void BuildPartA() {
       
        p->product.append("7 3 9 2\n7 3 9 2");
    }

    virtual void BuildPartB() {
        p->product.append("\n");
    }
    
    virtual void BuildPartC() {
       
        p->product.append("5 6 8 7\n5 6 7 8");

    }
    virtual void BuildPartD() {
         
        p->product.append("4 3 2 1\n5 6 7 8");
    }

    ProductD* GetProductD() {
        return p;
    }

private:
    ProductD* p;
};

class Director {

public:
    Director() {
    
    }

    void BuildProduct1(Builder* pb) {
       pb->BuildPartA();
       pb->BuildPartB();
       pb->BuildPartC();
       pb->BuildPartB();
       pb->BuildPartC();
       pb->BuildPartB();
       pb->BuildPartD();
       pb->BuildPartB();
    }

    void BuildProduct2(Builder* pb) {
       pb->BuildPartA();
       pb->BuildPartB();
       pb->BuildPartC();
       pb->BuildPartB();
       pb->BuildPartC();
       pb->BuildPartB();
       pb->BuildPartD();
       pb->BuildPartB();

       pb->BuildPartD();
       pb->BuildPartB();
       pb->BuildPartC();
       pb->BuildPartB();
       pb->BuildPartC();
       pb->BuildPartB();
       pb->BuildPartA();
       pb->BuildPartB();
    }

};

int main() {
  Director director;

  ConcreteBuilder1* pb1 = new ConcreteBuilder1;
  director.BuildProduct1(pb1);
  ProductA* ppa = pb1->GetProductA();
  std::cout<< *ppa << std::endl;

  ConcreteBuilder2* pb2 = new ConcreteBuilder2;
  director.BuildProduct1(pb2);
  ProductB* ppb = pb2->GetProductB();
  std::cout<< *ppb << std::endl;

  ConcreteBuilder3* pb3 = new ConcreteBuilder3;
  director.BuildProduct2(pb3);
  ProductC* ppc = pb3->GetProductC();
  std::cout << *ppc << std::endl;

  ConcreteBuilder4* pb4 = new ConcreteBuilder4;
  director.BuildProduct2(pb4);
  ProductD* ppd = pb4->GetProductD();
  std::cout << *ppd << std::endl;


  delete pb1;
  delete ppa;
  delete pb2;
  delete ppb;
  delete pb3;
  delete ppc;
  delete pb4;
  delete ppd;
}