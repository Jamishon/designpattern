/**
 * @file facade.cc
 * @author Jamishon
 * @brief Roles: Facede, Subsystem classes.
 *        Tips: Give out a consistent interface for multiple interfaces.
 * @version 0.1
 * @date 2022-08-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

#define FACADE_SUBCLASS 1
#define FACADE_CONFIG_OBJECT 0

class Subsystem1 {
 public:
  void Function1() { std::cout << "Subsystem1::Function1()" << std::endl; }

  void Function2() { std::cout << "Subsystem1::Function2()" << std::endl; }
};

class Subsystem2 {
 public:
  void Action1() { std::cout << "Subsystem2::Action1()" << std::endl; }

  void Action2() { std::cout << "Subsystem2::Action2()" << std::endl; }
};

class Subsystem3 {
 public:
  void Operation1() { std::cout << "Subsystem3::Operation1()" << std::endl; }
};

#if FACADE_SUBCLASS

class Facade {
 public:
  virtual void Function() = 0;
};

class FacadeSubA : public Facade {
 public:
  virtual void Function() {
    std::cout << "Function: {" << std::endl;
    s1_.Function1();
    s2_.Action2();
    std::cout << "}" << std::endl;
  }

 private:
  Subsystem1 s1_;
  Subsystem2 s2_;
};

class FacadeSubB : public Facade {
 public:
  virtual void Function() {
    std::cout << "Function: {" << std::endl;
    s2_.Action1();
    s3_.Operation1();
    std::cout << "}" << std::endl;
  }

 private:
  Subsystem2 s2_;
  Subsystem3 s3_;
};

#elif FACADE_CONFIG_OBJECT

class Facade {
 public:
  void ConfigFunctionA() {
    s1_ = new Subsystem1;
    s2_ = new Subsystem2;
  }

  void ConfigFunctionB() {
    s2_ = new Subsystem2;
    s3_ = new Subsystem3;
  }

  void FunctionA() {
    std::cout << "FunctionA: {" << std::endl;
    s1_->Function1();
    s2_->Action2();
    std::cout << "}" << std::endl;
    delete s1_;
    delete s2_;
  }

  void FunctionB() {
    std::cout << "FunctionB: {" << std::endl;
    s2_->Action1();
    s3_->Operation1();
    std::cout << "}" << std::endl;
    delete s2_;
    delete s3_;
  }

 private:
  Subsystem1* s1_;
  Subsystem2* s2_;
  Subsystem3* s3_;
};

#endif

int main() {
#if FACADE_SUBCLASS
  Facade* p = new FacadeSubA;
  p->Function();
  delete p;

  p = new FacadeSubB;
  p->Function();
  delete p;
#elif FACADE_CONFIG_OBJECT
  Facade* p = new Facade;

  p->ConfigFunctionA();
  p->FunctionA();

  p->ConfigFunctionB();
  p->FunctionB();

  delete p;

#endif
}