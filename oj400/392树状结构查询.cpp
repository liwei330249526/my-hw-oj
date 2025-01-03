/*
 *
题目描述
通常使用多行的节点父节点表示一棵树，比如
西安 陕西
陕西 中国
江西 中国
中国 亚洲
泰国 亚洲
输入一个节点后，请打印出来树中它的所有下层节点

输入
第一行输入行数，下面是多行数据，每行以空格区分节点和父节点，接着是查询节点
输出
输出查询节点的所有下层节点。以字典序排序
说明：
树中的节点是唯一的，不会出现两个节点，是同一个名字

样例1
输入
5
b a
c a
d c
e c
f d
c




输出
d
e
f

说明：
c的子节点有d、e
e的子节点有f
所以最终输入d、e、f

样例2
输入
6
b a
c a
d b
e c
g e
x y
a


a: b c
   d e g

输出
b
c
d
e
g

说明：
a的下层结点是b和c
b的下层结点是d
c的下层结点是e
e的下层结点是g


 unordermap<char, vector<char>>
 *
 * */

#include "iostream"
#include "unordered_map"
#include "vector"
#include "algorithm"
using namespace std;
int main() {
  int n;
  cin >> n;
  unordered_map<char, vector<char>> dict;
  char a; // 节点
  char b; // 父节点
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    dict[b].push_back(a); // 将子节点a加入到父节点b 的集合中
  }

  char root;
  cin >> root;

  // 可能有环，则用vis 标记
  unordered_map<char, bool> vis;
  vector<char> ret;
  auto dfs = [&](auto &&dfs, char node){
    // 截止
//    if (dict.find(node) == dict.end()) {
//      return;
//    }
    // 加入集合
    if (vis[node]) { // 如果已经范文了，则返回
      return;
    }
    ret.push_back(node);
    vis[node] = true;

    for (char child : dict[node]) { // 遍历所有子节点
      dfs(dfs, child);
    }
  };

  dfs(dfs, root);
  sort(ret.begin(), ret.end());
  for (int i = 1; i < ret.size(); i++) {
    cout << ret[i] << endl;
//    if(i != ret.size()) {
//      cout << " ";
//    }
  }

//  cout << endl;

  return 0;
}