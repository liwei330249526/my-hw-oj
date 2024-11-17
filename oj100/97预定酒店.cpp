/*
 *
题目描述
放暑假了，小明决定到经典游玩，他在网上搜索了酒店的价格（长度为n的数组A），他的心理价位是x元，请帮他筛选出k个最接近x元的酒店（n>=k>0）,并
由低到高打印酒店的价格。

输入输出
第一行， n,k,x
第二行, A[0]A[1]A[2] ... A[n-1]

输出
从第到高打印筛选出的酒店价格
 *
 * 样例1
输入
10 5 6
1 2 3 4 5 6 7 8 9 10



输出：
4 5 6 7 8


 *
 * 样例2
输入
10 4 6
10 9 8 7 6 5 4 3 2 1



输出：
4 5 6 7


 *
 * 样例3
输入
6 3 1000
30 30 200 500 70 300



输出：
200 300 500


 *
 * */

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

int main() {
  int n;
  int k;
  int x;

  cin >> n >> k >> x;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }


  vector<int> dx(n);
  for (int i = 0; i < dx.size(); i++) {
    dx[i] = abs(arr[i] - x);
  }

  // 根据 arr， dx ， 排序
  vector<int> rank(n);
  for (int i = 0; i < rank.size(); i++) {
    rank[i] = i;
  }

  sort(rank.begin(), rank.end(), [&](int a, int b) -> bool { // a 和 b 代表rank 中的每个数字，也代表索引；通过a，b 找到 dx 对应的值，根据值排序。
    if(dx[a] != dx[b]) {
      return dx[a] < dx[b];
    } else {
      return arr[a] < arr[b];
    }
  });

  // rank 中的数字被排序，第[0] 的值指向的是 dx 中最小的值。

  vector<int> res;
  for (int i = 0; i < k; i++) { // rank 中的值是索引， arr 和 dx 的索引
    res.push_back(arr[rank[i]]);
  }

  sort(res.begin(), res.end());

  for (int i = 0; i < res.size(); i++) {
    cout << res[i];
    if (i != res.size()-1) {
      cout << " ";
    }
  }

  return 0;
}