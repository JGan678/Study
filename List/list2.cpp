#include <iostream>

typedef enum state { ok = 0, out_of_space, out_of_range, not_found } state;

class Expression {
 private:
  class Node {
   private:
    Node *nxt;
    int coef;
    int exp;

   public:
    friend Expression;
    Node(int c = 0, int e = 0, Node *p = nullptr) : coef(c), exp(e), nxt(p) {}
    Node(Node &n) : nxt(nullptr), coef(n.coef), exp(n.exp) {}  //复制构造函数
    Node(Node *n) : nxt(nullptr), coef(n->coef), exp(n->exp) {}

    friend std::ostream &operator<<(std::ostream &os, const Expression &eq);
  } * head, *tmp;

 public:
  Expression() {
    head = new Node;
    head->nxt = head;
    tmp = head;
  }
  Expression(Expression &eq) {
    head = new Node;
    if (eq.head->nxt == eq.head)  //链表为空
    {
      head->nxt = head;
      return;
    }
    Node *p = head;
    for (Node *t = eq.head->nxt; t != eq.head; t = t->nxt)  //逐项复制, 连接
    {
      p->nxt = new Node(t);
      p = p->nxt;
    }
    p->nxt = head;  //尾节点指向头
    tmp = head;
  }
  ~Expression() {
    Node *p = head, *q = p->nxt;
    while (q != head) {
      delete p;
      p = q, q = q->nxt;
    }
    delete p;
  }
  void rf()  //重置暂存指针(插入算法用到)
  {
    tmp = head;
  }
  friend std::ostream &operator<<(std::ostream &os, const Expression &eq) {
    Node *t = eq.head->nxt;
    if (t == eq.head)  //为空
      return os;
    if (t->exp == 0)  //常数项
      os << t->coef;
    else  //非常数项
      os << t->coef << "x^" << t->exp;
    for (t = t->nxt; t != eq.head; t = t->nxt)  //逐项输出
      os << " + " << t->coef << "x^" << t->exp;
    return os;
  }

  state ins(int c, int e)  //插入,O(n)
  {
    rf();
    return ins_c(c, e);
  }
  state ins_c(int c, int e)  //连续插入
  {
    Node *p = tmp->nxt;
    while (true) {
      if (p == head)  // tmp为尾节点
      {
        tmp->nxt = new Node(c, e, head);  //在尾部插入
        p = tmp->nxt;
        return ok;
      } else if (p->exp < e)  //没到
      {
        tmp = p, p = p->nxt;   //移向下一个
      } else if (p->exp == e)  //与已有项指数相等
      {
        if ((p->coef += c) == 0)  //系数相加后为0
        {
          tmp->nxt = p->nxt;  //删除节点
          delete p;
          p = tmp->nxt;
        }
        return ok;
      } else  //到了
      {
        tmp->nxt = new Node(c, e, p);  //在tmp与p间插入
        p = tmp->nxt;
        return ok;
      }
    }
  }
  Expression &operator+(Expression &eq)  //加法,O(n)
  {
    if (head->nxt == head)  //其中之一为空
      return Expression(eq);
    if (eq.head->nxt == eq.head) return Expression(*this);
    Expression ep(eq);  //复制一个对象
    for (Node *t = head->nxt; t != head;
         t = t->nxt)  //将另一个对象中每个值插到新对象内
      ep.ins_c(t->coef, t->exp);
    return ep;
  }

  Expression &operator*(Expression &eq)  //乘法,O(n^2)
  {
    Expression ep;                                     //创建空对象
    if (head->nxt == head || eq.head->nxt == eq.head)  //其中一个为空
      return ep;
    int c, e;
    for (Node *p = head->nxt; p != head;
         p = p->nxt)  //遍历两个链表元素,相乘后插入新建的对象内
    {
      c = p->coef, e = p->exp;
      for (Node *q = eq.head->nxt; q != eq.head; q = q->nxt)
        ep.ins_c(q->coef * c, q->exp + c);
      ep.rf();
    }
    return ep;
  }
};
