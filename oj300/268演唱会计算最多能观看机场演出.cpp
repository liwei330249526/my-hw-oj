/*
 *
题目描述
为了庆祝中国共产党成立100周年，某公园将举行多长文艺表演，很多演出都是同时进行，一个人只能同时观看异常演出，且不能迟到早退，，
由于演出分布在不同的演出场地，所以连续观看的演出最少有15分钟的时间间隔
小明是一个狂热的文艺谜，想观看尽可能多的演出，现给出演出时间表，请帮小明计算他最多能观看几场演出。

输入
第一行为一个数N，表示演出场数，1<=N<=1000, 接下来N行，每行被空格分割的两个整数，
第一个整数T表示演出的开始时间，第二个整数L表示演出的时序时间，T和L的单位为分钟，0 <= T <= 1440, 0 < = 100

输出
输出最多能观看的演出场数

样例1
输入
2
720 120
840 120

输出
1


样例2
输入
2
0 60
90 60

输出
2


 [   ]
    [   ]

  [     ]
    [ ]

  [   ]
      []

  [    ]
           [ ]

按 start 排序
  [              ]             ok
    [      ]                   not ok
               [        ]      not ok

按 end 排序
     [       ]                 ok
  [              ]             not ok
                [      ]       ok

所以应该按 end 排序

 *
 * */

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

// 比较算子
struct SpanCompare {
    bool operator()(vector<int> &sp1, vector<int> &sp2) {
      return sp1[0] + sp1[1] < sp2[0] + sp2[1];
    }
};

int main() {
  int n;
  cin >> n;
  vector<vector<int>> spans(n, vector<int>(2));
  for (int i = 0; i < n; i++) {
    cin >> spans[i][0] >> spans[i][1];
  }

  sort(spans.begin(), spans.end(), SpanCompare());

  int count = 0;
  int lastEnd = 0;
  for (int i = 0; i < spans.size(); i++) {
    if (lastEnd <= spans[i][0]) { // 上次结束时间小于或等于 i 的起始时间
      count++;
      lastEnd = spans[i][0] + spans[i][1] + 15;
    }
  }

  cout << count << endl;

  return 0;
}