/*
 * 题目描述
 * 共n个人在机房，每个人有一个标号（1<= 标号 <=n）,他们分成多个团队，需要你根据收到的m跳消息判定指定的两个人是否
 * 在一个团队中，具体的：
 * 1 消息构成为abc，整数 a,b 分别代表两个人的标号，整数C代表指令
 * 2 c == 0 代表a b 在一个团队内
 * 3 c == 1 代表需要判定a 和b 的关系，如果a 和b是一个团队，则输出 "We are a team", 如果不是
 * 输出 "We are not a team"
 * 4 c 为其他值，或当前 a 或 b 超出 1- n 的范围，则输出 "da pian zi"
 *
 *
 * n m [1, 100000) 范围内
 *
 * 样例1
输入
5 7
1 2 0
4 5 0
2 3 0
1 2 1
2 3 1
4 5 1
1 5 1

输出
We are a team
We are a team
We are a team
We are not a team

 *
 *
 * 样例2
输入
5 6
1 2 0
1 2 1
1 5 0
2 3 1
2 5 1
1 3 2

输出
we are a team
we are not a team
we are a team
dapianzi

 * */


#include "vector"
#include "iostream"
using namespace std;
class UnionFind {
public:
    UnionFind(int n) {
      parents.resize(n+1);
      rank.resize(n+1, 1);
      for (int i = 0; i < parents.size(); i++) {
        parents[i] = i;
      }
    }

    int find(int num) {
      if (parents[num] == num) { // num 就是 root 节点
        return num;
      }

      int root = find(parents[num]); // 将父亲穿进去，找到 root节点
      parents[num] = root; // 更新 num 的父亲是 root
      return root;
    }

    bool merge(int a, int b) {
      int root1 = find(a);
      int root2 = find(b);

      if (root1 == root2) {
        return false;
      }

      if (rank[root1] < rank[root2]) { // root2 大，则root2 为根
        parents[root1] = root2;
      } else if (rank[root2] < rank[root1]) { // root1 大， 则root1 为根
        parents[root2] = root1;
      } else {
        parents[root2] = root1;  // 否则root1 为根，并增加root1 的秩
        rank[root1]++;
      }
      return true;
    }


private:
    vector<int> parents;
    vector<int> rank;
};

int main() {
  int m; // m 个人
  int n; // n 行数据

  cin >> m >> n;

  if(!(m >= 1 && m < 100000 && n >= 1 && n < 100000)) {
    cout << "Null" << endl;
    return 0;
  }

  UnionFind uf(m);

  vector<vector<int>> msgs(n, vector<int>(3));
  for (int i = 0; i < n; i++) {
    cin >> msgs[i][0] >> msgs[i][1] >> msgs[i][2];
  }

  vector<string> res;
  // merge 所有标记为 0 的消息
  int a = 0;
  int b = 0;
  int c = 0;
  for (int i = 0; i < msgs.size(); i++) {
    a = msgs[i][0];
    b = msgs[i][1];
    c = msgs[i][2];
    if (a >= 1 && a <= n && b >= 1 && b <= n && c == 0){
      uf.merge(a, b);
    }
  }


  // 判断 team
  for (int i = 0; i < msgs.size(); i++) {
    a = msgs[i][0];
    b = msgs[i][1];
    c = msgs[i][2];
    if (!(a >= 1 && a <= n && b >= 1 && b <= n)){
      res.push_back("da pian zi");
      continue;
    }

    if (c == 1) {
      if (uf.find(a) == uf.find(b)) {
        res.push_back("We are a team");
      } else {
        res.push_back("We are not a team");
      }
    } else if (c == 0) {
      continue;
    } else {
      res.push_back("da pian zi");
    }
  }

  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << endl;
  }

  return 0;
}