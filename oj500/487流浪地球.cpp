/*
 *
题目描述
流浪地球计划在赤道上俊宇步数了N个专项发动机，按位置顺序编号为 0 - N-1
1 初始状态下所有发动机都是未启动状态；
2 发动机启动的方式分为 "手动启动" 和 "关联启动" 两种方式；
3 如果在时刻1 一个发动机被启动，下一时刻与之相邻的两个发动机会被关联启动。
4 如果准备启动某个发动机时，它已经被启动了，则什么都不用做；
5 发动机0与发动机N-1是相邻的。
地球联合政府准备挑选某些发动机在某些时刻进行 "手动启动"， 当然最终所有发动机都会被启动。
所以哪些发动机最晚被启动呢？

输入
第1行输入N, E， 分别代表发动即总个数，和计划手动启动的发动机个数
接下来E行， 每行是时两个数字， T 和 P， 分别代表发动机手动启动时刻，和 发动机位置编号
输出
第1行一个数字N，以回车结束， N代表最后别启动的发动机个数
第2行N个数字，中间有空格，以回车结束，每个数字代表发动机的位置编号，从小到大排序。

样例1
输入
8 2
0 2
0 6

0 1 2 3 4 5 6 7
    x       x
  x   x   x   x
x       x


输出
2
0 4

说明：
8个发动机,时刻0启动2和6号发动机

样例2
输入
8 2
0 0
1 7

0 1 2 3 4 5 6 7
x
  x           x
    x       x
      x   x
        x
输出
1
4

说明：
8个发动机,时刻0 手动启动0, 时刻1手动启动7

 *
 * */

#include "iostream"
#include "vector"
#include "unordered_map"
#include "unordered_set"
#include "algorithm"
using namespace std;

int main() {
  int N; // 发动机总数
  int E; // 手动启动的个数

  cin >> N >> E;
  vector<pair<int, int>> manulStarts(E);
  for (int i = 0; i < E; i++) {
    cin >> manulStarts[i].first >> manulStarts[i].second; // 所有手动启动的信息
  }

  unordered_map<int, unordered_set<int>> startInfo; // 某个时刻启动了哪些机器
  for (int i = 0; i < manulStarts.size(); i++) {
    startInfo[manulStarts[i].first].insert(manulStarts[i].second);
  }

  int preTime = 0;
  int count = 0;
  vector<bool> status(N, false); // 发动机是否启动标记
  for (int curTime = 0; curTime < N ; curTime++) { // 模拟时间运行
    if (startInfo.find(curTime) != startInfo.end()) { // 该时间，存在要启动的机器，则启动他们
      vector<int> nextIds;
      for (int curId : startInfo[curTime]) {
        if(status[curId]) { // 加入在这个时间，发现 status 已经被执行过了， 则忽略
          continue;
        }
        count++; // 启动计数
        status[curId] = true; // 启动机器
        int nextId = (curId + 1) % N;  // 记录相邻机器
        int preId = (curId - 1 + N) % N;
        nextIds.push_back(nextId);
        nextIds.push_back(preId);
      }

      for (int inId : nextIds) {  // 将相邻的且没有启动的机器加入到 curTime+1 的时间的启动 集合中
        if (!status[inId]) {
          startInfo[curTime+1].insert(inId); // 设置到下一哥启动时间
        }
        if (!status[inId]) {
          startInfo[curTime+1].insert(inId);
        }
      }

      if (count == N) { // 如果所有机器都启动，则结束
        preTime = curTime;
        break;
      }
    }
  }

  vector<int> res;
  for (int curId : startInfo[preTime]) {
    res.push_back(curId);
  }

  cout << res.size() << endl;
  sort(res.begin(), res.end());
  for (int i = 0; i < res.size(); i++) {
    cout << res[i];
    if (i != res.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}