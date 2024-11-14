/*
 * 某学校举行运动会，学生们按编号(1,2,3...n) 进行标识，现需要按身高由低到高排列，对身高相同的人，按体重
 * 由轻到重排列；对于身高体重都相同的人，维持原有的编号顺序关系。轻输出排列后的学生编号。
 *
输入
4
100 100 120 130
40 30 60 50

输出
2 1 3 4


说明：

输出的第一个数字2表示此人原始编号为2，即身高为100，体重为30的这个人。

由于他和编号为1的人身高一样，但体重更轻，因此要排在1前面。


 * */

#include "vector"
#include "iostream"
#include "algorithm"
using namespace std;
int main() {
  int n;
  cin >> n;

  vector<int> height(n);
  vector<int> weight(n);
  vector<int> res(n);
  for (int i = 0; i < n; i++) {
    res[i] = i;
  }

  for (int i = 0; i < n; i++) {
    cin >> height[i];
  }

  for (int i = 0; i < n; i++) {
    cin >> weight[i];
  }

  sort(res.begin(), res.end(), [&](int a, int b) ->bool {
    if (height[a] != height[b]) {
      return height[a] < height[b];
    }

    if (weight[a] != weight[b]) {
      return weight[a] < weight[b];
    }

    return a < b;
  });

  for (int i = 0; i < res.size(); i++) {
    cout << res[i] + 1;
    if (i != res.size()-1) {
      cout << " ";
    }
  }
  cout << "" << endl;

  return 0;
}