#include <iostream>
#include <string>
using std::string;

string lcs(const string &a, const string &b) {
  if (a.empty() || b.empty()) return string();
  //初始化参数,创建表
  const int la = a.length(), lb = b.length();
  int table[la + 1][lb + 1];
  char *lcs;
  int i, j, k;
  //初始化表,设定初值
  for (i = 0; i <= la; i++) table[i][0] = 0;
  for (j = 0; j <= lb; j++) table[0][j] = 0;
  //计算lcs,若出现相同元素,则lcs长度加一同时ij移动,若非,lcs长度不变并分别移动ij
  for (i = 1; i <= la; i++)
    for (j = 1; j <= lb; j++) {
      if (a[i - 1] == b[j - 1])
        table[i][j] = table[i - 1][j - 1] + 1;
      else if (table[i - 1][j] >= table[i][j - 1])
        table[i][j] = table[i - 1][j];
      else
        table[i][j] = table[i][j - 1];
    }
  //依照计算过程输出lcs元素,即lcs长度变化的点
  i = la, j = lb, k = table[la][lb];
  lcs = new char[k + 1];
  lcs[k] = '\0';
  while (k > 0) {
    if (table[i][j] == table[i - 1][j])
      i--;
    else if (table[i][j] == table[i][j - 1])
      j--;
    else {
      lcs[--k] = a[i - 1];
      i--, j--;
    }
  }
  return string(lcs);
}

void bag(int n, const int *w, const int *v, const int wt) {
  int table[wt];
  int i, j;
  for (i = 0; i < wt; i++) table[i] = 0;
  for (i = 0; i < n; i++)
    for (j = wt - 1; j >= 0; j--)
      if (table[j] < table[j - w[i]] + v[i]) table[j] = table[j - w[i]] + v[i];
  for (j = wt - 1; j >= 0; j--) {
  }
}

int main() {
  string a("xzyzzyx");
  string b("zxyyzxz");
  std::cout << lcs(a, b);
  return 0;
}
