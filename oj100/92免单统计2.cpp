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
#include "unordered_map"
using namespace std;

typedef struct Mtime_t {
    int ms;
    int count;
}Mtime;


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


  unordered_map<string, Mtime> dict;
  for (int i = 0; i < arr.size(); i++) {
    int id = arr[i].find('.');
    string key = arr[i].substr(0, id);
    int curMs = stoi(arr[i].substr(id+1));
    if (dict.find(key) != dict.end()) { // 如果存在
      if (curMs < dict[key].ms) { // 如果 i 的ms 更小
        dict[key].ms = curMs;
        dict[key].count = 1;
      } else if (curMs == dict[key].ms){ // 如果 i 的ms 与 dict中 key 的ms 相等
        dict[key].count++;
      }
    } else {
      dict[key] = Mtime{curMs,1}; // 如果不存在
    }
  }

  int ret = 0;
  for (auto &it : dict) {
    ret += it.second.count;
  }
  cout << ret << endl;

  return 0;
}