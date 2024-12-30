/*
 *
题目描述
一个xx 产品行销总公司，只有一个boss，其有若干一级分销，一级分销又有若干二级分销，每个分销只有唯一的上级分销；规定
每个月，下级分销要将自己总收入(自己的+下级上交的)每满100元上交15元给自己的上级；现给出一组分销关系，和每个分销的收入，
请找出boss 并计算这个boss的收入，比如：
1 收入100元，上交15元
2 收入199元， 上交15元
3 收入200 元，上交30元。

输入
第一行输入N，表示有N个数据
接下来输入N行，每行3个数
分销id， 上级分销id，收入
输出
输出一行，两个以空格分隔的整数，含义如下：
boss 的ID boss 的收入

样例1
输入
5
1 0 100
2 0 199
3 0 200
4 0 200
5 0 200

输出
0 120


样例2
输入
3
1 0 223
2 0 323
3 2 1203

输出
0 105


递归
 *
 * */

#include "iostream"
#include "vector"
#include "unordered_map"
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<vector<int>> allSales(n, vector<int>(3)); // 所有销售额
  for (int i = 0; i < n; i++) {
    cin >> allSales[i][0] >> allSales[i][1] >> allSales[i][2];
  }


  unordered_map<int, vector<int>> agentParentDict; // 每个agent 和其子agents 关系
  unordered_map<int, vector<int>> agentSales; // agent 的销售额
  vector<int> allAgentIds; // 所有人
  for (int i = 0; i < n; i++) {
    agentParentDict[allSales[i][1]].push_back(allSales[i][0]);  // allSales[i][1] 上增加子
    agentSales[allSales[i][0]] = allSales[i]; // id 和销售额的映射, 及其父亲的映射
    allAgentIds.push_back(allSales[i][0]);
    allAgentIds.push_back(allSales[i][1]);
  }

  // 找顶层代理, 遍历每个人， 如果该人，没有父节点信息， 则是rootId
  int rootId = -1;
  for (int i = 0; i < allAgentIds.size(); i++) {
    if (agentSales.find(allAgentIds[i]) == agentSales.end()) {
      rootId = allAgentIds[i];
      break;
    }
  }


  int ret = 0;
  auto dfs = [&](auto &&dfs, int id) ->int {  // 遍历每个节点
    int ret = 0;
    if (agentSales.find(id) != agentSales.end()) {
      ret += agentSales[id][2];  // 自己本身
    }
    for (int childId : agentParentDict[id]) {
      ret += dfs(dfs, childId)/100 * 15; // 加上子节点的和 / 15
    }
    return ret;
  };

  int ans = dfs(dfs, rootId);
  cout << rootId << " " ans << endl;

  return 0;
}