#include <iostream>
#include <queue>
#include <stack>

typedef enum state
{
  ok = 0,
  error_value,
} state;

template <typename key_t>
class Tree
{
  struct Node
  {
    key_t k;
    Node *c1, *c2;

  public:
    friend Tree;
    Node(key_t k) : k(k), c1(nullptr), c2(nullptr) {}
  } * root;

public:
  Tree() : root(nullptr) {}
  ~Tree() { del(root); }
  void del(Node *n)
  {
    if (!n)
      return;
    del(n->c1);
    del(n->c2);
    delete n;
  }

  //先序插入
  Tree(key_t *key, int len)
  {
    std::queue<Node **> q; //暂存插入位置的队列
    Node **tmp;
    root = new Node(key[0]); //插入第一个元素
    q.push(&(root->c1));     //处理初始条件
    q.push(&(root->c2));
    for (int i = 1; i < len; i++) //逐项插入
    {
      tmp = q.front();
      q.pop();
      *tmp = new Node(key[i]);
      q.push(&((*tmp)->c1));
      q.push(&((*tmp)->c2));
    }
  }

  std::ostream &preorder(std::ostream &os)
  {
    //不断向左下的平行线
    Node *tmp = nullptr;
    std::stack<Node *> s; //储存待遍历节点
    s.push(root);         //入栈生成初始状态
    while (!s.empty())
    {
      tmp = s.top(); //取下一个待遍历元素
      s.pop();
      while (tmp)
      {
        os << " " << tmp->k << " "; //输出
        if (tmp->c2)                //若有右节点,压入待遍历栈
          s.push(tmp->c2);
        tmp = tmp->c1; //向左遍历
      }
    }
    return os;
  }

  std::ostream &inorder(std::ostream &os)
  {
    Node *tmp = root;
    std::stack<Node *> s;
    for (; tmp->c1; tmp = tmp->c1) //寻找最小节点
      s.push(tmp);                 //入栈
    while (true)
    {
      //已输出节点会在回溯时直接跳过,故无需判断
      os << " " << tmp->k << " "; //输出
      if (tmp->c2)                //若存在右孩子
      {
        tmp = tmp->c2;                 //转到右孩子
        for (; tmp->c1; tmp = tmp->c1) //查找右子树最小元素
          s.push(tmp);                 //入栈
      }
      //子树遍历完成,开始回溯
      else if (!s.empty()) //双亲存在
      {
        tmp = s.top(); //已输出不会入栈
        s.pop();
      }
      else
        break;
    }
    return os;
  }

  std::ostream &postorder(std::ostream &os)
  {
    postorder_b(root, os);
    return os;
  }

private:
  void postorder_b(Node *tmp, std::ostream &os)
  {
    if (!tmp)
      return;
    postorder_b(tmp->c1, os);
    postorder_b(tmp->c2, os);
    os << " " << tmp->k << " ";
  }

public:
  int total()
  {
    int n = 0;
    //不断向左下的平行线
    Node *tmp = nullptr;
    std::stack<Node *> s; //储存待遍历节点
    s.push(root);         //入栈生成初始状态
    while (!s.empty())
    {
      tmp = s.top(); //取下一个待遍历元素
      s.pop();
      while (tmp)
      {
        n++;
        if (tmp->c2) //若有右节点,压入待遍历栈
          s.push(tmp->c2);
        tmp = tmp->c1; //向左遍历
      }
    }
    return n;
  }

  int leaf()
  {
    int n = 0;
    //不断向左下的平行线
    Node *tmp = nullptr;
    std::stack<Node *> s; //储存待遍历节点
    s.push(root);         //入栈生成初始状态
    while (!s.empty())
    {
      tmp = s.top(); //取下一个待遍历元素
      s.pop();
      while (tmp->c1)
      {
        if (tmp->c2) //若有右节点,压入待遍历栈
          s.push(tmp->c2);
        tmp = tmp->c1; //向左遍历
      }
      if (!tmp->c2)
        n++;
    }
    return n;
  }

  int height() { return height_b(root); }

private:
  int height_b(Node *n)
  {
    if (!n)
      return 0;
    int a = height_b(n->c1);
    int b = height_b(n->c2);
    return (a > b ? a : b) + 1;
  }

public:
  void nswap() { nswap_b(root); }

private:
  void nswap_b(Node *n)
  {
    if (!n)
      return;
    nswap_b(n->c1);
    nswap_b(n->c2);
    Node *tmp = n->c1;
    n->c1 = n->c2;
    n->c2 = tmp;
  }
};
