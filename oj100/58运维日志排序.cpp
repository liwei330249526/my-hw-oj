/*
 *
题目描述
运维工程师采集到某产品线网运行产生的日志n条，先根据日志时间先后顺序对日志进行排序，日志时间格式为H:M:S.N。
H表示小时(0-23)
M表示分钟(0-59)
S表示秒(0-59)
N表示毫秒(0-999)
时间可能并没有补全，也就是说，01:01:01.001也可能表示为1:1:1.1

输入输出
输入
第一行输入一个整数n表示日志条数,1 <=n<=100000, 接下来行输入n个事件
输出
按时间升序排序后的时间，如果两个时间相同，则保持输入顺序。


 样例1
 输入
2
01:41:8.9
1:1:09.211


输出
1:1:09.211
01:41:8.9


 样例2
 输入
3
23:41:08.023
1:1:09.211
08:01:22.0



输出
1:1:09.211
08:01:22.0
23:41:08.023


 样例3
 输入
2
22:41:08.023
22:41:08.23


输出
22:41:08.023
22:41:08.23



 *
 * */



#include "iostream"
#include "string"
#include "vector"
#include "algorithm"
using namespace std;
typedef struct Mtime_t {
    string str;
    int time;
}Mtime;

int converStr2Num(string str) {
  vector<int> arr;
  int left = 0;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == ':' || str[i] == '.') {
      int num = stoi(str.substr(left, i - left));
      arr.push_back(num);
      left = i+1;
    }
  }

  int num = stoi(str.substr(left, arr.size() - left));
  arr.push_back(num);

  int ret = 0;
  ret = arr[0] * 3600000 + arr[1] * 60000 + arr[2] * 1000 + arr[3];

  return ret;
}

int main() {
  int n;
  cin >> n;
  vector<string> strs(n);
  for (int i = 0; i < n; i++) {
    cin >> strs[i];
  }

  vector<Mtime> times(n);
  for (int i = 0; i < n; i++) {
    times[i].str = strs[i];
    times[i].time = converStr2Num(strs[i]);
  }

  sort(times.begin(), times.end(), [](Mtime &t1, Mtime &t2) {
    return t1.time < t2.time;
  });

  for (int i = 0; i < n; i++) {
    cout << times[i].str << endl;
  }

  return 0;
}