/**
 * @file chainofresponsibility.cc
 * @author Jamishon
 * @brief Roles: Handler, ConcreteHandler, Client.
 *        Tips: Make objects a chain, and requests are passed along the chain
 * until resolved.
 * @version 0.1
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

class Request {
 public:
  enum Number { kPrint, kSound, kColor, kNone };

  Number request_id_;

  void DoTask() {
    switch (request_id_) {
      case kPrint:
        std::cout << "Hello World !" << std::endl;
        break;
      case kSound:
        std::cout << "Bi~ bi~ bi ~" << std::endl;
        break;
      case kColor:
        std::cout << "\033[38;5;"
                  << "10"
                  << "m"
                  << "Color !"
                  << "\033[m" << std::endl;
        break;
      case kNone:
        std::cout << "None !" << std::endl;
      default:
        break;
    }
  }
};

class Handler {
 public:
  Handler(Handler* ph, Request::Number id) : aim_id_(id), successor_(ph) {}

  virtual void HandlerRequest(Request* request) {
    if (successor_) successor_->HandlerRequest(request);
  }

  virtual void SetHandler(Handler* ph, Request::Number aim_id) {
    successor_ = ph;
    aim_id_ = aim_id;
  }

 protected:
  Handler* successor_;
  Request::Number aim_id_;
};

class ConcreteHandler1 : public Handler {
 public:
  ConcreteHandler1(ConcreteHandler1* ph, Request::Number id)
      : parent_(ph), Handler(ph, id) {}

  void HandlerRequest(Request* request) { Handler::HandlerRequest(request); }

 protected:
  ConcreteHandler1* parent_;
};

class ConcreteHandler2 : public ConcreteHandler1 {
 public:
  ConcreteHandler2(ConcreteHandler1* ph, Request::Number id)
      : ConcreteHandler1(ph, id) {}

  void HandlerRequest(Request* request) {
    if (request->request_id_ == aim_id_) {
      std::cout << "ConcreteHandler2 handler request:" << aim_id_ << std::endl;
      request->DoTask();
    } else {
      std::cout << "ConcreteHandler2 transfer request to parent:"
                << request->request_id_ << std::endl;
      parent_->HandlerRequest(request);
    }
  }
};

class ConcreteHandler3 : public ConcreteHandler1 {
public:    
  ConcreteHandler3(Handler* ph, Request::Number id)
      : ConcreteHandler1(NULL, id) {
    successor_ = ph;
  }

  void HandlerRequest(Request* request) {
    if (request->request_id_ == aim_id_) {
      std::cout << "ConcreteHandler3 handler request:" << aim_id_ << std::endl;
      request->DoTask();
    } else {
      std::cout << "ConcreteHandler3 transfer request to next: "
                << request->request_id_ << std::endl;
      Handler::HandlerRequest(request);
    }
  }
};

class ConcreteHandler4 : public Handler {
public:    
  ConcreteHandler4(Handler* ph, Request::Number id) : Handler(NULL, id) {
    successor_ = ph;
  }

  void HandlerRequest(Request* request) {
    if (request->request_id_ == aim_id_) {
      std::cout << "ConcreteHandler4 handler request:" << aim_id_ << std::endl;
      request->DoTask();
    } else {
      std::cout << "ConcreteHandler4 transfer request to next: "
                << request->request_id_ << std::endl;
      Handler::HandlerRequest(request);
    }
  }
};

int main() {
    ConcreteHandler1* p1 = new ConcreteHandler1(NULL, Request::kNone);
    ConcreteHandler2* p2 = new ConcreteHandler2(p1, Request::kPrint);
    ConcreteHandler3* p3 = new ConcreteHandler3(p2, Request::kColor);
    ConcreteHandler4* p4 = new ConcreteHandler4(p3, Request::kSound);
    Request* pRequest = new Request();
    pRequest->request_id_ = Request::kPrint;
    p4->HandlerRequest(pRequest);

    pRequest->request_id_ = Request::kColor;
    p4->HandlerRequest(pRequest);

    pRequest->request_id_ = Request::kSound;
    p4->HandlerRequest(pRequest);


    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete pRequest;

 }