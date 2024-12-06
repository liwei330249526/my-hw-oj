/*
 *
vlan 是一种对局域网设备进行逻辑划分的计数，为了标识不同的V领n，引入了 vlan id （1-4094 之间的整数）的概念
定义一个vlan id 的资源池（下称 vlan 资源池），资源池中连续的vlan 用开始vlan-结束vlan表示，不连续的用单个整数表示，
所有的vlan 用英文逗号连接起来
现在有个vlan资源池，业务需要从资源池中申请一个vlan，需要你输出从vlan资源池中移除申请的vlan后的资源池

输入
第一行为字符串格式的vlan资源池，第二行为业务要申请的vlan，vlan的取值范围为[1,4094]之间的整数

输出
从输入vlan资源池中移除申请的vlan后字符串格式的vlan资源池，输出要求满足题目描述的个数，并且按照vlan从小到大的升序输出
如果申请的vlan不在原资源池内，输出原vlan资源池升序排列后的字符串即可

 *
 * 样例1
 * 输入
1-5
2

输出
1,3-5

说明：
原VLAN资源池中有VLAN1、2、3、 4、 5, 从资源池中移除2后,剩下VLAN 1、3、 4、 5, 按照题目描述格式并升序后的结果为1,3-5

 *
 * 样例2
 * 输入
20-21,15,18,30,5-10
15

输出
5-10,18,20-21,30

说明：
原VLAN资源池中有VLAN 5、6、 7、8、9、 10、15、18、 20、21、 30,从资源池中移除15后，资源池中剩下的VLAN为5、6、7、8、9、10、18、 20、 21、 30, 按照题目描述格式并升序后的结果为5-10,18,20-21,30

 *
 * 样例3
 * 输入
5,1-3
10

输出
1-3,5
原VLAN资源池中有VLAN 1、2、3, 5,申请的VLAN 10不在原资源池中,将原资源池按照题目描述格式并按升序排序后输出的结果为1-3,5

 *
 *
 * 思路1
 * 获取区间， 将区间值加你加入vector<int> 数组
 * 申请资源
 * 返回区间
 *
 * */
#include "string"
#include "iostream"
#include "sstream"
#include "vector"
#include "algorithm"
using namespace std;
/*
 *
 * 20-21,15,18,30,5-10
   15
 * */
int main() {
  string str;
  cin >> str;
  int req;
  cin >> req;

  // 获得资源集合
  stringstream stm(str);
  vector<int> resource;
  string token;
  while (getline(stm, token, ',')) {
    int idl = token.find('-');
    if (idl != string::npos) { // 区间
      int start = stoi(token.substr(0, idl));
      int end = stoi(token.substr(idl+1));
      for (int i = start; i <= end; i++) {
        resource.push_back(i);
      }
    } else { // 单点
      int pt = stoi(token);
      resource.push_back(pt);
    }
  }

  // 资源集合排序
  sort(resource.begin(), resource.end());

  // 申请资源
  auto it = find(resource.begin(), resource.end(), req);
  if (it != resource.end()) {
    resource.erase(it);
  }

  // 打印
  ostringstream oss;
  int i = 0;
  while (i < resource.size()) {
    int left = resource[i];
    while (i+1 < resource.size() && resource[i] + 1 == resource[i+1]) { // 递增寻找, 从i开始遍历，如果 i+1 满足， 则i = i+1;
      i = i+1;
    }
    // 此时i是 右边界，是满足 (i+1 < resource.size() && resource[i+1] + 1 == resource[i]) 的； i+1 就不满足了
    int right = resource[i];
    if (right != left) {
      oss << left << "-" << right;
    } else {
      oss << left;
    }

    if (i != resource.size()-1) { // i 应该到最后一个元素 resource.size-1
      oss << ",";
    }
    i++;     // 此时i已经处理过了，所以要递增一次
  }

  string ret = oss.str();
  cout << ret << endl;

  return 0;
}