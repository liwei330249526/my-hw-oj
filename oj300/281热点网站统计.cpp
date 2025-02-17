/*
 *
题目描述
1 企业路由器的统计页面，有一个功能需要动态统计公司的访问最多的网页URL top N， 请设计一个算法，可以高效动态统计Top N 的页面

输入
每一行都是一个URL或一个数字，㒰是URL，代表一段时间内的网页访问；如果是一个数字N，代表本次需要输出逇Top N个 URL

输入约束：
1 总访问网页数量小于 5000 个，单网页范文次数小于 65535次；
2 网页URL仅由字母，数字和点分隔符组成，且长度小于等于127字节；
3 数字是正整数，小于等于10且小于当前总访问网页数；

输出
每行输入要对应一行输出，输出按访问你次数排序的前N个URL，用逗号分隔
输出要求：
1 每次输出要统计之前的所哟恱，不仅是本次输入；
2 如果有访问次数相等的URL， 按URL 的字符串字典序升序排列，输出upaixu靠前的URL。


样例1
输入
news.qq.com
news.sina.com.cn
news.qq.com
news.qq.com
game.163.com
game.163.com
www.huawei.com
www.cctv.com
3
www.huawei.com
www.cctv.com
www.huawei.com
www.cctv.com
www.huawei.com
www.cctv.com
www.huawei. com
www. cctv. com
www. huawei.com
3

输出
news.qq.com ,game.163.com,news.sina.com.cn
www.huawei.com,www.cctv.com, news.qq.com

样例2
输入
news.qq.com
www.cctv.com
1
www.huawei.com
www.huawei.com
2
3

输出
news.qq.com
www.huawei.com, news.qq.com
www.huawei.com, news.qq.com, www.cctv.com

 *
 * */

#include "iostream"
#include "vector"
#include "unordered_map"
#include "queue"
using namespace std;

bool isDigitStr(string str) {
  for (char c : str) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}
// 父节点要最大值， 要字典序最小的
struct WebVisiteCompare {
    bool operator()(pair<string, int> &p1, pair<string, int> &p2) {
      if (p1.second != p2.second) {
        return p1.second < p2.second; // 访问次数从大到校；  子节点  -- 父节点
      }
      return p1.first > p2.first; // string 按字典序，升序排列 ，  子节点 -- 父节点
    }
};

vector<pair<string, int>> getTopN(priority_queue<pair<string, int>, vector<pair<string, int>>, WebVisiteCompare> &pq, int N) {
  vector<pair<string, int>> res;
  priority_queue<pair<string, int>, vector<pair<string, int>>, WebVisiteCompare> pqt;
  // 获取top k
  while (N > 0 && !pq.empty()) {
    res.push_back(pq.top());
    pqt.push(pq.top());
    pq.pop();
    N--;
  }

  // 还原 pq
  while (pqt.empty()) {
    pq.push(pqt.top());
    pqt.pop();
  }
  return res;
}

int main() {
  string str;
  vector<string> strs;
  unordered_map<string, int> dict;

  while (getline(cin, str)) {
    if (isDigitStr(str)) {
      priority_queue<pair<string, int>, vector<pair<string, int>>, WebVisiteCompare> pq;
      int num = stoi(str);
      for(auto &it : dict) {
        pq.push({it.first, it.second});
      }
      vector<pair<string, int>> curStrs = getTopN(pq, num);
      for (int i = 0; i < curStrs.size(); i++) {
        cout << curStrs[i].first;
        if (i != curStrs.size()-1) {
          cout << ",";
        }
      }
      cout << endl;

    } else {
      dict[str]++;
    }
  }
//  cout << stoi("123") << endl;
//  if (isDigitStr("abc")) {
//    cout << stoi("abc") << endl;
//  } else {
//    cout << "not digit" << endl;
//  }

//  news.qq.com
//  www.cctv.com
//  string str1 = "news.qq.com";  // 小
//  string str2 = "www.cctv.com"; // 大
//  bool ret = str1 < str2;
//  cout << ret << endl;  // 1
  int6


  return 0;
}