/*
 * 题目描述
 * 停车场由一横排车位，0代表没有停车，1代表有车。至少停了一辆车在车位上，也至少有一个空位没有停车。
 * 为了防剐蹭，需要停车人找到一个车位，使得距离停车人最近的车辆距离是最大的，返回此时的最大距离。
 *
 * 输出
 * 输出一个整数记录最大距离
 *
输入
1,0,0,0,0,1,0,0,1,0,1


输出
2


说明：

当车停在第3个位置上时，离其最近的的车距离为2（1到3）。

当车停在第4个位置上时，离其最近的的车距离为2（4到6）。

其他位置距离为1。

因此最大距离为2。


 * */


#include "string"
#include "iostream"
#include "sstream"
#include "vector"
using namespace std;
int main() {
  string str;
  getline(cin, str);

  stringstream stm(str);
  string token;
  vector<char> arr;
  while(getline(stm, token, ',')) {
    arr.push_back(token[0]);
  }

  vector<int> left(arr.size());
  vector<int> right(arr.size());

  left[0] = arr.size();
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] == '1') {
      left[i] = 0;
    } else {
      if (i > 0) {
        left[i] = left[i-1] + 1;
      }
    }
  }

  right[arr.size()-1] = arr.size();
  for (int i = arr.size()-1; i >= 0; i--) {
    if (arr[i] == '1') {
      right[i] = 0;
    } else {
      if (i < arr.size()-1) {
        right[i] = right[i+1] + 1;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < arr.size(); i++) {
    ans = max(ans, min(left[i], right[i]));
  }

  cout << ans << endl;
  return 0;
}