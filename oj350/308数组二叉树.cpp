/*
 *
题目描述
二叉树也可以用数组来存储，给定一个数组，树的根节点的值存储在下标1，对于存储在下标N的节点，它的左子节点和右子节点分别存储在2N 和 2*N+1，
并且我们用值-1代表一个节点位空
给定衣蛾一个数组的二叉树，试求出从根节点到最小叶子节点的路径，路径由节点的值组成。

输入
一个数组，代表一个二叉树
输出
从根节点到最小叶子节点的路径的节点值
用力保证最小叶子结点只有一个

样例1
输入
3 5 7 -1 -1 2  4


输出
3 7 2

说明：
最小叶子节点的路径为3 7 2


样例2
输入
5 9 8 -1 -1 7 -1 -1 -1 -1 -1 6

输出
5 8 7 6


说明：
最小叶子节点的路径为5 8 7 6,注意数组仅存储至最后一个非空节点，
故不包含节点"7"右子节点的-1



 *
 * */

#include "iostream"
#include "vector"
#include "sstream"
#include "functional"
#include "stdint.h"
using namespace std;

// 左边为null， 右边为null
bool isLeaf(int id, vector<int> &arr) {
  if ((2 * id + 1 >= arr.size() || arr[2 * id + 1] == -1) &&
      (2 * id + 2 >= arr.size() || arr[2 * id + 2] == -1)) {
    //
    return true;
  }
  return false;
}

int main() {
  string str;
  getline(cin, str);
  stringstream stm(str);
  string token;
  vector<int> arr;
  while (getline(stm, token, ' ')) {
    if(token == "") {
      continue;
    }
    arr.push_back(stoi(token));
  }

  vector<int> res;
  int minLeafValue = INT32_MAX;
  vector<int> path;
//  void (*)(int,::std::vector<int, ::std::allocator<int>> &)
   auto dfs = [&](auto &&dfs, int id, vector<int> pathIn)  {  // 参数加上 &&dfs
    // 过滤越界, 或等于-1， 即 id 非法
    if (id >= arr.size() || arr[id] == -1) {
      return;
    }

    // 记录叶子节点
    if (isLeaf(id, arr)) {
      if (arr[id] < minLeafValue) {
        minLeafValue = arr[id];
        res.clear();
        res.resize(pathIn.size());
        res = pathIn;  // 上面path
        res.push_back(arr[id]); // 加上叶子节点值
      }
      return;
    }

    // 递归左右
    int left = id * 2 + 1;
    int right = id * 2 + 2;
    pathIn.push_back(arr[id]);
    dfs(dfs, left, pathIn);
    dfs(dfs, right, pathIn);
    pathIn.pop_back();
    return;
  };


  dfs(dfs, 0, path);

  for (int i = 0; i < res.size(); i++) {
    cout << res[i];
    if (i != res.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}

