/*
 *
题目描述
华为商城举办了一个促销活动，如果某顾客是某疫苗内最早下单的顾客(可能是多个人)，则可以获取免单。
请你编程计算有多少顾客可以获取免单。
 *
 * 样例1
输入
3
2019-01-01 00:00:00.001
2019-01-01 00:00:00.002
2019-01-01 00:00:00.003


输出
1

说明：
样例1中，三个订单都是同一秒内下单，只有第一个订单最早下单， 可以免单。


 *
 *
 * 样例2
输入
3
2019-01-01 08:59:00.123
2019-01-01 08:59:00.123
2018-12-28 10:08:00.999




输出
3


说明：
样例2中,前两个订单是同一秒内同一时刻(也是最早)下单,都可免单,第三个订单是当前秒内唯一个订单 (也是最早)，也可免单。


 *
 * 样例3
输入
6
2019-01-01 00:00:00.004
2019-01-01 00:00:00.004
2019-01-01 00:00:01.006
2019-01-01 00:00:01.006
2019-01-01 00:00:01.005
2019-01-01 00:00:01.005






输出
3



说明：
样例3中,前两个订单是同一秒内同一时刻(也是最早)下单,第三第四个订单不是当前秒内最早下单，可免单，第五个订单可以免单。

 *
 * */

#include <iostream>
#include "vector"
#include "algorithm"
using namespace std;



typedef struct Mtime_t {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int ms;
}Mtime;

class MyCmp {
public:
    bool operator()(Mtime &t1, Mtime &t2) {
      if (t1.year != t2.year) {
        return t1.year < t2.year;
      } else if (t1.month != t2.month) {
        return t1.month < t2.month;
      } else if (t1.day != t2.day) {
        return t1.day < t2.day;
      } else if (t1.hour != t2.hour) {
        return t1.hour < t2.hour;
      } else if (t1.minute != t2.minute) {
        return t1.minute < t2.minute;
      } else if (t1.second != t2.second) {
        return t1.second < t2.second;
      } else {
        return t1.ms < t2.ms;
      }
    }
};

int main() {
  int n;
  string str;
  getline(cin, str);
  n = stoi(str);
  vector<string> arr(n);
  // 获取所有时间
  for (int i = 0; i < n; i++) {
    getline(cin, arr[i]);
  }

  vector<Mtime> times(n);

  // 将时间字符串解析为Mtime
  for (int i = 0; i < arr.size(); i++) {
    sscanf(arr[i].c_str(), "%d-%d-%d %d:%d:%d.%d", &times[i].year, &times[i].month, &times[i].day, &times[i].hour, &times[i].minute, &times[i].second, &times[i].ms);
  }

  // 对时间进行排序
  sort(times.begin(), times.end(), MyCmp());

  // 获取所有免单
  // 1 和前面不同 y, m, d, h , m, s
  // 2 和前面同 s， 且 ms 一样， 且前面是当前s 的第一个

  int ret = 0;
  bool flagNewSecond = false;
  for (int i = 0; i < times.size(); i++) {
    if (i == 0) {
      ret++;
      flagNewSecond = true;
      continue;
    }

    if (times[i].year != times[i-1].year) {
      ret++;
      flagNewSecond = true;
    } else if (times[i].month != times[i-1].month) {
      ret++;
      flagNewSecond = true;
    } else if (times[i].day != times[i-1].day) {
      ret++;
      flagNewSecond = true;
    } else if (times[i].hour != times[i-1].hour) {
      ret++;
      flagNewSecond = true;
    } else if (times[i].minute != times[i-1].minute) {
      ret++;
      flagNewSecond = true;
    } else if (times[i].second != times[i-1].second) {
      ret++;
      flagNewSecond = true;
    } else  {
      // 判断ms
      if (times[i].ms == times[i-1].ms) {
        // 如果和前面是相同的秒，且ms 也相等， 且i-1 是免单的.
        if (flagNewSecond) { // 如果 i-1 是免单
          ret++;
        }
      } else {
        // 如果 ms 不等
        flagNewSecond = false; // ms 和 i-1 不一样，则不免单了
      }
    }
  }

  cout << ret << endl;

  return 0;
}