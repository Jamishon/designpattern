/**
 * @file composite.cc
 * @author Jamishon
 * @brief Roles: Component, Leaf, Composite, Client.
 *        Tips: Objects are organized in to a tree-like structure,
 *        and whloe-part objects have the consistent actions.
 * @version 0.1
 * @date 2022-08-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

class Component {
 public:
  Component(std::string s) : id(s), parent(NULL), children(NULL) {}

  virtual void Operation() { std::cout << id << "--Operation->" << std::endl; }

  virtual int Add(Component* pc) { return -1; }

  virtual int Remove(Component* pc) { return -1; }

  virtual Component* GetChild(int i) { return NULL; }

  virtual Component* GetComposite() { return NULL; }

  virtual void SetParent(Component* p) { parent = p; }

  virtual ~Component() {}

 protected:
  Component* parent;
  std::vector<Component*>* children;
  std::string id;
};

class Composite : public Component {
 public:
  Composite(std::string id) : Component(id) {
    children = new std::vector<Component*>();
  }

  virtual int Add(Component* pc) {
    children->push_back(pc);
    pc->SetParent(this);
    return children->size() - 1;
  }

  virtual int Remove(Component* pc) {
    int i = 0;
    for (std::vector<Component*>::iterator it = children->begin();
         it != children->end(); it++, i++) {
      if (*it == pc) {
        pc->SetParent(NULL);
        children->erase(it);
        return i;
      }
    }
    return -1;
  }

  virtual Component* GetChild(int i) {
    if (i < children->size())
      return children->at(i);
    else
      return NULL;
  }

  virtual Composite* GetComposite() { return this; }

  virtual void Operation() {
    std::cout << "Composite:";
    Component::Operation();
  }
};

class Leaf : public Component {
 public:
  Leaf(std::string id) : Component(id) {}

  virtual void Operation() {
    std::cout << "Leaf:";
    Component::Operation();
  }
};

void PostOrderTraversalRecursive(Component* root) {
  if (root) {
    int index = 0;
    if (root->GetComposite()) {
      Component* pc = NULL;
      while (pc = root->GetChild(index)) {
        PostOrderTraversalRecursive(pc);
        index++;
      }
    }
    root->Operation();
  }
}

void PreOrderTraversalRecursive(Component* root) {
  if (root) {
    root->Operation();
    if (root->GetComposite()) {
      int index = 0;
      Component* pc = NULL;
      while (pc = root->GetChild(index)) {
        PreOrderTraversalRecursive(pc);
        index++;
      }
    }
  }
}

void LevelOrderTraversal(Component* root) {
  if (root) {
    Component* current = NULL;
    Component* pc = NULL;
    int index = 0;
    std::queue<Component*> queue;
    queue.push(root);
    do {
      current = queue.front();
      queue.pop();

      current->Operation();
      
      index = 0;
      while (pc = current->GetChild(index++)) {
        queue.push(pc);
      }

    } while (!queue.empty());
  }
}

void PreOrderTraversal(Component* root) {
  if (root) {
    Component* current = root;
    std::stack<Component*> stack;
    do {
      int index = 0;
      Component* pc = NULL;
      current->Operation();
      if (pc = current->GetChild(index++)) {
        std::vector<Component*> temp;
        while (pc = current->GetChild(index++)) {
          temp.push_back(pc);
        }

        for (std::vector<Component*>::iterator it = temp.end() - 1;
             it >= temp.begin(); it--) {
          stack.push(*it);
        }

        current = current->GetChild(0);
      } else {
        if (!stack.empty()) {
          current = stack.top();
          stack.pop();
        } else {
          current = NULL;
        }
      }
    } while (!stack.empty() || current != NULL);
  }
}

void PostOrderTraversal(Component* root) {
  if (root) {
    Component* current = root;
    std::stack<Component*> stack;
    std::map<Component*, int> visisted;
    do {
      int index = 0;
      Component* pc = NULL;

      if (pc = current->GetChild(index)) {
        std::vector<Component*> temp;
        while (pc = current->GetChild(index++)) {
          temp.push_back(pc);
        }

        int last = temp.size();
        Component* plast = temp.at(last - 1);
        std::map<Component*, int>::iterator it = visisted.find(plast);
        bool visist = false;
        if (it != visisted.end()) {
          if (it->second != 0) visist = true;
        } else {
          visisted.insert(std::pair<Component*, int>(plast, 0));
        }

        if (visist) {
          current->Operation();
          std::map<Component*, int>::iterator itr = visisted.find(plast);
          if (itr != visisted.end()) {
            visisted.erase(it);
            visisted.insert(std::pair<Component*, int>(itr->first, 1));
          }

          if (!stack.empty()) {
            current = stack.top();
            stack.pop();
          } else {
            current = NULL;
          }

        } else {
          stack.push(current);

          temp.erase(temp.begin());
          for (std::vector<Component*>::iterator it = temp.end() - 1;
               it >= temp.begin(); it--) {
            stack.push(*it);
          }
          current = current->GetChild(0);
        }
      } else {
        current->Operation();

        std::map<Component*, int>::iterator it = visisted.find(current);
        if (it != visisted.end()) {
          visisted.erase(it);
          visisted.insert(std::pair<Component*, int>(it->first, 1));
        }

        if (!stack.empty()) {
          current = stack.top();
          stack.pop();
        } else {
          current = NULL;
        }
      }
    } while (current != NULL || !stack.empty());
  }
}

int main() {
  Component* root = new Composite("root a");
  root->Add(new Leaf("leaf b"));
  root->Add(new Leaf("leaf c"));

  Component* pc = new Composite("composite d");
  root->Add(pc);

  root->Add(new Leaf("leaf e"));

  pc->Add(new Leaf("leaf f"));
  pc->Add(new Leaf("leaf g"));
  pc->Add(new Leaf("leaf h"));

  PreOrderTraversalRecursive(root);
  std::cout << std::endl;
  PostOrderTraversalRecursive(root);
  std::cout << std::endl;

  PreOrderTraversal(root);
  std::cout << std::endl;
  PostOrderTraversal(root);
  std::cout << std::endl;

  LevelOrderTraversal(root);
  std::cout << std::endl;
}
