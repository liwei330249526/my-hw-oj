/*
 *
题目描述
1 可用于接龙的单词首字母必须要和前一个单词的尾字母相同；
2 当存在多个首字母相同的单词时，取长度最长的单词，如果长度也相等，则取字典序最小的单词；已经参与接龙的单词不能重复使用
3 先给定一组全部由小写字母组成的单词数组，并指定其中的一个单词作为起始单词，进行单词接龙
请输出最长的单词穿，单词穿是单词拼接而成，中间没有空格

输入
输入的第一行为一个非负整数，表示起始单词在数组中的索引 k
输入的第二行为一个非负数，正表示单词的个数n
接下来n行，分别表示单词数组的单词

输入
输入一个字符串，表示最终拼接的单词串

样例1
输入
0
6
word
dd
da
dc
dword
d

输出
worddwordda

说明：
先确定起始单词word,再接以d开头的且长度最长的单词dword,剩余以d开头且长度最长的有dd、da、 dc, 则取字典序最小的da,所以最后输出worddwordda



样例2
输入
4
6
word
dd
da
dc
dword
d


输出
dwordda

说明：
先确定起始单词dword,剩余以d开头且长度最长的有dd、da、 dc, 则取字典序最小的da,所以最后输出dwordda


样例3
输入
1
3
apple
elephant
tiger

输出
elephanttiger


样例4
输入
0
5
cat
dog
goat
tiger
rat

输出
cattigerrat


样例5
输入
3
6
banana
apple
elephant
tiger
rat
goat

输出
tigerrat

 *
 * */

#include "iostream"
#include "algorithm"
#include "vector"
#include "unordered_map"
using namespace std;

struct MCompareOp {
    bool operator()(string st1, string st2) {
      if (st1.size() != st2.size()) {
        return st1.size() > st2.size(); // 长度最长单词在前
      }

      return st1 < st2; // 字典序最小在前
    }
};

void dfs(vector<string> &path, vector<string> arr, int id,vector<bool> &vis ,unordered_map<int, vector<int>> dict) {
  // 走到这里，则该 id 单词没有访问过，则可以加入到 path 中
  // 当前单词是 id
  vis[id] = true;
  path.push_back(arr[id]);  // 加入path

  vector<int> nextIds = dict[id]; // 所有next
  for (int i = 0; i < nextIds.size(); i++) { // nextIds[i]， 遍历每个next
    // 如果没有访问过，则访问
    if (!vis[nextIds[i]]) {
      dfs(path, arr, nextIds[i], vis, dict);

      // 第一个访问的即可， break
      break;
    }
  }

  vis[id] = false;

}

int main() {
  int k;
  int n;
  cin >> k;
  cin >> n;
  vector<string> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  vector<string> sarr(n);
  sarr = arr;
  sort(sarr.begin(), sarr.end(), MCompareOp());
  int startId = k;
  for (int i = 0; i < sarr.size(); i++) {
    if (sarr[i] == arr[k]) {
      startId = i;
      break;
    }
  }

  vector<bool> vis(arr.size(), false);

  unordered_map<int, vector<int>> dict;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (sarr[i].back() == sarr[j].front()) {
        dict[i].push_back(j);  // i 尾部可连接 j
      }
      if (sarr[i].front() == sarr[j].back()) {
        dict[j].push_back(i); // j 尾部可连接 i
      }
    }
  }
  vector<string> path;
  vis[startId] = true;
  dfs(path, sarr, startId, vis, dict);

  for (int i = 0; i < path.size(); i++) {
    cout << path[i];
  }
  cout << endl;
  return 0;
}