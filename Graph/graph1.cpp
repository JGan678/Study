#include <iostream>
#include <queue>

typedef enum class state : unsigned int
{
  ok = 0,
  err,
  val_invalid,
  not_found,
  not_present,
  duplicate,
} state;

template <class ele_t>
class Gph
{
  ele_t **a;
  const int n;
  int e;
  ele_t no;

public:
  Gph(int size, ele_t noEdge) : n(size), e(0), no(noEdge)
  {
    a = new ele_t *[n];
    for (int i = 0; i < n; i++) //初始化邻接表
    {
      a = new ele_t[n];
      for (int j = 0; j < n; j++)
        a[i][j] = no;
    }
  }
  ~Gph()
  {
    for (int i = 0; i < n; i++) //空间释放
      delete[] a[i];
    delete[] a;
  }

  state find(int u, int v) //判断边是否存在
  {
    if (u < 0 || v < 0 || u >= n || v >= n || u == v)
      return state::val_invalid;
    else if (a[u][v] == no)
      return state::not_found;
    else
      return state::ok;
  }
  state ins(int u, int v, ele_t w) //插入边
  {
    if (u < 0 || v < 0 || u >= n || v >= n || u == v)
      return state::val_invalid; //防错
    else if (a[u][v] != no)      //已经存在
      return state::duplicate;
    else
    {
      a[u][v] = w; //插入
      e++;
      return state::ok;
    }
  }
  state del(int u, int v)
  {
    if (u < 0 || v < 0 || u >= n || v >= n || u == v)
      return state::val_invalid; //防错
    else if (a[u][v] == no)
      return state::not_present; //不存在
    else
    {
      a[u][v] = no; //删除
      e--;
      return state::ok;
    }
  }

  void DepthT(std::ostream &os) //深度优先遍历
  {
    int i, j;
    bool flag = true;        //是否完成一个节点的遍历
    bool *tvs = new bool[n]; //是否完成特定节点
    for (i = 0; i < n; i++)
      tvs = true;
    for (i = 0; i < n; i++)
      if (tvs[i]) //从每个未遍历节点开始
      {
        flag = false;
        while (true)
        {
          os << i;
          tvs[i] = true;
          for (j = 0; j < n; j++) //深度优先遍历
            if (tvs[j] && a[i][j] != no)
            {
              flag = false;
              i = j;
              break;
            }
          if (flag)
            break;
        }
      }
  }
  void BreadthT(std::ostream &os) //广度优先遍历
  {
    int i, j;
    std::queue<int> q;       //存储待遍历节点
    bool *tvs = new bool[n]; //是否完成特定节点
    for (i = 0; i < n; i++)
      tvs = true;
    for (i = 0; i < n; i++)
      if (tvs[i])
      {
        os << i;
        tvs[i] = false;
        for (j = 0; j < n; j++)
          if (tvs[j] && a[i][j] != no) //将所有可达节点加入队列
            q.push(j);
        while (!q.empty())
        {
          i = q.front(); //取队首
          q.pop();
          if (tvs[i]) //判断未遍历
          {
            os << i;
            tvs[i] = false;
            for (j = 0; j < n; j++)
              if (tvs[j] && a[i][j] != no)
                q.push(j);
          }
        }
      }
  }
};
