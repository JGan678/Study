#include <cstdlib>  //仅用于随机数
#include <ctime>    //仅用于随机数
#include <iostream>
#include <queue>  //仅用于非递归快排

using std::cin;
using std::cout;
using std::ifstream;
using std::istream;
using std::ofstream;
using std::ostream;

typedef enum class state : int {
  ok = 0,
  err,
  val_exceed,
  val_invalid,
} state;

template <class key_t, class data_t, class INT = long long int>
class List {
  class elm  //数据单元
  {
    key_t key;
    data_t data;

   public:
    friend List;
    elm(key_t k, data_t d = nullptr) : key(k), data(d) {}
    elm(elm &t) : key(t.key), data(t.data) {}
    elm(elm *t) : key(t->key), data(t->data) {}
  };

  INT n;            //存在的元素总数
  const INT n_max;  //最大元素总数
  elm *lst;

  elm *bg, *ed, *med;

 public:
  List(INT maxlen) : n(0), n_max(maxlen) { lst = new elm[n_max]; }
  ~List() { delete lst; }
  state rand(INT len)  //生成随机表
  {
    if (len > n_max)  //防错
      return state::val_exceed;
    n = len;
    srand((int)time(nullptr));  //增加随机度
    for (INT i = 0; i < n; i++) {
      lst[i]->key = (key_t)rand();  //随机赋值
      lst[i]->data = (data_t)rand();
    }
    return state::ok;
  }

 public:
  state sort(int m = 4)  //排序(选择器)
  {
    if (n <= 1) return state::ok;
    switch (m) {
      case 1:
        sort_select();
        break;
      case 2:
        sort_insert();
        break;
      case 3:
        sort_bubble();
        break;
      case 4:
        sort_quick();
        break;
      case 5:
        sort_merge();
        break;
      case 6:
        sort_heap();
        break;
      default:
        return state::val_invalid;
    }
    return state::ok;
  }

 protected:
  inline void swap(elm *i, elm *j)  //交换指针指向的值
  {
    static elm tmp;
    tmp = *i;
    *i = *j;
    *j = tmp;
  }

  void sort_select()  //选择排序
  {
    key_t min;
    elm *loc, *i, *j;
    for (i = lst; i < lst + n; i++) {
      min = i->key, loc = i;
      for (j = i; j < lst + n; j++)  //找最小值
        if (min > j->key) {
          min = j->key;
          loc = j;
        }
      if (loc != i) {
        *loc = *i;
        *i = min;
      }
    }
  }

  void sort_insert()  //直接插入排序
  {
    elm tmp, *i, *j;
    for (i = lst + 1; i < lst + n; i++)  //将数组无序部分逐个插入有序部分
    {
      tmp = *i;  //提出待插入元素
      for (j = i - 1; j >= lst; j--) {
        if (tmp.key < j->key)  //寻找插入位置并移动元素
          *(j + 1) = *j;
        else
          break;
      }
      *(j + 1) = tmp;  //插入
    }
  }

  void sort_bubble()  // 冒泡排序
  {
    bool flag;  //判断结束
    elm tmp, *i;
    while (true)  //每次循环
    {
      flag = true;
      for (i = lst; i < lst + n; i++) {
        if (i->key > (i + 1)->key)  //比较
        {
          swap(i, i + 1);  //交换
          if (flag) flag = false;
        }
      }
      if (flag)  //未发生交换
        break;
    }
  }

  void sort_quick()  //快速排序
  {
    typedef struct pair {
      elm *led, *red;
      pair(elm *l = 0, elm *r = 0) : led(l), red(r) {}
    } pr;
    std::queue<pr> que;  //每组需要进行快排的区间
    elm *i, *j, *led, *red;
    key_t div;                            //快排关键字
    que.emplace(pr(lst, lst + (n - 1)));  //初始化
    do {
      led = que.front()->led;  //读取区间
      red = que.front()->red;
      div = ((led + red) / 2)->key;  //定为中位数
      que.pop();
      i = led, j = red + 1;
      while (true)  //移动ij
      {
        do i++;
        while (i->key < div && i <= red);
        do j--;
        while (j->key > div);
        if (i >= j)  //相遇即结束
          break;
        swap(i, j);  //交换
      }
      if (j != led)  //关键字位置
      {
        swap(led, j);
        que.emplace(pr(led, j - 1));  //将新的区间存入
      }
      if (j != red) que.emplace(pr(j + 1, red));
    } while (!que.empty());  //存在待排序区间
  }

  void sort_merge()  //两路合并排序
  {
    INT len;
    elm *i, *j, *k, *bg, *mid, *ed, *lsted = lst + n;
    elm *tmp = new elm[n];            //暂存数组
    for (len = 2; len < n; len *= 2)  //划分区间长度
    {
      k = tmp;
      tmp = lst;  //将原数组变为待处理
      lst = k;
      for (bg = tmp, mid = bg + len, ed = mid + len; ed < lsted;
           bg = ed, mid = bg + len, ed = mid + len) {  //处理位置标记
        for (i = bg, j = mid; i < mid && j < ed;) {
          if (i->key < j->key)  //按照位置标记合并区间元素
          {
            *k = *i;
            k++, i++;
          } else {
            *k = *j;
            k++, j++;
          }
        }
        for (; i < mid; k++, i++) *k = *i;
        for (; j < ed; k++, j++) *k = *j;
      }
      if (mid < lsted)  //处理最后一部分数据
      {
        for (i = bg, j = mid; i < mid && j < lsted;) {
          if (i->key < j->key) {
            *k = *i;
            k++, i++;
          } else {
            *k = *j;
            k++, j++;
          }
        }
        for (; i < mid; k++, i++) *k = *i;
        for (; j < lsted; k++, j++) *k = *j;
      } else
        for (i = bg; i < lsted; k++, i++) *k = *i;
    }
    delete[] tmp;  //删除暂存数组
  }

  void sort_heap()  //堆排序
  {
    INT i;
    for (i = (n - 2) / 2; i >= 0; i--)  //构造最大堆
      AdjustDown(i, n - 1);
    for (i = ls->n - 1; i > 0; i--) {
      Swap(lst, lst + i);    //交换堆顶与有序部分首元
      AdjustDown(0, i - 1);  //重新构造最大堆
    }
  }
  void AdjustDown(int cur, int brd) {
    INT p = cur, minChild, tmp;
    while (2 * p + 1 <= brd) {
      if ((2 * p + 2 <= brd) && (lst[2 * p + 1].key > lst[2 * p + 2].key))
        minChild = 2 * p + 2;
      else
        minChild = 2 * p + 1;
      if (lst[p].key <= lst[minChild].key)
        break;
      else {
        tmp = lst[p].key;
        lst[p].key = lst[minChild].key;
        lst[minChild].key = tmp;
        p = minChild;
      }
    }
  }
};
