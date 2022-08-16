/**
 * @file singleton.cc
 * @author Jamishon
 * @brief Role: Singleton.
 *        Tips: Only one.
 * @version 0.1
 * @date 2022-08-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <pthread.h>

#include <iostream>

#define LOCAL_STATIC 0
#define LAZY_INIT 0
#define HUNGERY_INIT 1

#if LOCAL_STATIC

//local static variable
//Delcare the static variable in static fucntion, thread safey, Effective C++ item 4 by Scott Meyers
//attention: both constructor and desconstructor are executed
class Singleton {
 public:
  static Singleton& getInstance() {
    static Singleton instance;
    return instance;
  }

 protected:
  Singleton() { std::cout << "Singleton" << std::endl; }
  virtual ~Singleton() { std::cout << "~Singleton" << std::endl; }

 private:
  Singleton(const Singleton&);
  Singleton operator=(const Singleton&);
};

#elif LAZY_INIT

// Lazy initialize
// Double check and lock, thread safey
//attention: only  constructor executed
class Singleton {
 public:
  static Singleton& getInstance() {
    if (instance == NULL) {   // Only check the null
    
      pthread_mutex_lock(&mutex_);

      if (instance == NULL) { //Stop other threads to execute new Singleton again when they acqurie the lock
        instance == new Singleton;
      }
      pthread_mutex_unlock(&mutex_);
    }

    return *instance;
  }

 protected:
  Singleton() { std::cout << "Singleton" << std::endl; }
  virtual ~Singleton() { std::cout << "~Singleton" << std::endl; }

 private:
  Singleton(const Singleton&);
  
  Singleton operator=(const Singleton&);

  static Singleton* instance;
  static pthread_mutex_t mutex_;
};

Singleton* Singleton::instance = NULL;
pthread_mutex_t Singleton::mutex_ = PTHREAD_MUTEX_INITIALIZER;

#elif HUNGERY_INIT

//hungery initialize, 
//Delcare and initialize the static variable, thread safey
//attention: only  constructor executed
class Singleton {
 public:
  static Singleton& getInstance() { return *instance; }

 protected:
  Singleton() { std::cout << "Singleton" << std::endl; }
  virtual ~Singleton() { std::cout << "~Singleton" << std::endl; }

 private:
  Singleton(const Singleton&);

  Singleton operator=(const Singleton&);

  static Singleton* instance;
};

Singleton* Singleton::instance = new Singleton;

#endif

int main() { Singleton& p = Singleton::getInstance(); }