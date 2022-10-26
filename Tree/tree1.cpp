#include <iostream>

typedef enum state
{
  ok = 0,
  not_found,
  empty,
  duplicate_element
} state;

template <typename key_t, typename data_t> //键类型,数据类型
class Tree                                 //假的AVL树
{
private:
  class Node
  {
  private:
    key_t key;     //键
    data_t data;   //数据
    Node *p;       //指向双亲
    Node *c1, *c2; //指向孩子(递减)
    int h;         //子树高度
    bool tvs;      //是否已遍历

  public:
    friend Tree;
    Node(key_t k, data_t d, Node *p = nullptr, int h = 0)
        : key(k), data(d), p(p), c1(nullptr), c2(nullptr), h(h) {}
    friend std::ostream &operator<<(std::ostream &os, Tree &t);

  } * root; //根节点

public:
  Tree() : root(nullptr) {}
  ~Tree() //删除比较简单,故直接使用递归
  {
    del(root);
  }

private:
  void del(Node *n)
  {
    if (!n)
      return;
    del(n->c1);
    del(n->c2);
    delete n;
  }

public:
  friend std::ostream &operator<<(std::ostream &os, Tree &t) //输出函数
  {
    //中序遍历
    Tree::Node *tmp = t.root;
    for (; tmp->c1; tmp = tmp->c1) //寻找最小节点
      tmp->tvs = false;            //标记为未输出
    while (true)
    {
      //已输出节点会在回溯时直接跳过,故无需判断
      tmp->tvs = true;                                    //标记为已输出
      os << " <" << tmp->key << "," << tmp->data << "> "; //输出
      if (tmp->c2)                                        //若存在右孩子
      {
        tmp = tmp->c2;                 //转到右孩子
        for (; tmp->c1; tmp = tmp->c1) //查找右子树最小元素
          tmp->tvs = false;            //标记为未输出
      }
      //子树遍历完成,开始回溯
      else if (tmp->p) //双亲存在
      {
        for (tmp = tmp->p; tmp && tmp->tvs;
             tmp = tmp->p) //回溯,并跳过已输出节点(若为空则说明完成遍历)
          ;
        if (!tmp)
          break;
      }
      else
        break;
    }
    return os;
  }

  state rmbig() //删除最大节点
  {
    if (!root) //为空
      return empty;
    Node *tmp = root;
    if (!root->c2) //只有头节点
    {
      if (!root->c1) //没有左子树
      {
        delete root;
        root = nullptr;
        return ok;
      }
      else //把左子树接过去
      {
        tmp = root;
        root = root->c1;
        root->p = nullptr;
        delete tmp;
        return ok;
      }
    }
    for (tmp = root; tmp->c2; tmp = tmp->c2) //找最大节点
      ;
    if (tmp->c1) //有左子树
    {
      tmp->p->c2 = tmp->c1; //接过去
      tmp->c1->p = tmp->p;
    }
    else
      tmp->p->c2 = nullptr; //没有左子树
    delete tmp;
    return ok;
  }

  state ins(key_t &k, data_t &d) //有极大缺陷的插入函数
  {
    if (!root) //若为空
    {
      root = new Node(k, d);
      return ok;
    }
    return ins_b(k, d, root); //向下
  }

private:
  state ins_b(key_t &k, data_t &d, Node *n)
  {
    if (n->key == k) //重复元素
      return duplicate_element;
    if (k < n->key) //比键值小
    {
      if (!n->c1) //没有左孩子,直接插
      {
        n->c1 = new Node(k, d, n);
        return ok;
      }
      return ins_b(k, d, n->c1); //继续查找左孩子
    }                            //比键值大
    if (!n->c2)                  //没有右孩子,直接插
    {
      n->c2 = new Node(k, d, n);
      return ok;
    }
    return ins_b(k, d, n->c2); //继续查找右孩子
  }

public:
  state hcal() //计算每个节点子树高度
  {
    if (!root) //为空
      return ok;
    Tree::Node *tmp = root;
    //重置所有节点数据
    for (; tmp->c1; tmp = tmp->c1) //找到最小节点
      tmp->tvs = false;            //标记为未处理
    while (true)
    {
      //已处理回溯时会直接跳过,不影响
      tmp->tvs = true; //标记为已处理
      tmp->h = 0;      //将高度重置为0
      if (tmp->c2)     //若有右孩子
      {
        tmp = tmp->c2;                 //转到右孩子
        for (; tmp->c1; tmp = tmp->c1) //寻找子树的最小节点
          tmp->tvs = false;
      }
      //子树遍历完成,开始回溯
      else if (tmp->p) //若有双亲
      {
        for (tmp = tmp->p; tmp && tmp->tvs; tmp = tmp->p) //跳过已处理节点
          ;
        if (!tmp)
          break;
      }
      else
        break;
    }
    //开始计算子树高度
    int ht = 0;
    for (tmp = root; tmp->c1; tmp = tmp->c1) //找到最小节点
      tmp->tvs = false;
    while (true)
    {
      //已处理结点回溯时直接跳过
      tmp->tvs = true;
      if (tmp->c2) //若有右孩子
      {
        tmp = tmp->c2;                 //移到右子树
        for (; tmp->c1; tmp = tmp->c1) //找到子树最小节点
          tmp->tvs = false;
      }
      //子树遍历完成,开始回溯
      else if (tmp->p)
      {
        ht = tmp->h + 1; //双亲最小高度比孩子大1
        tmp = tmp->p;    //回溯
        if (tmp->h < ht)
          tmp->h = ht;
        else
          ht = tmp->h;
        for (; tmp && tmp->tvs; tmp = tmp->p, ht++) //跳过已处理节点
        {
          if (tmp->h < ht) //处理新的子树高度影响
            tmp->h = ht;
          else
            ht = tmp->h;
        }
        if (!tmp)
          break;
      }
      else
        break;
    }
  }

