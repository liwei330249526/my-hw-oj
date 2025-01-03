/*
 *
题目描述
给定一个输入字符串，字符串只可能由英文字母(a-z A-Z) 和左右小括号 ( ) 组成
当字符串存在小括号时，小括号时成对的，可以有一个或多个小括号，小括号不会嵌套，小括号对内可以包含1个或多个英文字母，也可以不包含英文字母。
当小括号对内包含多个英文字母时，这些字母之间是相互等效的关系，而且等效关系可以在不同的小括号对之间传递，即当存在 a和b等效和存在b和c等效时，
a和c也等效，另外，同一个英文字母的大写字母和小写字母也相互等效（及时他们分布在不同额括号对里）
要对这个输入字符串左简化，输出一个新的字符串，输出字符串里只需保留输入字符串里没有被小括号对包含的字符（按照输入字符串里的字符顺序），
并将每个字符替换为在小括号对里包含的字典序最小的等效字符。

如果简化后字符串为空，请输出0

实例： 输入字符串为 "never(dont)live(run)up(f)()" , 初始等效字符集合为(d,0,n,t)，（r,u,n） 由于等效关系可以传递，因此最终等效字符集合为
(d,o,n,t,r,u),将输入字符串里的剩余部分按字典序最小的等效字符替换后得到 devedgivedp

样例1
输入
()abd

输出
abd


说明：输入字符串里没有被小括号包含的了字符串为"abd"，其中每个字符没有等效字符，输出为"abd"


样例2
输入
(abd)demand(fb)()for


输出
aemanaaor


说明: 等效字符集为(a，b，d，f)，输入字符串里没有被小括号包含的了字符串集合为'demandfor”，将其中字符替换为字典序最小的等效字符后输出为:aemanaaor

样例3
输入
()happy(xyz)new(wxy)year(t)

输出
happwnewwear


说明：等效字符集为(x，y, z，w)，输入字符串里没有被小括号包含的了字符串集合为"happynewyear”，将其中字符替换为字典序最小的等效字等后输出为:happwnewwear


(abd)demand(fb)()for
 *
 * */

#include "iostream"
#include "unordered_map"
#include "algorithm"
#include "vector"
using namespace std;

int test1() {
  string str;
  getline(cin, str);
  string strIn;
  string strOut;

  bool hasLeft = false;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '(') {
      hasLeft = true;
    } else if (str[i] == ')') {
      hasLeft = false;
    } else {
      if (hasLeft) {
        strIn += str[i];
      } else {
        strOut += str[i];
      }
    }
  }

  if (strIn.size() == 0) {
    cout << strOut << endl;
    return 0;
  }

  char root;
  unordered_map<char, int> inDict;
  sort(strIn.begin(), strIn.end());
  root = strIn[0];
  for (int i = 0; i < strIn.size(); i++) {
    inDict[strIn[i]]++;
  }

  string ret;
  for (int i = 0; i < strOut.size(); i++) {
    if (inDict.find(strOut[i]) != inDict.end()) { // 存在
      ret += root;
    } else { // 不存在
      ret += strOut[i];
    }
  }
  cout << ret << endl;
  return 0;
}


// 并查集
class UnionFind {
public:
  UnionFind(int x) {
    parents.resize(x);
    ranks.resize(x);
    for (int i = 0; i < parents.size(); i++) {
      parents[i] = i;
    }
    return;
  }

  int find(int a) {
    // 截止
    if (parents[a] == a) {
      return a;
    }

    int root = find(parents[a]);
    parents[a] = root;
    return root;
  }

  int merge(int a, int b) {
    int roota = find(a);
    int rootb = find(b);

    if (roota != rootb) {
//      if (ranks[roota] > ranks[rootb]) { // a root          比较平衡的策略，rank
//        parents[rootb] = roota;
//      } else if (ranks[roota] < ranks[rootb]) { // b root
//        parents[roota] = rootb;
//      } else { // a root
//        ranks[roota]++;
//        parents[rootb] = roota;
//      }

        // 这里可以按顺序合并
        if (roota < rootb) { // 较小的是root
          parents[rootb] = roota;
        } else {
          parents[roota] = rootb;
        }
    }
    return 1;
  }

private:
    vector<int> parents;
    vector<int> ranks;
};

int test2() {
  string str;
  getline(cin, str);
  string strIn;
  string strOut;
  unordered_map<char, int> vs; // 加入并查集的

  UnionFind uf(150);
  bool hasLeft = false;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '(') {
      hasLeft = true;
    } else if (str[i] == ')') {
      hasLeft = false;
      // 并查集合并 strIn
      if (strIn.size() != 0) {
        char c0 = strIn[0];
        for (int i = 0; i < strIn.size(); i++) {
          // 加入并查集
          uf.merge(c0, strIn[i]);
          vs[strIn[i]] = 1;

          // 如果是小写，则看大写如果已经加入， 则大小写合并
          // 如果是大写，则看小写如果已经就爱如，则大小写合并
          if (islower(strIn[i]) && vs[toupper(strIn[i])] == 1) {
            uf.merge(strIn[i], toupper(strIn[i]));
          } else if (isupper(strIn[i]) && vs[tolower(strIn[i])]) {
            uf.merge(strIn[i], tolower(strIn[i]));
          }
        }
        strIn = "";
      }
    } else {
      if (hasLeft) {
        strIn += str[i];
      } else {
        strOut += str[i];
      }
    }
  }
  string ret;
  for (int i = 0; i < strOut.size(); i++) {
    if (vs[strOut[i]] == 1) { // 在并查集内
      ret += uf.find(strOut[i]);
    } else { // 不在并查集内
      ret += strOut[i];
    }
  }
  cout << ret << endl;

  return 0;
}

int main() {
  test2();
  return 0;
}