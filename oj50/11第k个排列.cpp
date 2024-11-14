/*
 * 给定参数n，从1到n有n个整数：1，2，3，4，... n ； 共有n!种排列
 * 按大小顺序升序列出所有排列情况，并意义标记
 * 当n=3 时，所有排列如下：
 * 123  132  213  231  312  321
 *
 * 给出n和k，返回第k个排列
 *
输入
3
3


输出
213

说明：
3的排列有123,132,213…,那么第三位置就是213

 *
 * */

// 回溯找排列

#include "iostream"
#include "vector"
using namespace std;

void dfs(vector<bool> &fg, int n, string path, string &res, int &count) {
  if (path.size() == n) {
    count--;
    if (count == 0) {
      res = path;
    }
    return ;
  }

  for (int i = 0; i < fg.size(); i++) {
    if (!fg[i]) {
      fg[i] = true;
      dfs(fg, n, path+ to_string(i+1), res, count);
      fg[i] = false;

      if (count == 0) {
        return;
      }
    }
  }
}

int main() {
  int n;
  int id;
  cin >> n >> id;
//  cin >> id;

  vector<bool> fg(n);
  string res;
  int count = id;
  dfs(fg, n, "", res, count);
  if (!res.empty()) {
    cout << res << endl;
  }
  return 0;
}