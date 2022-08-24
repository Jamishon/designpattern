/**
 * @file command.cc
 * @author Jamishon
 * @brief Roles:Command, ConcreteCommand, Client, Invoker, Receiver.
 *        Tips: Encapsulate a requirement into an object, put the
 *              object in a queue, log, redo or undo it.
 * @version 0.1
 * @date 2022-08-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

class Receive1 {
 public:
  void Action() { std::cout << "Receive1::Action" << std::endl; }
};

class Receive2 {
 public:
  void DoAction() { std::cout << "Receive2::DoAction" << std::endl; }
};

class Receive3 {
 public:
  void DoSomething() { std::cout << "Receive3::DoSomething" << std::endl; }
};

class Command {
 public:
  virtual ~Command() {}

  virtual void Execute() = 0;
};

class ConcreteCommand1 : public Command {
 public:
  ConcreteCommand1(Receive3* r3) : r3_(r3) {}
  void Execute() { r3_->DoSomething(); }

 private:
  Receive3* r3_;
};

class ConcreteCommand2 : public Command {
 public:
  ConcreteCommand2(Receive2* r2) : r2_(r2) {}
  void Execute() { r2_->DoAction(); }

 private:
  Receive2* r2_;
};

class ConcreteCommand3 : public Command {
 public:
  ConcreteCommand3(Receive1* r1) : r1_(r1) {}

  void Execute() { r1_->Action(); }

 private:
  Receive1* r1_;
};

class Invoker {
 public:
  void ExecuteCommand(Command* c) { c->Execute(); }
};

int main() {
  Receive3* r3 = new Receive3;
  Receive2* r2 = new Receive2;
  Receive1* r1 = new Receive1;

  Command* pc1 = new ConcreteCommand1(r3);
  Command* pc2 = new ConcreteCommand2(r2);
  Command* pc3 = new ConcreteCommand3(r1);

  Invoker* pInv = new Invoker();

  pInv->ExecuteCommand(pc1);
  pInv->ExecuteCommand(pc2);
  pInv->ExecuteCommand(pc3);

  delete r1;
  delete r2;
  delete r3;
  delete pc1;
  delete pc2;
  delete pc3;
  delete pInv;
}