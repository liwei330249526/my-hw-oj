/*
 *
题目描述
智能手机方便了我们的生活，也侵占了我们的时间。 “手机App防沉迷系统” 能range我们每天合理的规划手机 App使用时间。
在正确的时间左正确的事。
1 在一天24小时内，可注册的每个App 的允许使用时间段。
2 一个时间段只能使用一个App， 距离说明： 不能在 09::00 - 10::00 同时注册 App2，和App3.
3 App 有优先级，数值越高，优先级越高。注册使用时段时。如果高优先级的App时间和低优先级的时间段有冲突，则系统会自动注销低优先级时间段，如果App
优先级相同，则后添加的App 不能注册。

输入
第1行表示注册App数 N
接下来是N行，每行表示App 注册数据，
最后一行输入一个时间段，程序即返回该时间点可用App
输出
输出一个字符串，表示App 的名称， 没有返回NA

样例1
输入
2
App1 1 09:00 10:00
App2 2 11:00 11:30
09:30

输出
App1


样例2
输入
2
App1 1 09:00 10:00
App3 2 09:00 10:00
09:30


输出
App3


样例3
输入
2
App1 1 09:00 10:00
App2 2 09:10 09:30
09:20



输出
App2

说明
App1和App2的时段有冲突，App2优先级高，注册App2之后，App1自动注销，因此输出App2


样例4
输入
2
App1 1 09:00 10:00
App2 2 09:10 09:30
09:50

输出
NA

说明：
App2优先级高会被注册, 然后App1被注销, App1被注销后, 09:50时刻没有应用注册，因此输出NA

 *
 * */

/*
 *
 * 1 时间可以直接比较
 * 2
 *
 * */

#include "iostream"
#include "sstream"
#include "vector"
using namespace std;

class Mapp {
public:
    Mapp(string name, int rank, string startTime, string endTime){
      this->name = name;
      this->rank = rank;
      this->startTime =startTime;
      this->endTime = endTime;
    }

    string name;
    int rank;
    string startTime;
    string endTime;
};

int main() {
  int n;
  cin >> n;
  cin.ignore();
  string str;
  string name;
  int rank;
  string startTime;
  string endTime;
  vector<Mapp> apps;
  for (int i = 0; i < n; i++) { // 外循环 i
    getline(cin, str);
    istringstream ist(str);
    ist >> name >> rank >> startTime >> endTime;
    // 如果和之前的 app 有时间交叉， 则判断本 cur app 的rank 是否是最大的，如果是最大的，删除所有交叉的app，插入本app
    // 如果没有时间交叉， 则直接插入；
    if (startTime >= endTime) {
      continue;
    }
    bool canAdd = true; // 可以添加进去
    vector<int> toRemove;
    for(int j = 0; j < apps.size(); j++) { // 内循环 apps j
      if (endTime <= apps[j].startTime || apps[j].endTime <= startTime) { // 没有交叉; 双重循环， index 又搞错了
        // nothing
      } else { // 有交叉
        if (apps[j].rank < rank) {
           toRemove.push_back(j);
        } else {
          canAdd = false; // rank 优先级不是最高的，则不能add
          break;
        }
      }
    }

    // 先删除靠后的元素，避免前面删除元素后导致后面元素索引变化而出现错误。例如，如果先删除索引为 1 的元素，
    // 那么原来索引为 3 的元素就变成了新的索引 2，按顺序删除就会出错，所以从大到小删除能保证索引的正确性
    if(canAdd) { // 删除重叠的， 插入新的
      for (int k = toRemove.size()-1; k >= 0; k--) {
        apps.erase(apps.begin() + toRemove[k]);
      }
      apps.push_back(Mapp(name, rank, startTime, endTime));
    }
  }

  string queryTime;
  getline(cin, queryTime);

  string resAppName = "NA";
  for (int i = 0; i < apps.size(); i++) { // 查询时间在某个 app 的时间范围内   9:00, 9:01,   query 是9:01 则不能使用
    if (apps[i].startTime <= queryTime && queryTime < apps[i].endTime) {
      resAppName = apps[i].name;
      break;
    }
  }
  cout << resAppName << endl;
  return 0;
}