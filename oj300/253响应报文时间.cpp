/*
 *
IGMP 协议中， 有一个字段称作最大响应时间（Max Response Time）,Host 收到查询报文，解析出MaxResponse Time字段后，需要在（0- MaxResponse Time）
时间内选取随机事件回应一个响应报文，如果在随机事件内收到一个新的查询报文，则会根据两者时间大小，选取小的乙方刷新回应时间。
最大响应时间有如下计算方式
当 MaxRespCode<128, MaxRespTime=MaxRespCode;
当 MaxRespCode=128， MaxRespTime = (mant | 0x10) << (exp + 3)
0|123|4567
|1|exp|mant|
注： exp 最大响应时间的高 5-7 位， mant 为最大响应时间的低4位
中接收到的MaxRespCode最大值为255， 以上出现的所有字段均为无符号数
现在我们认为HOST接收到查询报文时，选取的随机事件必定为最大值，现给出HOST收到查询报文的个数C， HOST收到报文的时间T，以及查询报文的最大响应时间字段M,
请计算出HOST发送响应报文的时间

输入
第一行： 查询报文个数C，后续每行分别为HOST收到报文时间T，以及最大响应字段M，以空格分隔
输出
HOST发送响应报文的时间

样例1
输入
3
0 20
1 10
8 20



输出
11

说明：
收到3个报文
第0秒收到1个报文响应时间为20秒，则要到0+20=20秒响应

第1秒收到第2个报文，响应时间为10，则要到1+10=11秒响应， 与上面的报文的响应时间比较获得响应时间最小为11秒

第8秒收到第3个报文，响应时间为20秒，则要到8+20=28秒响应，与上面的报文的响应时间比较获得响应时间最小为11秒

最终得到最小响应报文时间为11秒


样例2
输入
2
0 255
200 60



输出
260

说明：
第0秒收到第1个报文,响应时间为255秒，则要到(15 | 0x10)<<(7+3)=31744秒响应:(mant=15,exp=7)

第200秒收到第2个报文,响应时间为60,则要到200+60=260秒响应，与上面的报文的响应时间比较获得响应时间最小为260秒最终得到最小响应报文时间为260秒


备注：
用例确定只会发送一个响应报文, 不存在计时结束后依然收到查询报文的情况


样例3
输入
1
5 100

输出
105

 *
 * */

#include "iostream"
#include "string"
#include "vector"
#include "stdint.h"
using namespace std;

int getMaxTime(int maxCode) {
  if (maxCode < 128) {
    return maxCode;
  }

  int mant = maxCode & 0xf;
  int exp = (maxCode >> 4) & 0x7;

  return (mant | 0x10) << (exp+3);
}

int main() {
  int n;
  cin >> n;
  vector<vector<int>> pk(n, vector<int>(2));

  for (int i = 0; i < n; i++) {
    cin >> pk[i][0] >> pk[i][1];
  }
  int ret = INT32_MAX;
  for (int i = 0; i < n; i++) {
    int curTime = pk[i][0];
    int maxCode = pk[i][1];
    int maxTime = getMaxTime(maxCode);

    ret = min(ret, curTime + maxTime);
  }
  cout << ret << endl;

  return 0;
}