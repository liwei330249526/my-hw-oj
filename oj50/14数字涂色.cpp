/*
 * 题目描述
 * 疫情过后，希望小学开学了，要制作黑板报
 * 黑板上已经写了N个正整数，同学们需要给每个数涂色。
 * 为了让黑板报有学习意思，老师要求同种颜色的所有数都可以被这种颜色中最小的那个数整除。
 * 请计算，虽少需要多少中颜色才能给这N个数进行上色.
 *
 *

输入
4
2 3 4 9

输出
2

说明：
2与4涂一种颜色，4能被2整除；

3与9涂另一种颜色，9能被3整除。

不能4个数涂同一个颜色，因为3与9不能被2整除。所以最少的颜色是两种

 * */


#include "iostream"
#include "vector"
#include "algorithm"
#include "unordered_map"
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  sort(arr.begin(), arr.end());
  int numMax = arr.back();

  unordered_map<int, int> mem;
  int count = 0;
  for (int i = 0; i < arr.size(); i++) {
    int num = arr[i];
    if(mem[num] == 0) { // 不存在, 则染色，染色的时候，将其所有倍数都染色
      count++;

      // 染色
      for (int j = 1; num * j <= numMax; j++) {
        if (mem[num * j] == 0) { // 如果没有染色， 则染色
          mem[num * j] = num;
        }
      }
    } else { // 如果已经染色，则本次循环忽略
      continue;
    }
  }

  cout << count << endl;
  return 0;
}

