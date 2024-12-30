/*
 *
题目描述
给定衣柜额数组x 和正整数 k， 请找出使表达式 x[i] - x[i+1] ... - x[i+k-1] ，结果最进阶与数组中位数q 的下表i，如果有多个i满足条件
则返回最大的i

样例1
输入
[50,50,2,3], 2



输出
1

说明:

1、中位数为50：[50,50,2,3]升序排序后变成[2,3,50,50]，中位数为下标4/2=2的元素50

2、计算结果为1：X [50,50,2,3] 根据题目计算X[i] - ... - X[i + k - 1] 得出三个数0 (X[0] - X[1] = 50 - 50) 、48 (X[1] - X[2] = 50 - 2) 和 -1 (X[2]-X[3] = 2 - 3) ，其中48最接近50，因此返回下标1


样例2
输入
[6,6,6,6,6],2

输出
3

 *
 * */


#include "iostream"
#include "sstream"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  string str;
  getline(cin, str);
  string nstr;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] != '[' && str[i] != ']') {
      nstr += str[i];
    }
  }

  stringstream stm(nstr);
  string token;
  vector<int> arr;
  while (getline(stm, token, ',')) {
    arr.push_back(stoi(token));
  }

  int k = arr.back();
  arr.pop_back();

  vector<int> sArr(arr.size());
  sArr = arr;

  sort(sArr.begin(), sArr.end(), [](int a, int b){
    return a < b;
  });

  int mid = 0; // 中位数
//  if (arr.size() % 2 == 0) { // 偶数 0 1 2 3
//    mid = (arr[arr.size()/2-1] + arr[arr.size()/2]) / 2;
//  } else { // 奇数 0 1 2 3 4
//    mid = arr[arr.size()/2];
//  }
  mid = sArr[arr.size()/2];

  int result;
  int count;

  int resResult;
  int resStart;

  for (int i = 0; i + k -1 < arr.size(); i++) { // 从每个位置开始计算, 共k个数字    0 1 2 3 4 5 6 7 8 9
    result = arr[i];
    count = 1; // 一个数字
    for (; count < k;) { // 发现 count == k 的时候， 已经计算了 k 个数字
      result -= arr[i+count]; // - [1]
      count++;
    }

    if (i == 0) {
      resResult = result;
      resStart = 0;
    } else {
      if (abs(mid - result) <= abs(mid - resResult)) { // 如果新的result 更适合
        resResult = result;
        resStart = i;
      }
    }
  }

  cout << resStart << endl;

  return 0;
}
