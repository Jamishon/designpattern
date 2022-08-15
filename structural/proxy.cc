/**
 * @file proxy.cc
 * @author Jamishon
 * @brief Roles:Proxy, Subject, RealSubject.
 *        Using Proxy to access the object.
 * @version 0.1
 * @date 2022-08-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

class Subject {
 public:
  virtual void Request() {}
};

class RealObject : public Subject {
 public:
  void Request() { std::cout << "RealOjbect received request" << std::endl; }
};

class Proxy : public Subject {
 public:
  Proxy(Subject* p) : pRealSubject(p) {

  }

  void Request() {
    std::cout << "Proxy request Subject" << std::endl;
    pRealSubject->Request();
  }

 private:
  Subject* pRealSubject;
};

int main() {
    Subject* pReal = new RealObject();
    Subject* pProxy = new Proxy(pReal);

    pProxy->Request();

    delete pReal;
    delete pProxy;
}
