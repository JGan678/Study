#include <iostream>
#include <queue>

template <class key_t, class data_t>
class BTree
{
  class Node
  {
    key_t key;
    data_t data;

    Node *p;
    Node *c1, c2;

    bool tvs;

  public:
    friend BTree;
    Node(key_t k, data_t d, Node *p = nullptr, Node *c1 = nullptr,
         Node *c2 = nullptr)
        : key(k), data(d), p(p), c1(c1), c2(c2), tvs(false) {}
  } * root;

public:
  void preT(std::ostream &os)
  {
    if (!root)
      return;
    Node *tmp;
    for (tmp = root; tmp->c1; tmp = tmp->c1)
    {
      tmp->tvs = false;
      os << " <" << tmp->key << "," << tmp->data << "> ";
    }
    while (true)
    {
      tmp->tvs = true;
      if (tmp->c2)
        for (tmp = tmp->c2; tmp->c1; tmp = tmp->c1)
        {
          tmp->tvs = false;
          os << " <" << tmp->key << "," << tmp->data << "> ";
        }
      else if (tmp->p)
      {
        for (tmp = tmp->p; tmp && tmp->tvs; tmp = tmp->p)
          ;
        if (!tmp)
          break;
      }
      else
        break;
    }
  }

  void inT(std::ostream &os)
  {
    if (!root)
      return;
    Node *tmp;
    for (tmp = root; tmp->c1; tmp = tmp->c1)
      tmp->tvs = false;
    while (true)
    {
      os << " <" << tmp->key << "," << tmp->data << "> ";
      tmp->tvs = true;
      if (tmp->c2)
        for (tmp = tmp->c2; tmp->c1; tmp = tmp->c1)
          tmp->tvs = false;
      else if (tmp->p)
      {
        for (tmp = tmp->p; tmp && tmp->tvs; tmp = tmp->p)
          ;
        if (!tmp)
          break;
      }
      else
        break;
    }
  }

  void postT(std::ostream &os)
  {
    if (!root)
      return;
    Node *tmp;
    for (tmp = root; tmp->c1; tmp = tmp->c1)
      tmp->tvs = false;
    while (true)
    {
      tmp->tvs = true;
      if (tmp->c2)
        for (tmp = tmp->c2; tmp->c1; tmp = tmp->c1)
          tmp->tvs = false;
      else if (tmp->p)
      {
        for (tmp = tmp->p; tmp && tmp->tvs; tmp = tmp->p)
          os << " <" << tmp->key << "," << tmp->data << "> ";
        if (!tmp)
          break;
      }
      else
        break;
    }
  }

  void levelT(std::ostream &os)
  {
    if (!root)
      return;
    std::queue<Node *> q;
    Node *tmp;
    q.push(root);
    while (true)
    {
      tmp = q.front();
      os << " <" << tmp->key << "," << tmp->data << "> ";
      if (tmp->c1)
        q.push(tmp->c1);
      if (tmp->c2)
        q.push(tmp->c2);
      q.pop();
      if (q.empty())
        break;
    }
  }
};