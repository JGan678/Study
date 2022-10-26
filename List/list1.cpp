#include <iostream>

typedef enum state { ok = 0, out_of_space, out_of_range, not_found } state;

template <typename T>
class List {
 private:
  class Node {
   private:
    Node *nxt;
    T data;

   public:
    friend List;
    Node(T d = nullptr, Node *p = nullptr) : data(d), nxt(p) {}

    friend std::ostream &operator<<(std::ostream &os, const List &eq);
  } * head;
  int n;

 public:
  List() : n(0) { head = new Node((T) nullptr, nullptr); }
  ~List() {
    Node *p = head, *q = p->nxt;
    while (q != nullptr) {
      delete p;
      p = q, q = q->nxt;
    }
    delete p;
  }
  friend std::ostream &operator<<(std::ostream &os, const List &eq) {
    Node *t = eq.head->nxt;
    if (t == nullptr)  //链表为空
      return os;
    os << t->data;
    for (t = t->nxt; t != nullptr; t = t->nxt)  //遍历输出
      os << ' ' << t->data;
    return os;
  }
  state ins(T d, int l = 0)  //插入,O(n)
  {
    if (l < 0 || l > n) return out_of_range;
    int i;
    Node *p = head;
    for (i = 0; i < l; i++)  //找到末尾
      p = p->nxt;
    Node *q = new Node(d, p->nxt);  //插入
    p->nxt = q;
    n++;
    return ok;
  }
  state rm(int l)  //删除,O(n)
  {
    if (n == 0 || l < 0 || l > n) return out_of_range;
    Node *p = head;
    for (int i = 0; i < l; i++)  //找到待删除位置
      p = p->nxt;
    Node *q = p->nxt;
    p->nxt = q->nxt;  //删除
    delete q;
    n--;
    return ok;
  }
  state invert()  //逆置,O(n)
  {
    switch (n)  //特殊情况
    {
      case 0:
      case 1:
        return ok;
      case 2:
        head->nxt->nxt->nxt = head->nxt;
        head->nxt = head->nxt->nxt;
        head->nxt->nxt->nxt = nullptr;
        return ok;
    }
    Node *t, *q, *p;
    p = head->nxt;
    t = p->nxt;  //处理最尾端
    head->nxt->nxt = nullptr;
    while (t) {
      q = t->nxt;  //处理中间部分
      t->nxt = p;
      p = t;
      t = q;
    }
    head->nxt = p;  //处理最前端
    return ok;
  }
  state sort()  //排序,O(n^2)
  {
    switch (n)  //特殊情况
    {
      case 0:
      case 1:
        return ok;
      case 2:
        Node *p = head, *q = p->nxt, *r = q->nxt;
        if (q->data > r->data) {
          p->nxt = r;
          r->nxt = q;
          q->nxt = nullptr;
        }
        return ok;
    }
    //冒泡排序
    bool t = true;
    Node *p, *q, *r;
    while (t) {
      t = false;                         //判断是否发生交换
      p = head, q = p->nxt, r = q->nxt;  //从头遍历
      while (r) {
        if (q->data > r->data)  //比较相邻两个值
        {
          q->nxt = r->nxt;
          p->nxt = r;
          r->nxt = q;
          p = r, r = q->nxt;
          if (!t) t = true;
        } else
          p = q, q = r, r = r->nxt;
      }
    }
    return ok;
  }
};
