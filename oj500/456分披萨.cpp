/*
 *
题目描述
“吃货” 和 “馋嘴” 两人到披萨店点了一份铁盘披萨，并让店员将披萨按放射状切成大小相同的偶数扇形小块；但是粗心的服务员将披萨切成了每块代傲都完全不同的奇数块，
且肉眼能分片出大小。

由于两人都想吃最多的披萨，他们商量一个他们认为公平的分发，从"吃货"开始，轮流取披萨，除了第一块可以任意选取以外，其他的都必须从缺口开始选。

他俩选披萨的思路不同。 “馋嘴”每次都会选最大的披萨， 而且吃货知道 “馋嘴” 的想法

已知披萨小块的数量uiji每块的大小，求 “吃货” 能分得的最大披萨大小的总和。

输入
第1行为一个正整数奇数N，表示披萨的小块的数量。
接下来第2行到第N+1行，每行为一个正整数，表示第i块披萨的大小，
输出
“吃货能”分得的最大的披萨的大小总和。

样例1
输入
5
8
2
10
5
7


输出
19

说明:
此例子中，有5块披萨。每块大小依次为8、2、10、5、7。按照如下顺序拿披萨，可以使 "吃货" 拿到最多披萨：

1、吃货 拿大小为10的披萨
2、馋嘴 拿大小为5的披萨
3、吃货 拿大小为7的披萨
4、馋嘴 拿大小为8的披萨
5、吃货 拿大小为2的披萨
至此，披萨瓜分完毕，"吃货"拿到的披萨总大小为10+7+2=19
可能存在多种拿法，以上只是其中一种。


样例I
输入
5
8
2
10
7
5

输出
17


样例3
输入
7
1
2
3
4
5
6
7

输出
16



 *
 * */


/*
 *
 *
思路：
1 吃货 开始选哪个呢？ 这个要遍历每个位置，求每个结果。
2 馋嘴选的时候， 只能从缺口选，缺口处有2块，选哪个呢？ 馋嘴很聪明，每次选较大的一个。
3 轮到吃货选了， 缺口处有2块，选哪个呢？ 这个要 遍历2个位置。
4 怎么优化呢， dp[i][j] 是一个状态， 表示 start 是哪块， end 是哪块？  这个状态下的披萨，吃货能获得最大披萨是多少

 *
 *
  */

#include "iostream"
#include "string"
#include "vector"
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  vector<vector<int>> dp(n, vector<int>(n));  // dp[i][j] 这个状态， 吃货获得的最大量
  auto dfs = [&](auto &&dfs, int start, int end) -> int {
    // 让馋嘴选
    if(arr[start] > arr[end]) {
      start = (start + 1) % n;
    } else {
      end = (end -1 + n) % n;
    }

    // 轮到吃货选了，判断dp 状态是否已经计算了
    if(dp[start][end] != 0) {
      return dp[start][end];
    }

    // 递归计算
    // 吃start

    // 截止， 如果到了最后一块,直接赋值
    if (start == end) {
      dp[start][end] = arr[start];
      return dp[start][end];
    }


    int nstart = (start+1) % n; // 新的start
    int left = arr[start] + dfs(dfs, nstart, end);

    int nend = (end-1 + n) % n; // 新的end
    int right = arr[end] + dfs(dfs, start, nend);

    dp[start][end] = max(left, right);
    return dp[start][end];
  };


  // 1 吃货 开始选哪个呢？ 这个要遍历每个位置，求每个结果。
  int ret = 0;

  for(int i = 0; i < n; i++) {
    // 选择 i位置
    int nextStart = (i+1) % n;
    int nextEnd = (i-1 + n) % n;
    int curRet = arr[i] + dfs(dfs, nextStart, nextEnd);
    ret = max(ret, curRet);
  }

  cout << ret << endl;

  return 0;
}