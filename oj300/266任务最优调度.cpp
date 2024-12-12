/*
 *
给定一个正整数数组表示待系统执行的任务列表，数组的米格元素代表一个任务，元素的值表示该任务的类型，请计算执行完所有任务所需的最短时间
任务执行规则如下
1 任务可以按任意顺序执行，且每个任务执行耗时间均为1个事件单位。
2 两个同类型的任务之间必须有长度为N个单位的冷却时间，比如N为2时，在时间K执行了类型3个任务，那么K+1， K+2 两个时间不能执行类型3任务。
3 系统在任何一个单位时间内都可以执行一个任务，或者等待状态。

输入
第一行是整数数组
第二行时冷却时间
输出
所有任务执行完最短时间

样例1
输入
2,2,2,3
2

输出
7

说明：
时间1:执行类型2任务
时间2:执行类型3的任务(因为冷却时间为2,所以时间2不能执行类型2的任务)
时间3:系统等待(仍然在类型2的冷却时间)
时间4:执行类型2任务
时间5:系统等待
时间6:系统等待
时间7:执行类型2任务
因此总共耗时7

样例2
输入
1,1,2,2,3,3,4,4
2

输出
8

样例3
输入
1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,4
2


输出
17


 *
 * */

#include "iostream"
#include "string"
#include "sstream"
#include "vector"
#include "unordered_map"
#include "queue"
using namespace std;

/*
 *
A B C
A B C
A B X
A B X


A B C
A B C
D D

(maxCount-1) * (n+1) + maxCountTime
 *
 * */
int solve1(vector<int> arr, int freeze) {
  // 公式
  unordered_map<int, int> dict;
  int maxCount = -1;
  for (int i = 0; i < arr.size(); i++) {
    dict[arr[i]]++;
    maxCount = max(maxCount, dict[arr[i]]);
  }

  int maxCountTimes = 0;
  for (auto it : dict) {
    if (it.second == maxCount) {
      maxCountTimes++;
    }
  }

  int ret = (maxCount-1) * (freeze+1) + maxCountTimes;
  ret = max(ret, int(arr.size()));

  return ret;
}

/*
 *
堆
2,2,2,3,3,4,4
2

2xx2xx2
3xx3
4xx4
 * */

// 任务
struct Task {
    int type;
    int availableTime;
};

struct CompareTasks {
    bool operator()(Task &l, Task &r) {
//      return l.availableTime < r.availableTime; // 第1个是4， 大堆， 子节点 < 父节点， 大根
      return l.availableTime > r.availableTime; // ， 子节点 > 父节点， 小根
    }
};

// 小根堆测试
int solve2(vector<int> arr, int freeze) {
  priority_queue<Task, vector<Task>, CompareTasks> minHeap;
  for (int i = 0; i < arr.size(); i++) {
    minHeap.push({i, arr[i]});
  }

  while (!minHeap.empty()) {
    auto task = minHeap.top();
    cout << task.availableTime << " ";
    minHeap.pop();
  }
  cout << endl;
  return 0;
}

// 方法2
//2,2,2,3,3,4,4
//2
//
//2xx2xx2
//3xx3
//4xx4
int solve3(vector<int> arr, int freeze) {
  priority_queue<Task, vector<Task>, CompareTasks> minHeap;
  unordered_map<int, int> lastEtime;
  for (int i = 0; i < arr.size(); i++) {
    int avTime;
    if(lastEtime.find(arr[i]) == lastEtime.end()) { // 不存在
      avTime = 1;
    } else {
      avTime = lastEtime[arr[i]] + freeze + 1;
    }
    lastEtime[arr[i]] = avTime;
    minHeap.push({arr[i], avTime});  // 某任务，可执行时间
  }

  int curTime = 1;
  while (!minHeap.empty()) {
    Task t = minHeap.top();
    if (t.availableTime <= curTime) {
      minHeap.pop();
    }

    curTime++;
  }

  return curTime-1;
}

int main() {
  string str;
  cin >> str;
  int freeze;
  cin >> freeze;

  string token;
  vector<int> arr;
  stringstream stm(str);
  while (getline(stm, token, ',')) {
    arr.push_back(stoi(token));
  }
//
//  int ret = solve1(arr, freeze);
//  cout << ret << endl;
  int ret = solve3(arr, freeze);
  cout << ret << endl;
  return 0;
}