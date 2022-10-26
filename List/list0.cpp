#include <iostream>

typedef enum state { ok = 0, out_of_space, out_of_range, not_found } state;

template <typename T>
class List {
 private:
  T *list;        //数组首指针
  const int len;  //最大长度
  int used;       //已使用长度

 public:
  List(int n) : len(n), used(0) { list = new T[n]; }
  ~List() { delete[] list; }
  state ins(T d)  //插入值,O(n)
  {
    if (used >= len)  //防错
      return out_of_space;
    list[used] = d;  //在尾端插入
    used++;
    return ok;
  }
  state del(T d)  //删除值,O(n)
  {
    int i;
    for (i = 0; i < used; i++)  //遍历,寻找值
      if (list[i] == d) {
        for (; i < used; i++) list[i] = list[i + 1];
        used--;
        return ok;
      }
    return not_found;
  }
  state rm(int n)  //删除位置,O(n)
  {
    if (n >= used) return out_of_range;
    for (; n < used; n++)  //寻找位置
      list[n] = list[n + 1];
    used--;
    return ok;
  }
  T *find(T d)  //查找值(由于引用不能为空,使用指针),O(n)
  {
    for (int i = 0; i < used; i++)  //遍历找值
      if (list[i] == d) return list + i;
    return nullptr;
  }
  friend std::ostream &operator<<(std::ostream &os, List &l) {
    if (l.used > 0 && l.used < l.len)   //不为空
      for (int i = 0; i < l.used; i++)  //逐项输出
        os << l.list[i] << ' ';
    return os;
  }
};
