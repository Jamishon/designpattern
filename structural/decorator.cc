/**
 * @file decorator.cc
 * @author Jamishon
 * @brief Roles: Component, ConcreteComponent, Decorator, ConcreteDecorator.
 *        Tips: Dynamically add additional responsibilities to objects.
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

class Component {
 public:
  virtual ~Component() {}

  virtual void Operation() = 0;
};

class ConcreteComponent : public Component {
 public:
  virtual void Operation() { std::cout << "Hello world !"; }
};

class Decorator : public Component {
 public:
  virtual ~Decorator() {}

  virtual void Operation() {
    if (pc_) pc_->Operation();
  }

  void SetComponent(Component* p) { pc_ = p; }

 private:
  Component* pc_;
};

class ConcreteDecoratorA : public Decorator {
 public:
  virtual void Operation() {
    int num = 30;
    while (num--) std::cout << "A";
    std::cout << std::endl;
    Decorator::Operation();
    std::cout << std::endl;
    num = 30;
    while (num--) std::cout << "A";
  }
};

class ConcreteDecoratorB : public Decorator {
 public:
  virtual void Operation() {
    int num = 30;
    while (num--) std::cout << "B";
    std::cout << std::endl;
    Decorator::Operation();
    std::cout << std::endl;
    num = 30;
    while (num--) std::cout << "B";
  }
};

int main() {
  ConcreteComponent* pc = new ConcreteComponent;
  ConcreteDecoratorA* pda = new ConcreteDecoratorA;
  ConcreteDecoratorB* pdb = new ConcreteDecoratorB;

  // pdb -> pda -> pc
  pda->SetComponent(pc);
  pdb->SetComponent(pda);
  pdb->Operation();
  std::cout << std::endl;

  // pda -> pdb -> pc
  pdb->SetComponent(pc);
  pda->SetComponent(pdb);
  pda->Operation();
  std::cout << std::endl;

  delete pc;
  delete pda;
  delete pdb;
}
