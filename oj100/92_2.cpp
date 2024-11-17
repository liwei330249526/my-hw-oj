#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct Node {
    int year;
    int month;
    int date;
    int hours;
    int minute;
    int second;
    int ms;
};

// 比较函数
int compare(const void *a, const void *b) {
  Node *aa = (Node *)a;
  Node *bb = (Node *)b;

  // 按年份升序排序
  if (aa->year != bb->year) return aa->year - bb->year;
  // 按月份升序排序
  if (aa->month != bb->month) return aa->month - bb->month;
  // 按日期升序排序
  if (aa->date != bb->date) return aa->date - bb->date;
  // 按小时升序排序
  if (aa->hours != bb->hours) return aa->hours - bb->hours;
  // 按分钟升序排序
  if (aa->minute != bb->minute) return aa->minute - bb->minute;
  // 按秒钟升序排序
  if (aa->second != bb->second) return aa->second - bb->second;
  // 按毫秒升序排序
  if (aa->ms != bb->ms) return aa->ms - bb->ms;

  return 0;
}

int main() {
  int n;
  char str[100];
  int index = 0;
  Node node[1000];
  int res = 0;

  // 输入时间节点个数
  cin >> n;
  cin.get();

  // 循环读取时间节点并解析存储
  for (int i = 0; i < n; i++) {
    cin.getline(str, 100);
    sscanf(str, "%d-%d-%d %d:%d:%d.%d", &node[index].year, &node[index].month, &node[index].date,
           &node[index].hours, &node[index].minute, &node[index].second, &node[index].ms);

    index++;
  }

  // 使用自定义比较函数对时间节点进行排序
  qsort(node, index, sizeof(node[0]), compare);

  // 统计不同的时间节点个数
  Node pre = node[0];
  res = 1;
  for (int i = 1; i < index; i++) {
    // 判断是否与前一个时间节点相同，如果不同则计数加一
    if (node[i].year != pre.year ||
        node[i].month != pre.month ||
        node[i].date != pre.date ||
        node[i].hours != pre.hours ||
        node[i].minute != pre.minute ||
        node[i].second != pre.second ||
        node[i].ms != pre.ms) {
      res++;
    }
    pre = node[i];
  }

  // 输出结果
  cout << res << endl;

  return 0;
}


