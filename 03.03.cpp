#include <iostream>
#include <cassert>

class List {
 public:
  bool empty() {
    if (head == nullptr) {
      return true;
    }
    return false;
  }

  void show() {
    Node* node = head;
    while (node != nullptr) {
      std::cout << (*node).val << " ";
      node = (*node).next;
    }
    std::cout << '\n';
  }

  void push_front(int x) {
    Node* node_x = new Node;
    node_x->val = x;
    if (head != nullptr) {
      node_x->next = head;
      head = node_x;
    } else {
      head = node_x;
      tail = node_x;
    }
  }

  void push_back(int x) {
    Node* node_x = new Node;
    node_x->val = x;
    if (tail != nullptr) {
      tail->next = node_x;
      tail = node_x;
    } else {
      head = node_x;
      tail = node_x;
    }
  }

  void pop_front() {
    if (head == nullptr) {
      return;
    }
    if (head->next != nullptr) {
      Node* old = head;
      head = head->next;
      delete old;
    } else {
      delete head;
      head = nullptr;
      tail = nullptr;
    }
  }

  void pop_back() {
    if (head == nullptr) {
      return;
    }
    if (head == tail) {
      pop_front();
      return;
    }
    if (head->next == tail) { 
      delete tail;
      tail = head;
      head->next = nullptr;
      return;
    }
    Node* node = head;
    while (node->next->next != nullptr) {
      node = node->next;
    }
    Node* old = tail;
    tail = node;
    tail->next = nullptr;
    delete old;
  }

  int get() {
    if (head == nullptr) {
      return 0;
    }
    int i{};
    Node* node1 = head;
    Node* node2 = head;
    while (node1 != nullptr) {
      node1 = (*node1).next;
      if (i % 2) {
        node2 = (*node2).next;
      }
      i++;
    }
    return (*node2).val;
  }

  ~List() {
    while (!empty()) {
      pop_front();
    }
  }

 private:
  struct Node {
    int val{};
    Node* next = nullptr;
  };

  Node* head = nullptr;
  Node* tail = nullptr;
};


void test1() {
    List list;
    assert(list.empty() == true);
    list.push_front(10);
    assert(list.empty() == false);
    list.pop_front();
    assert(list.empty() == true);
}

void test2() {
    List list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.pop_front();
    list.pop_front();
    list.pop_front();
    assert(list.empty() == true);
}

void test3() {
    List list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.pop_back();
    list.pop_back();
    list.pop_back();
    assert(list.empty() == true);
}

void test4() {
    List list;
    list.push_back(42);
    assert(list.get() == 42);
    list.push_back(24);
    assert(list.get() == 24);
    list.push_back(100);
    assert(list.get() == 24);
    list.push_back(200);
    list.push_back(300);
    assert(list.get() == 100);
}

void test5() {
    List list;
    list.push_front(2);
    list.push_back(3);
    list.push_front(1);
    list.push_back(4);
    list.pop_front();
    list.pop_back();
    assert(list.empty() == false);
    list.pop_front();
    list.pop_front();
    assert(list.empty() == true);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}
