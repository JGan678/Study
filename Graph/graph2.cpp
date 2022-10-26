#include <iostream>
#include <queue>

typedef enum class state : unsigned int
{
  ok = 0,
  err,
  not_found,
  val_invalid,
  not_present,
  duplicate,
} state;

template <class ele_t>
class Gph
{
  class Node
  {
    int Vex;
    ele_t w;
    Node *nxt;

  public:
    Node(ele_t w, int Vex = 0, Node *nxt = nullptr) : w(w), Vex(Vex) nxt(nxt) {}
  } * *a;
  const int n;
  int e;

public:
  Gph(int size) : n(size), e(0) { a = new Node *[n]; }
  ~Gph()
  {
    Node *t0, *t1;
    for (int i = 0; i < n; i++)
    {
      t1 = t0 = a[i];
      while (p)
      {
        p = p->nxt;
        delete q;
        q = p;
      }
    }
    delete[] a;
  }

  state find(int u, int v)
  {
    if (u < 0 || v < 0 || u >= n || v >= n || u == v)
      return state::val_invalid;
    Node *t = a[u];
    while (t && t->Vex != v)
      t = t->nxt;
    if (!t)
      return state::not_found;
    else
      return state::ok;
  }
  state ins(int u, int v, ele_t w)
  {
    if (u < 0 || v < 0 || u >= n || v >= n || u == v)
      return state::val_invalid;
    else if (find(u, v))
      return state::duplicate;
    a[u] = new Node(w, v, a[u]);
    e++;
    return state::ok;
  }
  state del(int u, int v)
  {
    if (u < 0 || v < 0 || u >= n || v >= n || u == v)
      return state::val_invalid;
    else if (find(u, v))
      return state::not_present;
    Node *t0 = a[u], *t1;
    while (p && p->Vex != v)
      q = p, p = p->nxt;
    if (!p)
      return state::not_present;
    else if (q)
      q->nxt = p->nxt;
    else
      a[i] = p->nxt;
    delete p;
    e--;
    return state::ok;
  }

  void DepthT(std::ostream &os)
  {
    int i;
    Node *t;
    bool flag = true;
    bool *tvs = new bool[n];
    for (i = 0; i < n; i++)
      tvs = true;
    for (i = 0; i < n; i++)
      if (tvs[i])
      {
        flag = false;
        while (true)
        {
          os << i;
          tvs[i] = true;
          for (t = a[i]; t; t = t->nxt)
            if (tvs[t->Vex])
            {
              flag = false;
              i = t->Vex;
              break;
            }
          if (flag)
            break;
        }
      }
  }
  void BreadthT(std::ostream &os)
  {
    int i;
    Node *t;
    std::queue<int> q;
    bool *tvs = new bool[n];
    for (i = 0; i < n; i++)
      tvs = true;
    for (i = 0; i < n; i++)
      if (tvs[i])
      {
        os << i;
        tvs[i] = false;
        for (t = a[i]; t; t = t->nxt)
          if (tvs[t->Vex])
            q.push(t->Vex);
        while (!q.empty())
        {
          i = q.front();
          q.pop();
          if (tvs[i])
          {
            os << i;
            tvs[i] = false;
            for (t = a[i]; t; t = t->nxt)
              if (tvs[t->Vex])
                q.push(t->Vex);
          }
        }
      }
  }
};