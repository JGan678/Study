#include <iostream>
using std::cin;
using std::cout;
using std::endl;
template <class TY>
TY *search3(TY *bg, TY *ed, TY x) {
  if (bg > ed) return nullptr;
  if (*bg == x) return bg;
  if (*ed == x) return ed;
  int div;
  TY *p1, *p2, v1, v2;
  while (true) {
    if ((div = (ed - bg) / 3) > 1) {
      if ((v1 = *(p1 = bg + div)) == x)
        return p1;
      else if (v1 > x)
        ed = p1;
      else if ((v2 = *(p2 = ed - div)) == x)
        return p2;
      else if (v2 < x)
        bg = p2;
      else
        bg = p1, ed = p2;
    } else {
      while (++bg != ed)
        if (*bg == x) return bg;
      return nullptr;
    }
  }
}
int main() {
  int x, n, *a, *r;
  cout << "please enter the number of elements" << endl;
  cin >> n;
  a = new int[n];
  cout << "please enter the elements" << endl;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  cout << "please input the element to be searched" << endl;
  cin >> x;
  if ((r = search3<int>(a, a + n, x)) == nullptr)
    cout << "Not Found" << endl;
  else
    cout << r << endl;
  delete[] a;
  return 0;
}
