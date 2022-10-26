#include <queue>
#include <utility>
// #include <iostream>
// #include <Windows.h>
// #include <cstdlib>

typedef int elm;
typedef int INT;

inline void swap(elm *i, elm *j)  //交换指针指向的值
{
  static elm tmp;
  tmp = *i;
  *i = *j;
  *j = tmp;
}

void sort_quick(elm *lst, elm *rst)  //快速排序
{
  typedef std::pair<elm *, elm *> pr;
  elm *i, *j;
  std::queue<pr> que;         //暂存需要排序的每组区间
  elm *led, *red, div;        //工作区间与中值
  que.emplace(pr(lst, rst));  //初始化为表全体
  do                          //存在待排序区间
  {
    led = que.front().first;  //读取区间
    red = que.front().second;
    div = *((led + red) / 2);  //二次取中开销过大,直接定为中位数
    que.pop();
    i = led, j = red;
    do  //移动ij
    {
      do  //右移i直到大于中值
        i++;
      while (*i < div);
      do  //左移j直到小于中值
        j--;
      while (*j > div);
      if (i >= j)  //相遇即结束
        break;
      swap(i, j);  //否则交换
    } while (true);
    if (j != led)  // j即为中值现在位置
    {
      swap(led, j);
      que.emplace(pr(led, j));  //将新的区间存入
    }
    if (j != red) {
      que.emplace(pr(j + 1, red));
    }
  } while (!que.empty());
}

void sort_merge(elm *lst, elm *rst)  //两路合并排序
{
  INT len;
  elm *i, *j, *k;
  elm *bg, *mid, *ed;  //工作区间
  elm *led = lst, *red = rst;
  elm *tmp = new elm[rst - lst];  //暂存数组
  k = tmp;
  for (len = 2; len < rst - lst; len *= 2)  //划分区间长度
  {
    //处理位置标记
    for (bg = led, mid = bg + len, ed = mid + len; ed < red;
         bg = ed, mid = bg + len, ed = mid + len) {
      for (i = bg, j = mid; i < mid && j < ed;) {
        if (*i < *j)  //按照位置标记合并区间元素
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
    //处理最后一部分数据
    if (mid < red)  //剩两路
    {
      for (i = bg, j = mid; i < mid && j < red;) {
        if (*i < *j) {
          *k = *i;
          k++, i++;
        } else {
          *k = *j;
          k++, j++;
        }
      }
      for (; i < mid; k++, i++) *k = *i;
      for (; j < red; k++, j++) *k = *j;
    } else  //剩一路
      for (i = bg; i < red; k++, i++) *k = *i;
    //交换新旧
    led = k, k = red + lst - rst, red = led - lst + rst;
  }
  if (led != lst)
    for (i = lst, j = led; i < rst; i++, j++) *i = *j;
  delete[] tmp;  //删除暂存数组
}

elm *find(elm *lst, elm *rst, INT n) {
  static const int len = 5;
  elm *led = lst, *red = rst, *i, *j, *bg, *ed, *k, div;  //边界们与中值
  n--;
  while (true) {
    //二次取中
    i = led, j = red;
    while (true) {
      if (j - i < len)  //剩余足够短,排序取中
      {
        sort_quick(i, j);
        div = *(i + j / 2);
        break;
      }
      k = i;  //分成长度为len的子列,分别取中值合并到表头
      for (bg = i, ed = bg + len; ed <= j; bg = ed, ed = bg + len) {
        sort_quick(bg, ed);
        swap(bg + len / 2, k++);
      }
      if (ed < j) {
        sort_quick(ed, j);
        swap((ed + j) / 2, k++);
      }
      j = k;  //对表头的中值们继续二次取中
    }
    //按中值分划
    i = led, j = red;
    while (true)  //移动ij
    {
      while (*i < div)  //右移i直到大于中值
        i++;
      do  //左移j直到小于中值
        j--;
      while (*j > div);
      if (i >= j)  //相遇即结束
        break;
      swap(i, j);  //否则交换
    };
    //判断位置
    if (j - led == n)  //找到
      return j;
    else if (j - led > n)  //前段够长
      red = j;
    else  //前端较短
      n -= j - led, led = j + 1;
  }
}

// int main()
// {
//   INT i;
//   std::cout << "请输入待排序关键字个数:\n";
//   std::cin >> i;
//   elm *lst = new int[i];
//   srand((int)time(nullptr));
//   for (elm *j = lst; j < lst + i; j++)
//   {
//     *j = (elm)rand() * INT_MAX;
//   }
//   return state::ok;
//   LARGE_INTEGER start_time, end_time;
//   double dqFreq;
//   LARGE_INTEGER f;
//   QueryPerformanceFrequency(&f);
//   dqFreq = (double)f.QuadPart;
//   QueryPerformanceCounter(&start_time);
//   sort_quick(lst, lst + n), cout << "快速排序"; //sort_merge(lst, lst + n),
//   cout << "两路合并排序"; QueryPerformanceCounter(&end_time); double time =
//   1000000 * (end_time.QuadPart - start_time.QuadPart) / dqFreq; cout <<
//   "的时间为:" << time << "微秒\n"; return 0;
// }