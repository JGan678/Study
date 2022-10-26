#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 300;
int n = maxn, m = maxn, sum = maxn;
int Map[maxn][maxn]; // map[i][j]=1表示X部的i和Y部的j存在匹配
int cx[maxn],        // cx[i]表示X部i点匹配的Y部顶点的编号
    cy[maxn];        // cy[i]表示Y部i点匹配的X部顶点的编号
bool vis[maxn];      //暂存遍历状态

bool dfs(int u) // dfs进入的都是X部的点
{
  for (int v = 0; v < n; v++) //枚举Y部的点，判断X部的u和Y部的v是否存在路径
  {
    //如果存在路径并且还没被标记加入增广路
    if (Map[u][v] && !vis[v]) // vis数组只标记Y组
    {
      //标记加入增广路
      vis[v] = 1;

      if (cy[v] == -1 || dfs(cy[v]))
      {
        cx[u] = v; //可以匹配，进行匹配
        cy[v] = u;
        return 1;
      }
    }
  }
  return 0; //不能匹配
}
int maxmatch() //匈牙利算法主函数
{
  int ans = 0;
  //匹配清空，全部置为-1
  memset(cx, -1, sizeof(cx));
  memset(cy, -1, sizeof(cy));
  for (int i = 0; i < n; i++)
  {
    if (cx[i] == -1) //如果X部的i还未匹配
    {
      memset(vis, 0, sizeof(vis)); //每次找增广路的时候清空vis
      ans += dfs(i);
    }
  }
  return ans;
}

int main()
{
  cout << "输入匹配的两个点集合的数量" << endl;
  cin >> n >> m;
  cout << "输入集合成员间关系数量" << endl;
  cin >> sum;
  cout << "输入两个点集合成员间的连线" << endl;
  int x, y;
  for (int i = 0; i < sum; i++)
  {
    cin >> x >> y;
    Map[x][y] = 1;
  }
  //执行匈牙利算法，输出最大匹配
  cout << maxmatch() << endl;
}