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
  no_route,
} state;

template <class ele_t>
class Traffic
{
  class Node
  {
    int vx;
    ele_t w;
    Node *nxt;

  public:
    Node(ele_t w, int vx = 0, Node *nxt = nullptr) : w(w), vx(vx), nxt(nxt) {}
  } * *a;

  const int n;
  int e;

  ele_t **d; //可达权表
  int **r;   //路径表
  bool cal;  //是否需要重新计算

  enum //定义常数
  {
    infty = -1,
  };

public:
  Traffic(int size) : n(size), e(0), cal(true)
  {
    a = new Node *[n];
    d = new ele_t *[n];
    r = new int *[n];
    for (int i = 0; i < n; i++)
    {
      d[i] = new ele_t[n];
      r[i] = new int[n];
      for (int j = 0; j < n; j++)
      {
        d[i][j] = infty;
        r[i][j] = 0;
      }
    }
  }
  ~Traffic()
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
      delete[] d[i];
      delete[] r[i];
    }
    delete[] a;
    delete[] d;
    delete[] r;
  }

public:
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
    cal = true;
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
    cal = true;
    return state::ok;
  }

public:
  state route(int u, int v)
  {
    if (u < 0 || v < 0 || u >= n || v >= n || u == v)
      return state::val_invalid;
    if (cal)
      cal_floyd();        //是否调用计算函数
    if (d[u][v] != infty) //存在路径
    {
      std::cout << d[u][v] << ' '; //输出长度
      std::cout << v;
      int i = r[u][v]; //输出路径
      if (i != u)
        while (true)
        {
          if (r[u][i] == u)
            break;
          i = r[u][i];
          std::cout << '<' << i;
        }
      std::cout << '<' << u;
      return state::ok;
    }
    else
      return state::no_route;
  }

private:
  state cal_floyd()
  {
    int i, j, k;
    Node *ptr;
    ele_t tmp;
    for (i = 0; i < n; i++) //生成初始邻接表
    {
      ptr = a[i];
      if (ptr)
        while (true)
        {
          d[i][ptr->vx] = ptr->w;
          ptr = ptr->nxt;
          if (!ptr)
            break;
        }
    }
    for (i = 0; i < n; i++) //生成初始路径表
      for (j = 0; j < n; j++)
        r[i][j] = (i != j && d[i][j] != infty) ? i : -1;
    for (k = 0; k < n; k++)
      for (i = 0; i < n; i++) //计算
        for (j = 0; j < n; j++)
        {
          tmp = d[i][k] + d[k][j];
          if (tmp < d[i][j])
          {
            d[i][j] = tmp;
            r[i][j] = r[k][j];
          }
        }
    cal = false;
  }
};
