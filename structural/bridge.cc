/**
 * @file bridge.cc
 * @author Jamishon
 * @brief Roles: Abstraction, RedefinedAbstraction, Implementor,
 * ConcreteImplementor. 
 *        Tips: Separate the abstract parts from the implementation, and
 * can change themselves independently.
 * @version 0.1
 * @date 2022-08-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

class Implementor {
 public:
  virtual void OperationImpl() = 0;
};

class ConcreteImplementor1 : public Implementor {
 public:
  void OperationImpl() {
    std::cout << "ConcreteImplementor1::OperationImpl" << std::endl;
  }
};

class ConcreteImplementor2 : public Implementor {
 public:
  void OperationImpl() {
    std::cout << "ConcreteImplementor2::OperationImpl" << std::endl;
  }
};

class Abstraction {
 public:
  Implementor* GetImplementor() {
    return pImpl;
  }

  virtual void Operation() {
    std::cout << "Abstraction::Operation" << std::endl;
    pImpl->OperationImpl();
  }

 protected:
  Implementor* pImpl;
};

class RedefinedAbstraction : public Abstraction {
 public:
  RedefinedAbstraction(Implementor* p) { pImpl = p; }

  void Operation() {
    std::cout << "RedefinedAbstraction::Operation" << std::endl;
    Abstraction::Operation();
  }
};

int main() {
  Abstraction* p1 = new RedefinedAbstraction(new ConcreteImplementor1);
  p1->Operation();

  Abstraction* p2 = new RedefinedAbstraction(new ConcreteImplementor2);
  p2->Operation();

  Implementor* p = p1->GetImplementor();
  delete p;
  p = p2->GetImplementor();
  delete p;
  delete p1;
  delete p2;
}