  std::ostream &valout(std::ostream &os)
  {
    if (!root)
      return os;
    Tree::Node *tmp = root;
    for (; tmp->c1; tmp = tmp->c1) //找到最小节点
      tmp->tvs = false;
    while (true)
    {
      //已处理节点已跳过
      tmp->tvs = true;
      //输出左子树高度-右子树高度
      os << ' ' << (tmp->c2 ? tmp->c2->h : -1) - (tmp->c1 ? tmp->c1->h : -1)
         << ' ';
      if (tmp->c2) //有右子树
      {
        tmp = tmp->c2;
        for (; tmp->c1; tmp = tmp->c1) //找右子树最小节点
          tmp->tvs = false;
      }
      //子树遍历结束
      else if (tmp->p)
      {
        for (tmp = tmp->p; tmp && tmp->tvs; tmp = tmp->p) //跳过已输出
          ;
        if (!tmp)
          break;
      }
      else
        break;
    }
    return os;
  }

  /*
private:
  //从叶子向根
  state rotate11(Node *k1)
  {
          Node *k0 = k1->p, *k2 = k1->c1;
          k1->c1 = k2->c2;
          if (k2->c2)
                  k2->c2->p = k1;
          k2->c2 = k1;
          k1->p = k2;
          k2->p = k0;
          if (k0->c1 == k1)
                  k0->c1 = k2;
          if (k0->c2 == k1)
                  k0->c2 = k2;
          return ok;
  }
  state rotate22(Node *k1)
  {
          Node *k0 = k1->p, *k2 = k1->c2;
          k1->c2 = k2->c1;
          if (k2->c1)
                  k2->c1->p = k1;
          k2->c1 = k1;
          k1->p = k2;
          k2->p = k0;
          if (k0->c1 == k1)
                  k0->c1 = k2;
          if (k0->c2 == k1)
                  k0->c2 = k2;
          return ok;
  }
  state rotate12(Node *k1)
  {
          Node *k0 = k1->p, *k2 = k1->c2, *k3 = k2->c1;
          k1->c2 = k3->c1;
          if (k3->c1)
                  k3->c1->p = k1;
          k2->c1 = k3->c2;
          if (k3->c2)
                  k3->c2->p = k2;
          k3->c2 = k2;
          k3->c1 = k1;
          k1->p = k2->p = k3;
          if (k0->c1 == k1)
                  k0->c1 = k3;
          if (k0->c2 == k1)
                  k0->c2 = k3;
          k3->p = k0;
          return ok;
  }
  state rotate21(Node *k1)
  {
          Node *k0 = k1->p, *k2 = k1->c1, *k3 = k2->c2;
          k1->c1 = k3->c2;
          if (k3->c2)
                  k3->c2->p = k1;
          k2->c2 = k3->c1;
          if (k3->c1)
                  k3->c1->p = k2;
          k3->c1 = k2;
          k3->c2 = k1;
          k1->p = k2->p = k3;
          if (k0->c1 == k1)
                  k0->c1 = k3;
          if (k0->c2 == k1)
                  k0->c2 = k3;
          k3->p = k0;
          return ok;
  }
  */
};
