/*
 *

有一个简易内存池，内存按照大小力度分类，每个力度有若干个可用内存资源，用户会进行一系列内存申请，需要按需分配内存池种的资源，返回申请结果成功失败列表
分配规则如下：
1 分配的呢刺激你要大于等于内存的申请量，存在满足需求的内存就必须分配，优先分配力度小的，单内存不能拆分使用；
2 需要按申请肾虚分配，先申请的线分配，有可用内存分配则申请结果为true；
3 没有可用则返回false

输入
输入为两行字符串，第一行为内存池资源列表，包含内存粒度数据信息，粒度数据间用逗号分隔
一个粒度信息内用冒号分隔，冒号前位内存粒度大小，冒号后为数量，
第二行为申请列表，申请的内存大小用逗号分隔
输出
输出四内存池分配结果

样例1
输入
64:2,128:1,32:4,1:128
50,36,64,128,127

输出
True,True,True,False,False

说明：
内存池资源包含: 64K共2个. 128K共1个、 32K共4个、 1K共128个的内存资源;
针对50,36, 64,128, 127的内存申请序列，分配的内存依次是: 64,64, 128,NULL,NULL,
第三次申请内存时已经将128分配出去，因此输出结果是:True,True,True,False,False


样例2

 *
 * */

#include "vector"
#include "sstream"
#include "string"
#include "iostream"
#include "algorithm"
using namespace std;

struct Mcompare {
    bool operator()(pair<int, int> &p1, pair<int, int> &p2) {
      return p1.first < p2.first;
    }
};

int binSearch(vector<pair<int, int>> &source, int target) {
  int left = 0;
  int right = source.size()-1;
  int res = -1;
  while (left <= right) {
    int mid = (left+right)/2;
    if (source[mid].first < target) {
      left = mid+1;
      res = left;
    } else if (target < source[mid].first) {
      right = mid-1;
    } else {
      return mid;
    }
  }

  return res;
}

int main() {
  string sourceStr;
  string reqStr;
  cin >> sourceStr;
  cin >> reqStr;

  string token;
  vector<pair<int, int>> source;
  stringstream stm(sourceStr);
  while (getline(stm, token, ',')) {
    int id = token.find(':');
    string rs = token.substr(0, id);
    string ct = token.substr(id+1);
    source.push_back({stoi(rs), stoi(ct)});
  }

  vector<int> reqs;
  stm.clear();
  stm.str(reqStr);
  while (getline(stm, token, ',')) {
    reqs.push_back(stoi(token));
  }

  sort(source.begin(), source.end(), Mcompare());
  vector<string> res(reqs.size());

  for (int i = 0; i < reqs.size(); i++) {
    bool reqOk = false;
//    for (int j = 0; j < source.size(); j++) {
//      if(reqs[i] < source[j].first && source[j].second > 0) {
//        source[j].second--;
//        reqOk = true;
//        break;
//      }
//    }
    // 改为二分查找
    int id = binSearch(source, reqs[i]);
    if (id != -1 && source[id].second > 0) {
      reqOk = true;
      source[id].second--;
      if (source[id].second == 0) {
        source.erase(source.begin() + id);
      }
    }

    if (reqOk) {
      res[i] = "True";
    } else {
      res[i] = "False";
    }
  }

  for (int i = 0; i < res.size(); i++) {
    cout << res[i];
    if (i != res.size()-1) {
      cout << ",";
    }
  }
  cout << endl;

  return 0;
}