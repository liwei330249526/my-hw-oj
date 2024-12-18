/*
 *
题目描述
近些年来，我国防砂治沙取得显著成果，某沙漠新种植N棵胡杨，编号 1-N， 排成一排，一个月后，有M棵胡杨未能成活，现可补种胡杨K棵，请问如何补种
（只能补种，不能新种），可以取得最多的连续胡杨树。
 输入
 第一行，N， 共N棵树
 第二行，M，M棵未成活
 第三行，M个数字，空格分隔，代表未成活的树的数量
 第四行，K，可补种K棵

 输出
 最多连续的胡杨棵树

 样例2
 输入
10
3
2 4 7
1

输出
6
说明：
补种第7棵树，最多连续胡杨树棵数位6 (5,6，8,9,10)

5
2
2 4
1


 *
 * */

#include "iostream"
#include "sstream"
#include "vector"
#include "unordered_map"
using namespace std;

int main() {
  int N; // 共N 棵树
  int M; // M 棵未活
  int K; // 可补种 K棵
  cin >> N >> M;

  vector<int> arr(M);
  for (int i = 0; i < M; i++) {
    cin >> arr[i];
  }

  cin >> K;

  unordered_map<int, int> Mdict; // 未成活字典
  for (int i = 0; i < arr.size(); i++) {
    Mdict[arr[i]-1] = 1; // 未成活的 索引
  }
  // 滑动窗口        2 4 7
  int left = 0;
  int right = 0;
  int count = 0;
  int res = 0;
  while (right < N) { // 除了第一次外，每次将left 边界递进，递进时判断如果是未成活，则count计数减1， right 向右扩
    if (right != 0) {
      if(Mdict[left] == 1) {
        count--;
      }
      left++;
    }

    while (right < N && count <= K) { // 循环right递进，递进过程中判断如果是未成活，则count计数加1
      if (Mdict[right]) {            //  如果count <= K, [left, right] 中的未成活计数是符合要求的； 则记录一个做大边界范围
        count++;
      }
      if (count <= K) {
        res = max(res, right - left + 1);
      }

      right++;
    }
  }

  cout << res << endl;


  return 0;
}