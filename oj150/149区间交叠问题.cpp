/*
 *
题目描述
给定坐标轴上的一组线段，线段的起点和终点均为整数并且长度不小于1，请你从中找到最少数量的线段，这些线段可以覆盖住所有线段。

输入
第一行输入线段数量 n
接着n行输入n个线段，格式为 x y

输出
最少线段数量

 *
 * 样例1
 * 输入
3
1,4
2,5
3,6



输出
2

 *
 * 样例2
 * 输入
3
1,7
2,5
10,16



输出
2




1
6,2

 *
 * */

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  int n;
  cin >> n;

  // 读取所有线
  vector<vector<int>> lines(n, vector<int>(2));
  int a;
  int b;
  string str;
  for (int i = 0; i < n; i++) {
    cin >> str;
    int id = str.find(',');
    a = stoi(str.substr(0, id));
    b = stoi(str.substr(id+1));
    if (a > b) {
      swap(a, b);
    }
    lines[i][0] = a;
    lines[i][1] = b;
  }

  // 排序
  sort(lines.begin(), lines.end(), [](vector<int> &l1, vector<int> &l2) {
    return l1[0] < l2[0];
  });

  int preEnd = lines[0][1];
  int ret = 1;
  for (int i = 1; i < lines.size(); i++) {
    if (preEnd <= lines[i][0]) { // 如果i 的 start 大于 之前的 end， 则是新的线
      preEnd = max(preEnd, lines[i][1]) ;
      ret++;
    } else {
      if(lines[i][1] <= preEnd) { // 如果i 的end 小于或等于 preEnd， 则完全被覆盖
        continue;
      } else { // 有交叠
        int endT = lines[i][1];
        while (i+1 < lines.size() && lines[i+1][0] <= preEnd ) { // 遍历所有有交叠的线， 在循环过程中会记录一个最大的end
          endT = max(endT, lines[i+1][1]);
          i = i+1;
        }
        preEnd = endT;
        // 结束时， i 是符合条件的 (i+1 < lines.size() && lines[i+1][1] <= preEnd )， 不影响 for 中的下次 i++

        ret++;
      }
    }
  }

  cout << ret << endl;

  return 0;
}