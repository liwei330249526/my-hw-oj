/*
 *
题目描述
某个打印机根据打印队列执行打印任务；打印任务分为9个优先级，分别用数字1-9表示，数字越大优先级越高，打印机每次从队列头部
取出一个任务A，然后检查队列余下有没有比A优先级更高的任务，如果有比A优先级高的任务，则将任务A放到队列的尾部，都则就执行
任务A 的打印。
请编写一个程序，根据输入的打印队列，输出实际的打印顺序。

输入
输入一行，为每个任务的优先级，优先级之间用逗号隔开，优先级取值范围是1-9
输出一行，为每个任务的打印顺序，打印顺序从0开始，用逗号隔开。

 *
 * 样例1
 * 输入
9,3,5

输出
0,2,1


说明：
队列头部任务的优先级为9，最先打印，故序号为0;
接着队列头部任务优先级为3，队列中还有优先级为5的任务，优先级3任务被移到队列尾部;
接着打印优先级为5的任务,故其序号为1; .
最后优先级为3的任务的序号为2

 *
 * 样例2
 * 输入
1,2,2

输出
2,0,1


说明：
队列头部任务的优先级为1，被移到队列尾部；接着顺序打印两个优先级为2的任务，故其序号分别为0和1；最后打印剩下的优先级为1的任务，其序号为2

 *
 *
 * 思路
 * prirority_que
 *
 * que
 * 模拟
 *
 * Task{优先级， index}
 * que的第[0]个， 判断是否是优先级（优先级）最大的；如果是最大的，则设置该任务（index）的打印顺序
 *
 * */

#include "iostream"
#include "string"
#include "queue"
#include "vector"
#include "string"
#include "sstream"
using namespace std;

// 任务
typedef struct Task_t {
    int priority;
    int index;
}Task;

class MyCompare {
public:
    bool operator()(Task &t1, Task &t2) {
      return t1.priority < t2.priority;
    }
};

int main() {
  // 获取字符串
  string str;
  getline(cin, str);

  // 获取数字数组
  string token;
  vector<int> arr;
  stringstream stm(str);
  while (getline(stm, token, ',')) {
    arr.push_back(stoi(token));
  }

  // 获取队列和堆
  queue<Task> que;
  priority_queue<Task, vector<Task>, MyCompare> priQue;
  for (int i = 0; i < arr.size(); i++) {
    Task t = Task{arr[i], i};
    que.push(t);
    priQue.push(t);
  }

  // 模拟
  int printIndex = 0;
  vector<int> retPrint(arr.size()); // 记录所有的执行顺序
  while (!que.empty()) { // 队列不为空
    // 获取que的第一个
    Task t = que.front();
    que.pop();
    if (t.priority == priQue.top().priority) { // 如果任务t的优先级是最大的，则记录它的执行顺序
      priQue.pop();
      retPrint[t.index] = printIndex;
      printIndex++;
    } else {
      que.push(t);
    }
  }

  for (int i = 0; i < retPrint.size(); i++) {
    cout << retPrint[i];
    if (i != retPrint.size()-1) {
      cout << ",";
    }
  }
  cout << endl;

  return 0;
}