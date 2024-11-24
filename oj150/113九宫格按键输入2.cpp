#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

string nineKeyInput(const string& inputStr) {
  // 初始模式为数字模式
  string mode = "number";

  // 存储结果的字符串
  string result;

  // 九宫格按键对应的字母和数字关系
  unordered_map<char, string> keyMap = {
          {'1', "1"}, {'2', "abc"}, {'3', "def"},
          {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"},
          {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
          {'0', "0"}
  };

  // 当前正在处理的按键
  char currentKey = '\0';
  // 当前按键被按了多少次
  int currentCount = 0;

  // 遍历输入字符串中的每个字符
  for (char charInput : inputStr) {
    if (charInput == '#') {  // 如果遇到模式切换符号
      if (mode == "number") {  // 从数字模式切换到字母模式
        mode = "alpha";
      } else {  // 从字母模式切换到数字模式
        mode = "number";
      }
      // 重置当前按键和计数
      currentKey = '\0';
      currentCount = 0;
    } else if (charInput == '/') {  // 如果遇到延迟符号
      if (currentKey != '\0') {  // 如果有正在处理的按键
        // 根据按键被按的次数确定要输出的字母
        result += keyMap[currentKey][(currentCount - 1) % keyMap[currentKey].size()];
      }
      // 重置当前按键和计数
      currentKey = '\0';
      currentCount = 0;
    } else if (mode == "number") {  // 数字模式下，直接输出字符
      result += charInput;
    } else {  // 字母模式下
      if (charInput == currentKey) {  // 如果按的是相同的按键
        currentCount++;  // 按键次数加一
      } else {  // 如果按的是不同的按键
        if (currentKey != '\0') {  // 如果有正在处理的按键
          // 根据按键被按的次数确定要输出的字母
          result += keyMap[currentKey][(currentCount - 1) % keyMap[currentKey].size()];
        }
        // 更新当前按键和计数
        currentKey = charInput;
        currentCount = 1;
      }
    }
  }

  // 处理最后一个按键的输出
  if (currentKey != '\0') {
    result += keyMap[currentKey][(currentCount - 1) % keyMap[currentKey].size()];
  }

  // 返回结果字符串
  return result;
}

int main() {
  string inputStr;
  // 获取输入字符串
  cin >> inputStr;
  // 输出九宫格按键处理后的结果
  cout << nineKeyInput(inputStr) << endl;
  return 0;
}
