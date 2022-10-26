#include <iostream>
#include <vector>

typedef enum class state : int
{
  ok,
  empty,
} state;
//哈夫曼树
template <class key_t, class data_t>
class HTree
{
  class Node
  {
    key_t k;  //权值
    data_t d; //数据

    bool alt;             //为数据节点或虚拟节点
    HTree::Node *c1, *c2; //指向子树的指针

  public:
    friend HTree;
    friend HTree::pQue;
    //构造函数
    Node(key_t k, data_t d, bool a, Node *c1 = nullptr, Node *c2 = nullptr)
        : k(k), d(d), alt(a), c1(c1), c2(c2) {}
    //复制构造函数
    Node(Node *t) : k(t->k), d(t->d), alt(t->alt), c1(t->c1), c2(t->c2) {}
  } * root;

  //优先权队列(有头节点)
  class pQue
  {
    class Node
    {
      key_t k;        //权值
      HTree::Node *t; //哈夫曼树节点

      Node *p, *n; //指向前后节点的指针

    public:
      friend pQue;
      //构造函数
      Node(HTree::Node *t = nullptr, key_t k = 0, Node *p = nullptr,
           Node *n = nullptr)
          : t(t), k(k), p(p), n(n) {}
    } * f;

  public:
    pQue() { f = new Node; }
    ~pQue()
    {
      while (f->n)
      {
        f = f->n;
        delete f->p;
      }
      delete f;
    }

    //插入新节点并排序
    void push(HTree::Node *i)
    {
      key_t k = i->k;     //记录优先级,加速调用
      if (Node *t = f->n) //若不为空
      {
        for (; t->n; t = t->n) //遍历序列,寻找插入点
        {
          if (t->k >= k) //找到插入点
          {
            Node *tmp = new Node(i, k, t->p, t); //生成节点
            t->p->n = tmp;                       //插入
            t->p = tmp;
            return;
          }
        }
        //单独处理遍历到尾节点情况
        if (t->k >= k) //若比尾小
        {
          Node *tmp = new Node(i, k, t->p, t);
          t->p->n = tmp;
          t->p = tmp;
          return;
        } //若比尾大
        t->n = new Node(i, k, t);
        return;
      }
      else //若为空
      {
        f->n = new Node(i, k, f);
        return;
      }
    }

    bool empty() { return f->n == nullptr; }
    HTree::Node *front()
    {
      return f->n->t; //返回头节点
    }
    state pop() //删除头节点
    {
      if (!f->n)
        return state::empty;
      Node *t = f->n;
      f->n = t->n;
      if (f->n)
        f->n->p = f;
      delete t;
      return state::ok;
    }
  };

public:
  ~HTree()
  {
    if (root)
      del(root);
  }
  void del(Node *n)
  {
    if (n->c1)
      del(n->c1);
    if (n->c2)
      del(n->c2);
    delete n;
  }

  //权值数列,值数列,数列长度
  HTree(key_t *k, data_t *d, int n)
  {
    pQue q;
    for (int i = 0; i < n; i++)
      q.push(
          new HTree::Node(k[i], d[i], true)); //生成有效节点,并插入优先权队列中
    if (q.empty())                            //若无有效节点
      return;
    Node *t; //弹出两个,合并,再插入,知道只剩一个节点
    for (t = q.front(), q.pop(); !q.empty(); t = q.front(), q.pop())
    {
      q.push(new Node(t->k + q.front()->k, 0, false, t, q.front()));
      q.pop(); //生成中继节点
    }
    root = t;
  }

  //输出每个值对应编码
  void out(std::ostream &os)
  {
    if (!root)
      return;
    std::vector<bool> s; //储存编码
    out_b(os, root, s);  //递归
  }
  void out_b(std::ostream &os, HTree::Node *t, std::vector<bool> s)
  {
    if (t->alt) //若为有效节点
    {           //输出
      os << t->d << ":";
      for (int i = 0; i < s.size(); i++)
      {
        if (s[i])
          os << '1';
        else
          os << '0';
      }
      os << "; ";
    }
    else //为中继节点
    {
      if (t->c1) //向下遍历
      {
        s.emplace_back(false); //左孩子为0
        out_b(os, t->c1, s);
        s.pop_back();
      }
      if (t->c2)
      {
        s.emplace_back(true); //右孩子为1
        out_b(os, t->c2, s);
      }
    }
  }

  //解码
  std::vector<data_t> &decode(std::vector<bool> &i)
  {
    std::vector<data_t> o;
    if (!root || i.empty())
      return o;
    std::vector<bool>::iterator r = i.begin();
    Node *tmp;
    while (true) //不断循环查找树
    {
      tmp = root;
      while (true) //按照输入序列查找
      {
        if (!*r) // 0为左孩子
          tmp = tmp->c1;
        else // 1为右孩子
          tmp = tmp->c2;
        if (!tmp) //防止序列出错
          return o;
        if (++r == i.end()) //查找下一个,并判断是否查完
        {
          if (tmp->alt)
            o.emplace_back(tmp->d);
          return o;
        }
        if (tmp->alt) //若遇到数据节点
        {
          o.emplace_back(tmp->d); //输出
          break;                  //从头开始
        }
      }
    }
  }
};
