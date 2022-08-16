/**
 * @file flyweight.cc
 * @author Jamishon
 * @brief Roles: Flyweight, ConcreteFlyWeight, UnsharedConcreteFlyweight,
 * FlyweihtFactory, Client.
 *        Tips: Efficiently support a large number of intensively
 * used objects using sharing techniques.
 * @version 0.1
 * @date 2022-08-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <map>
#include <vector>

class Context;
class Flyweight {
 public:
  virtual ~Flyweight() {}
  virtual void Operation(Context& ct){};
};

class Context {
 public:
  Context(std::ostream& os) : output(os) {}

  void Print() {
    for (std::vector<Flyweight*>::iterator it = flyweights_.begin();
         it != flyweights_.end(); it++) {
      Flyweight* p = *it;
      p->Operation(*this);
    }
  }

  std::ostream& OutputStream() { return output; }

  void AddFlyweight(Flyweight* p) { flyweights_.push_back(p); }

 private:
  std::ostream& output;
  std::vector<Flyweight*> flyweights_;
};

class ConcreteFlyweightA : public Flyweight {
 public:
  ConcreteFlyweightA(char a) : c_(a) {}

  virtual void Operation(Context& ct) {
    std::ostream& os = ct.OutputStream();
    os << c_;
  }

  friend bool operator==(char c, const ConcreteFlyweightA& a) {
    return c == a.c_;
  }

  friend bool operator==(const ConcreteFlyweightA& a, char c) { return c == a; }

 private:
  char c_;
};

class ConcreteFlyweightB : public Flyweight {
 public:
  ConcreteFlyweightB(int num) : color_num_(num) {}

  virtual void Operation(Context& ct) {
    std::ostream& os = ct.OutputStream();
    os << color_num_;
  }

  friend bool operator==(int c, const ConcreteFlyweightB& b) {
    return c == b.color_num_;
  }

  friend bool operator==(const ConcreteFlyweightB& b, int c) { return c == b; }

 private:
  int color_num_;
};

class UnsharedConcreteFlyweightC : public Flyweight {
 public:
  UnsharedConcreteFlyweightC(unsigned int pos) : position_(pos) {

  }
  
  void AddFlyweightPair(ConcreteFlyweightA* pa, ConcreteFlyweightB* pb) {
    mp_ab_.insert(std::make_pair(pa, pb));
  }

  void Operation(Context& ct) {
    std::ostream& os = ct.OutputStream();
    for (std::map<Flyweight*, Flyweight*>::iterator it = mp_ab_.begin();
         it != mp_ab_.end(); it++) {
      os << "\033[38;5;";
      it->second->Operation(ct);
      os << "m";
      it->first->Operation(ct);
      os << "\033[m";
    }
  }

 private:
  std::map<Flyweight*, Flyweight*> mp_ab_;
  unsigned int position_;
};

class FlyweightFactory {
 public:
  ~FlyweightFactory() {
    for (std::vector<ConcreteFlyweightA*>::iterator it = vc_a_.begin();
         it != vc_a_.end(); it++) {
      if (*it) delete *it;
    }

    for (std::vector<ConcreteFlyweightB*>::iterator it = vc_b_.begin();
         it != vc_b_.end(); it++) {
      if (*it) delete *it;
    }

    for (std::vector<UnsharedConcreteFlyweightC*>::iterator it = vc_c_.begin();
         it != vc_c_.end(); it++) {
      if (*it) delete *it;
    }
  }

  ConcreteFlyweightA* GetFlyweightA(char c) {
    for (std::vector<ConcreteFlyweightA*>::iterator it = vc_a_.begin();
         it != vc_a_.end(); it++) {
      if (**it == c) return *it;
    }
    ConcreteFlyweightA* pa = new ConcreteFlyweightA(c);
    vc_a_.push_back(pa);

    return pa;
  }

  ConcreteFlyweightB* GetFlyweightB(int color_num) {
    for (std::vector<ConcreteFlyweightB*>::iterator it = vc_b_.begin();
         it != vc_b_.end(); it++) {
      if (**it == color_num) return *it;
    }
    ConcreteFlyweightB* pb = new ConcreteFlyweightB(color_num);
    vc_b_.push_back(pb);

    return pb;
  }

  UnsharedConcreteFlyweightC* GetFlyweightC(int pos) {
    UnsharedConcreteFlyweightC* pc = new UnsharedConcreteFlyweightC(pos);
    vc_c_.push_back(pc);

    return pc;
  }

 private:
  std::vector<ConcreteFlyweightA*> vc_a_;
  std::vector<ConcreteFlyweightB*> vc_b_;
  std::vector<UnsharedConcreteFlyweightC*> vc_c_;
};

int main() {
  FlyweightFactory factory;
  std::string content("FLYWEIGHT\nDESIGNPATTERN\n");
  ConcreteFlyweightA* pa = NULL;
  ConcreteFlyweightB* pb = NULL;
  UnsharedConcreteFlyweightC* pc = NULL;
  Context ct(std::cout);
  for (int i = 0; i < content.size(); i++) {
    pa = factory.GetFlyweightA(content[i]);
    pb = factory.GetFlyweightB(i + 1);
    pc = factory.GetFlyweightC(i);
    pc->AddFlyweightPair(pa, pb);
    ct.AddFlyweight(pc);
  }

  ct.Print();

}