/*
 *
题目描述
A B 两个人把苹果分为两堆，A希望按他的规则等分苹果，他的规则是按照二进制加法计算，并且不计算进位 12+5=9(1100+0101=9), B 的计算规则是十进制加法，
包括正常进位，B 希望在满足A 的情况下获取苹果重最多
输入苹果的数量和每个苹果重量，输出满足A 的情况下B 获取的苹果总重量
如果无法满足A的要求，输出-1

输入
第一行是苹果数量
第二行是每个苹果重量

输出
输出第一行是B 获取的苹果总重量

样例1
 输入
8
7258 6579 2602 6716 3050 3564 5396 1773

输出
35165


 样例2
 输入
3
3 5 6

输出
11


 *
 * */


/*
 * 如果所有苹果的异或为0 ，则最小的苹果 x， 和剩余的其他苹果，可以分为这两堆，因为他们的异或为0
 * */

#include "vector"
#include "iostream"
#include "algorithm"
using namespace std;
int main() {
  // 获取所有苹果
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  // 所有苹果异或
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum = sum ^ arr[i];
  }

  // 如果为0， 则可以任意1个苹果，和剩余的所有苹果分成这两堆
  if (sum == 0) {
    // 排序
    sort(arr.begin(), arr.end());
    int ret = 0;

    // B ， 苹果重，最大
    for (int i = 1; i < arr.size(); i++) {
      ret += arr[i];
    }
    cout << ret << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}



#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

int minimumTimeRequired(const vector<int>& tasks) {
  unordered_map<int, int> lastExecution; // 记录每种任务类型最后执行的时间戳
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  // 优先队列，按照最早可执行时间戳排序，如果时间戳相同，则按照任务类型排序（实际上类型排序在这里不影响结果）

  // 初始化，将所有任务加入队列，设置它们的最早可执行时间戳
  for (int task : tasks) {
    int earliestTime = lastExecution[task] + 3; // 加上冷却时间2和当前任务的执行时间1
    if (lastExecution.find(task) == lastExecution.end()) {
      earliestTime = 1; // 如果任务类型第一次出现，最早可执行时间为1
    }
    pq.push({earliestTime, task});
    lastExecution[task] = earliestTime - 1; // 更新最后执行时间戳（任务实际结束是在earliestTime-1的下一个时间单位）
  }

  int currentTime = 1; // 当前时间戳，从1开始
  while (!pq.empty()) {
    auto [taskTime, taskType] = pq.top();
    pq.pop();
    if (taskTime > currentTime) {
      // 如果当前队列中的最早可执行任务的时间戳大于当前时间戳，说明系统需要等待
      currentTime = taskTime; // 快进到最早可执行任务的时间戳
    }
    // 执行任务，这里不需要更新lastExecution，因为pq中已经按照冷却时间排好了
    currentTime++; // 执行完任务后，时间戳前进到下一个单位
    // 注意：这里不需要再次将任务加入队列，因为每个任务只会被执行一次
  }

  // 由于是从1开始计数的时间戳，所以返回的时间应该是currentTime-1的下一个整数（即完成所有任务后的第一个空闲时间戳）
  // 但由于我们是在每个任务执行完毕后立即将时间戳+1，所以实际上currentTime已经是完成所有任务后的第一个空闲时间戳了
  // 因此，直接返回currentTime作为完成所有任务所需的最短时间（以事件单位计）
  return currentTime;
}

int main() {
  vector<int> tasks = {1, 2, 1, 3, 2, 3, 3}; // 示例任务列表
  cout << "Minimum time required: " << minimumTimeRequired(tasks) << endl;
  return 0;
}