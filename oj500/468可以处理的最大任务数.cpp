/*
 *
题目描述
在某个项目中多个任务（用task 数组表示）需要你处理，其中 tasks[i] = [si, ei], 你可以在 si<=day<=ei 中任意一天处理该任务； 请返回你可以处理的最大任务数
注： 一天可以完成一个任务的处理
输入
第一行为任务数n， 1 <= n <= 100000
随后n行为每个任务的开始时间和结束时间
输出
输出为一个整数，表示可以处理的最大任务数

样例1
输入
3
1 1
1 2
1 3


输出
3

说明:
第一天处理任务1,第二天处理任务2,第三天处理任务3


样例2
输入
3
1 1
1 1
1 1


输出
1

 *
 * */


/*
 *
 * 思路
 * 按 start 排序
 * 建立最小堆
 * 模拟时间递增到 10000， 每天将 start 小于或等于 i 的任务加入最小堆，并将 end 小于 i 的任务pop 出去； 如果最小堆中还有任务则 执行一个任务，并计数
 *
 * */

#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"
using namespace std;

class MSortCompare {
public:
    bool operator()(vector<int> &a, vector<int> &b) {
      return a[0] < b[0];
    }
};

class MPriQueCompare {
public:
    bool operator()(vector<int> &a, vector<int> &b) {
      return a[1] > b[1];  // 子节点 >   父节点；  最小堆
    }
};

int main() {
  int n;
  cin >> n;

  // 获取所有任务
  vector<vector<int>> tasks(n, vector<int>(2));
  for (int i = 0; i < n; i++) {
    cin >> tasks[i][0] >> tasks[i][1];
  }

  // 对任务按 start 排序
  sort(tasks.begin(), tasks.end(), MSortCompare()); // sort 需要加括号

  // 优先队列
  priority_queue<vector<int>, vector<vector<int>>, MPriQueCompare> que;

  // 模拟时间递增
  int ret = 0;
  int taskId = 0;
  for(int i = 1; i <= 100000; i++) {
    // 每天将 start 小于或等于 i 的任务加入最小堆，
    while (taskId < tasks.size() && tasks[taskId][0] <= i) {
      que.push(tasks[taskId]);
      taskId++;
    }

    // 并将 end 小于 i 的任务pop 出去；
    while (!que.empty() && que.top()[1] < i) {
      que.pop();
    }

    // 如果最小堆中还有任务则 执行一个任务，并计数
    if (!que.empty()) {
      ret++;
      que.pop();
    }

    if (que.empty() && taskId == tasks.size()) {
      break;
    }
  }

  cout << ret << endl;

  return 0;
}