/**
 * @file prototype.cc
 * @author your name (you@domain.com)
 * @brief Roles: Prototype, ConcretePrototype, Client
 *        Clone classes by themselves   
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>

class ProtoType {
public:
  virtual ProtoType *clone() = 0;

  virtual ~ProtoType() {
    std::cout << "~ProtoType" << std::endl;
  }
};

class ConcreteProtoType1 : public ProtoType {
public:
    ConcreteProtoType1(int a, std::string b) {
      this->a = a;
      this->b.append(b);
    }

    ConcreteProtoType1() = default;

    ~ConcreteProtoType1() { std::cout << "~ConcreteProtoType2" << std::endl; }

    ProtoType *clone() {
        ConcreteProtoType1* p = new ConcreteProtoType1;
        p->a = this->a;
        p->b.append(this->b);

        return p;
    }

    friend std::ostream& operator<<(std::ostream& os, const ConcreteProtoType1 &c) {
        os << c.a <<" " << c.b << std::endl;
        return os;
    }

private:
    int a;
    std::string b;
};

class ConcreteProtoType2 : public ProtoType {
public:
    ConcreteProtoType2(std::string a, double b, int c) {
        this->a.append(a);
        this->b = b;
        this->c = c;
    } 

    ConcreteProtoType2() = default;

    ~ConcreteProtoType2() {
        std::cout << "~ConcreteProtoType2" << std::endl;
    }

    ProtoType *clone() {
        ConcreteProtoType2* p = new ConcreteProtoType2;
        p->a.append(this->a);
        p->b = this->b;
        p->c = this->c;

        return p;
    }

    friend std::ostream& operator<<(std::ostream& os, const ConcreteProtoType2 &c) {
        os << c.a <<" " << c.b << " " << c.c <<std::endl;
        return os;
    }

private:
    std::string a;
    double b;
    int  c;
};

int main() {
  ConcreteProtoType1* p1 = new ConcreteProtoType1(2587982435, "Hello,world!");
  ConcreteProtoType2* p2 = new ConcreteProtoType2("You are NO.1!", 3.14159265, 5484456);

  std::cout << *p1 << *p2 << std::endl;

  ConcreteProtoType1* p1c = dynamic_cast<ConcreteProtoType1 *>(p1->clone());
  ConcreteProtoType2* p2c = dynamic_cast<ConcreteProtoType2 *>(p2->clone());

  std::cout << *p1c << *p2c << std::endl;

  delete p1;
  delete p2;
  delete p1c;
  delete p2c;
}
