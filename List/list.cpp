#include <iostream>
using std::istream;
using std::ostream;

typedef enum state {
  ok = 0,
  out_of_space,
  out_of_range,
  type_not_match,
  not_found
} state;

template <typename T>
class List {
 private:
  int n;                 //链表长度
  int *order(T &, T &);  //顺序判断,正序为正,相同为0,逆序为负,空为首位
  class Node             //每个链表单元
  {
   private:
    node *next;
    T data;

   public:
    friend List;

    Node(T &d = nullptr, Node *n = nullptr) : data(d), next(n) {}
    Node(Node &nd) : next(nd.next), data(nd.data) {}
    Node(Node *nd) : next(nd->next), data(nd->data) {}
  } * head;  //头指针

 public:
  List() : n(0), head(nullptr) {}
  List(List &ls) : n(ls.n), head(nullptr), order(ls.order) {
    if (ls.head == nullptr) return;
    Node *t, *p;
    t = ls.head;
    head = p = new Node(t);
    t = t->next;
    while (t) {
      p = p->next = new Node(t);
      t = t->next;
    }
  }
  ~List() {
    for (Node *tmp1 = head, *tmp2 = head->next; tmp2;
         tmp1 = tmp2, tmp2 = tmp2->next)
      delete tmp1;
    delete tmp1;
  }

  int ins(T d) {
    Node *ins = new Node(d);
    for () }

  state invert() {
    switch (n) {
      case 0:
      case 1:
        return ok;
      case 2:
        head->next->next = head;
        head = head->next;
        head->next->next = nullptr;
        return ok;
    }
    Node *tmp, *tmpn, *tmpp;
    tmpp = head->next;
    tmp = tmpp->next;
    head->next = nullptr;
    while (tmp) {
      tmpn = tmp->next;
      tmp->next = tmpp;
      tmpp = tmp;
      tmp = tmpn;
    }
    head = tmpp;
    return ok;
  }

  List &operator+=(List ls) {
    if (order != ls.order) {
      throw(type_not_match);
      return *this;
    }
    if (n == 1) {
      if (order(head->data, ls.head->data))
        head->next = ls.head;
      else {
        Node *tmp = ls.head;
        for (; tmp->next; tmp = tmp->next)
          ;
        tmp->next = head;
        head = ls.head;
      }
      return *this;
    }
    head = new Node(nullptr, head);
    Node *t0, *t1, *i1, *i2, *i3;
    for (t0 = head, t1 = head->next, i1 = ls.head; t1 && i1;
         t0 = t1, t1 = t1->next)
      if (order(i1->data, t1->data) >= 0) {
        for (i2 = i1, i3 = i2->next; i3 && order(i3->data, t1->data) >= 0;
             i2 = i3, i3 = i2->next)
          ;
        t0->next = i1;
        i2->next = t1;
        i1 = i3;
      }
    if (i1) t0->next = i1;
    t0 = head;
    head = head->next;
    delete t0;
    return *this;
  }
  List &operator+(List &ls) {
    List o(ls);
    return o += *this;
  }
};
