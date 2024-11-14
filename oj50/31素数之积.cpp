/*
 * RSA 加密算法在网络安全世界无处不在，它利用了极大整数分解的困难度，数据越大，安全系数越高。
 * 给定一个32位正整数，请对其进行因数分解，找出是哪两个素数的乘积。
 *
 * 输出：
 * 如果成功找到，以单个空格分隔，从小到大输出两个素数；分解失败，请输出-1,-1
 *
输入
15

输出
3 5

说明：
因数分解后，找到两个素数3和5，使得3*5=15，按从小到大排列后，输出3 5


 * */

#include "iostream"
using namespace std;

// 除了1和此数本身以外，不能被其他任何自然数整除的数
// 直到sqrt(num)。这是因为一个合数n的最小因数不会超过sqrt(n)。  一个合数， a， 找两个因子， 一个是 i， 另一个是 a / i
bool isPrim(int a) {
  if (a < 2) {
    return false;
  }

// i < sqrt(n)
  for (int i = 2; i < a; i++) {  // (1,n) 开区间内有能整数 a 的，则a不是素数
    if (a % i == 0) {
      return false;  // 不是素数
    }
  }

  return true; // 是素数
}

int main() {
  int num;
  cin >> num;

  int prim1 = -1;
  int prim2 = -1;
  // a < b; a < num / a;  a * a < num
  for (int a = 2; a < num; a++) { // 找一个合数的因子，一个是 a， 另一个是 num /a;  两个素数可以相等
    if (num % a == 0) { // 能保证 a * b = num
      int b = num / a;
      if (isPrim(a) && isPrim(b)) {
        prim1 = a;
        prim2 = b;
        break;
      }
    }
  }

  cout << prim1 << " " << prim2 << endl;

  return 0;
}