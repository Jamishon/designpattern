/**
 * @file adapter.cc
 * @author Jamishon
 * @brief Roles: Client, Target, Adapter, Adaptee
 *        Client calls operation on the adapter, then adapter calls the
 * function in the adaptee to implement this operation.
 * @version 0.1
 * @date 2022-08-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>

#define CLASS_VERSION

class Adaptee {
 public:
  Adaptee() { std::cout << "Adaptee" << std::endl; }
  ~Adaptee() { std::cout << "~Adaptee" << std::endl; }

  virtual void SpecificRequest() {
    std::cout << "SpecificRequest finished" << std::endl;
  }
};

class Target {
 public:
  Target() { std::cout << "Target" << std::endl; }

  virtual ~Target() { std::cout << "~Target" << std::endl; }

  virtual void Request() {
    std::cout << "Send Request, waiting..." << std::endl;
  }
};


#ifdef CLASS_VERSION
// Class version, inherit class Adaptee
class Adapter : private Adaptee, public Target {
 public:
  Adapter() { std::cout << "Adapter" << std::endl; }
  ~Adapter() { std::cout << "~Adapter" << std::endl; }

  virtual void Request() {
    Target::Request();
    std::cout << "Adapter receive request, working..." << std::endl;
    SpecificRequest();
  }
};

#else
//Object version, declear Adaptee object
class Adapter : public Target {
 public:
  Adapter() { std::cout << "Adapter" << std::endl; }
  ~Adapter() { std::cout << "~Adapter" << std::endl; }

  void Request() {
    Target::Request();
    std::cout << "Adapter receive request, working..." << std::endl;
    adaptee.SpecificRequest();
  }

 private:
  Adaptee adaptee;
};

#endif

int main() {
  Target* p = new Adapter;
  p->Request();

  delete p;
}