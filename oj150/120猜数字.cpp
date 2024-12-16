/*
 *
题目描述
一个人设定一组四码的数字作为谜底，另一方猜。每猜一个数，出数者就要根据这个数字给出提示，提示以XAYB形式呈现，直到猜中位置。
其中X表示位正确的数的个数（数字正确且位置正确），而Y表示数字正确而位置不对的数的个数。
例如，当谜底为8123，而猜迷者猜1052时，出题者必须提示0A2B。
     当谜底为5637，而猜谜者猜4931时，出题者必须提示1A0B。
当前已知N组猜谜者猜的数字与提示，如果答案确定，请输出答案，不确定则输出N/A

输入
第一行输入一个正整数N。
接下来N行，每行包含一个猜测的数字与提示结果。
 *
 *样例1
输入
6
4815 1A1B
5716 0A1B
7842 0A1B
4901 0A0B
8585 3A0B
8555 2A1B


输出
3585

 *
 * */

#include "string"
#include "iostream"
#include "vector"
#include "unordered_map"
using namespace std;


bool isMatchAllGuess(vector<int> &answer, vector<pair<int, pair<int, int>>> &guess) {
  vector<int> numArr(4);

  int num;
  int a;
  int b;
  int match1;
  int match2;

  // answer 是否满足所有的猜测
  for (auto &g : guess) {
    num = g.first;
    a = g.second.first;
    b = g.second.second;
    match1 = 0;
    match2 = 0;
    unordered_map<int, int> dict_answer;
    unordered_map<int, int> dict_num;

    for (int j = 3; j >= 0; j--) {
      numArr[j] = num % 10;
      num /= 10;
    }

    // 匹配1
    for (int i = 0; i < 4; i++) {
      if (answer[i] == numArr[i]) { // 如果位置一样，值一样
        match1++;
      } else {                     // 如果位置一样，值不同
        dict_answer[answer[i]]++;
        dict_num[numArr[i]]++;
      }
    }

    // 匹配2
    for(auto &it : dict_answer) {
      match2 += min(it.second, dict_num[it.first]);
    }

    if(a != match1 || b != match2) {
      return false;
    }
  }
  return true;
}

// 遍历所可能
int main() {
  int n;
  cin >> n;
  vector<pair<int, pair<int, int>>> guess; // 猜的数字， a，b分别是 正确的数的个数， 数字正确而位置不对的数的个数
  int guessNum;
  string guessInfo;
  int a;
  int b;
  for (int i = 0; i < n; i++) {
    cin >> guessNum >> guessInfo;
    sscanf(guessInfo.c_str(), "%dA%dB", &a, &b);
    guess.push_back({guessNum, {a, b}});
  }

  // 遍历每个可能
  vector<int> resNum;
  for (int i = 0; i < 10000; i++) {
    vector<int> anser(4);  // 一个可能的答案
    int num1 = i;
    for (int j = 3; j >= 0; j--) {
      anser[j] =num1 % 10;
      num1 /= 10;
    }

    // 尝试匹配所有 guess
    if (isMatchAllGuess(anser, guess)) {
      resNum.push_back(i);
    }
  }
  vector<int> res(4);
  if (resNum.size() == 1) {
    int num = resNum[0];
    for (int j = 3; j >= 0; j--) {
      res[j] =num % 10;
      num /= 10;
    }
  } else {
    cout << "NA" << endl;
  }

  for (auto &num : res) {
    cout << num;
  }
  cout << endl;

  return 0;
}

