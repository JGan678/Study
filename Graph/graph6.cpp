#include <cstdarg>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
// pair of several elements
template <class ty = int, int len = 2>
class pir
{
protected:
  ty *dat;

public:
  pir()
  {
    dat = new ty[len];
    for (int i = 0; i < len; ++i)
    {
      dat[i] = (ty) nullptr;
    }
  }
  pir(ty vr, ...)
  {
    dat = new ty[len];
    dat[0] = vr;
    va_list ap;
    va_start(ap, vr);
    for (int i = 1; i < len; ++i)
      dat[i] = va_arg(ap, ty);
    va_end(ap);
  }
  ~pir() { delete[] dat; }
  ty operator[](int n) { return dat[n]; }
};
typedef std::vector<class pir<int>> pirv;
// the graph
class biGph
{
protected:
  const int x, y; // the size of x and y node group
  bool **adj;     // adjacency matrix
  int *mx, *my;   // the pair of x and y group in staggered tree

public:
  biGph(int x, int y) : x(x), y(y)
  {
    int i, j;
    // allocate space
    adj = new bool *[y];
    for (i = 0; i < y; ++i)
    {
      adj[i] = new bool[x];
      for (j = 0; j < x; ++j)
        adj[i][j] = false;
    }
    mx = new int[x], my = new int[y];
    vy = new bool[y];
  }
  // input value
  void setVal(pirv &ipt)
  {
    for (int i = 0; i < ipt.size(); ++i)
      if (ipt[i][0] < x && ipt[i][1] < y)
        adj[ipt[i][1]][ipt[i][0]] = true;
  }
  // find maximum match
  void match()
  {
    rstMch();
    preMch();
    bpMch();
  }

private:
  bool *vy; // record visited node in travesal
  int c;    // record matching progress

  // match obvirous pairs
  void preMch()
  {
    c = 0;
    for (int i = 0; i < x; ++i)
      if (mx[i] == -1) // not matched
        for (int j = 0; j < y; ++j)
          if (my[j] == -1 && adj[i][j]) // could be matched
          {
            mx[i] = j;
            my[j] = i;
            c++;
            break;
          }
  }
  // do complete match and make staggered tree with DFS
  void bpMch()
  {
    for (int i = 0; i < x; ++i)
      if (mx[i] == -1)
      {
        for (int k = 0; k < y; ++k)
          vy[k] = false;
        if (makeTr(i))
          c++;
      }
  }
  bool makeTr(int i)
  {
    for (int j = 0; j < y; ++j)
      if (adj[i][j] && !vy[j])
      {
        vy[j] = true;
        if (my[j] == -1 || makeTr(my[j]))
        {
          mx[i] = j; // find the route
          my[j] = i;
          return true;
        }
      }
    return false;
  }
  // reset the matched group
  void rstMch()
  {
    int i;
    for (i = 0; i < x; ++i)
      mx[i] = -1;
    for (i = 1; i < y; ++i)
      my[i] = -1;
  }
};
// input and output
int main()
{
  int x, y;
  class pir<int> tmp;
  pirv dt;
  cout << "please input the number of x and y node group" << endl;
  cin >> x >> y;
  class biGph gph(x, y);
  cout << "please input the edges" << endl;
  while (cin >> tmp[0] >> tmp[1])
    dt.emplace_back(tmp);
  gph.setVal(dt);
  gph.match();
};
