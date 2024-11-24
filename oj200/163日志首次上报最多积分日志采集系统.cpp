/*
 *
题目描述
日志采集是运维系统的核心组件，日志是按行生成，每行做一条，由采集系统分批上报。
如果上报太频繁，会对服务器造成压力；
如果上报太晚，会降低用户体验；
如果一次上报条数太多，导致超市失败。

为此，项目组设计了如下的上报策略：
1 每成功上报一日志，奖励1分
2 每条日志每延迟上报1秒，扣1分
3 积累日志达到100条，必须立即上报。

给出日志序列，根据该规则，计算首次上报能获得最多积分数。

输入
按时序产生的日志条数 T1， T2 ... Tn, 其中 1<=n<=1000, 0 <=Ti <= 100.

输出
首次上报最多能获得的积分数
 *
 * 样例1
 * 输入
1 98 1

输出
98

说明：
T1时刻上报得1分
T2时刻上报得98分,最大
T3时刻上报得0分


 *
 * 样例2
 * 输入
50 60 1

输出
50


说明：
如果第1个时刻上报,获得积分50
如果第2个时刻上报,最多上报100条,前50条延迟上报1s,每条扣除1分,共获得积分为100-50=50

 *
 * 样例3
 * 输入
  3 7 40 10 60

    3  10 50 60 120

       prePreSum=3
       preSum=10
       sum=50


           prePreSum=3
           prePresum=10
           preSum=50
           sum=60

输出
37


说明：
T1时刻上报得3分

T2时刻上报得7分

T3时刻上报得37分，最大

T4时刻上报得-3分

T5时刻上报，因为已经超了100条限制，所以只能上报100条,得-23分

 *
 * */

#include "iostream"
#include "vector"
#include "string"
#include "sstream"
//3 7  40 10 60
//3 10 50 60 120   前缀和，包括自己, [i] 天提交，能提交多少个？
//3 13 63 123 243  前缀和的前缀和

using namespace std;
int main() {
  string str;
  getline(cin ,str);
  vector<int> arr;
  string token;
  stringstream stm(str);
  while (getline(stm, token, ' ')) {
    arr.push_back(stoi(token));
  }

  int preSum = 0; // 到当前秒之前的总条数
  int sum = 0;    // 到当前秒的总条数
  int ret = 0;
  int nMinus = 0; // 当前秒提交，需要减的分数
  for(int i = 0; i < arr.size(); i++) {
    preSum = sum;
    sum += arr[i];

    if (sum >= 100) {
      sum = 100;
      nMinus += preSum;
      ret = max(ret, sum - nMinus);
      break;
    }

    nMinus += preSum;
    ret = max(ret, sum - nMinus);
  }
  cout << ret << endl;

  return 0;
}

