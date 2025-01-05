/*
 *
题目描述
有一种特殊的加密算法，明文为一段数字串，经过密码本查找转换，生成另一端秘闻数字串。
规则如下：
1 明文为一段数字串由 0-9 组成。
2 密码本为数字 0-9 组成的二维数组
3 需要按铭文串的数字顺序在密码本里找到同样的数字串，密码本里的数字串事由相邻的单元格数字组成，上下和左右是相邻的。
注意： 对角线不相邻，同一个单元格的数字不能重复使用。
4 每一位明文对应密文即为密码本中找到的单元格所在的行和列的需要组成的两个数字。
如明文第i位 data[i] 对应密码本单元格为 book[x][y]， 则铭文第i位对应的密文为xy， x 和y 用空格隔开
如果有多条密文，返回字符串最小的密文
如果密码本无法匹配，则返回 "error"

样例1
输入
2
0 3
3
0 0 2
1 3 4
6 6 4


输出
0 1 1 1


样例2
输入
2
0 5
3
0 0 2
1 3 4
6 6 4



输出
error

说明:
找不到 0 5 的序列，返回error


样例3
输入
4
8 2 2 3
4
0 0 2 4
1 3 4 6
3 4 1 5
6 6 6 5



输出
error

说明：密码本中无法匹配

 *
 * */


#include "iostream"
#include "string"
#include "vector"
#include "algorithm"
using namespace std;

vector<vector<int>> dirs{{0,1},{1,0},{0,-1},{-1,0}};
vector<string> res;

void dfs(vector<vector<int>> &cipher, int row, int col, vector<vector<bool>> &vis,
         vector<int> text, int id, vector<pair<int, int>> &path) {
  if (id == text.size()) { // 明文匹配结束了
    // path 中是路径
    string rest;
    for (int i = 0; i < path.size(); i++) { // 获取path 中的密文
      rest += to_string(path[i].first);
      rest += to_string(path[i].second);
    }
    res.push_back(rest);
    return;
  }

  for (int i = 0; i < dirs.size(); i++) {
    int nrow = row + dirs[i][0];
    int ncol = col + dirs[i][1];
    if (nrow >= 0 && nrow < vis.size() && ncol >= 0 && ncol < vis[0].size() &&
        !vis[nrow][ncol] && text[id] == cipher[nrow][ncol]) {  // 搜索
      vis[nrow][ncol] = true;
      path.push_back({nrow, ncol});
      dfs(cipher, nrow, ncol, vis, text, id+1, path);

      path.pop_back();
      vis[nrow][ncol] = false;
    }
  }

}

int main() {
  // 明文
  int textLen;
  cin >> textLen;
  vector<int> text(textLen);
  for (int i = 0; i < textLen; i++) {
    cin >> text[i];
  }

  // 密文
  int cipherLen;
  cin >> cipherLen;
  vector<vector<int>> cipher(cipherLen, vector<int>(cipherLen));
  for (int i = 0; i < cipherLen; i++) {
    for (int j = 0; j < cipherLen; j++) {
      cin >> cipher[i][j];
    }
  }
  for (int i = 0; i < cipher.size(); i++) {
    for (int j = 0; j < cipher[0].size(); j++) {
      if (cipher[i][j] == text[0]) {
        vector<pair<int, int>> path;
        vector<vector<bool>> vis(cipher.size(), vector<bool>(cipher[0].size()));  // 访问标记
        // dfs 查找明文串
        path.push_back({i,j});
        vis[i][j] = true;
        dfs(cipher, i, j, vis, text, 1, path); // 下一次从1开始匹配
      }
    }
  }

  if (res.empty()) {
    cout << "error" << endl;
    return 0;
  }

  sort(res.begin(), res.end(), [](string a, string b){
    return a < b;
  });

  for(int i = 0; i < res[0].size(); i++) {
    cout << res[0][i];
    if (i!= res[0].size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}