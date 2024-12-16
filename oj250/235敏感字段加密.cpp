/*
 *
题目描述
给定一个或多个命令组成的命令字符串
1 字符串长度小于等于127字节，只包含大小写字母，数字，下划线和偶数个双引号；
2 命令字之间以一个或多个下划线进行分隔；
3 可以通过两个双引号来标识包含下划线的命令字或空命令字（仅包含两个双引号的命令字），双引号不会在命令字内部出现；
请对指定索引的敏感字段加密，替换为 *****(6个*), 并删除命令字前后多余的下划线
如果无法找到指定索引的命令字，输出字符串ERROR
输入
输入为两行，第一行为命令字索引K（从0开始），第二行为命令字符串S
输出
输出处理后的命令字符串，如果无法找到指定索引的命令字，输出字符串ERROR

 样例1
输入
1
password__a12345678_timeout_100
输出
password_******_timeout_100


输入
1
password__a12345678___timeout_100
输出
password_******_timeout_100


样例2
 输入
2
aaa_ password__"a12_45678"_timeout_100_""_
输出
aaa_ password_******_timeout_100_""

输入
2
aaa_ password__"a12_45678"____timeout_100_""_

 *
 *
 * 思路
 * 1 遍历
 * 2 如果是 '-', 则判断当前 cmd ， 如果没有 " , 则可以； 如果有， 则加上当前 char
 * 3 如果是  "  , 则判断当前 cmd， 如果有 ",  则可以； 如果没有， 加上当前 char
 * 4 cmd  加上当前 char
 * */

#include "string"
#include "iostream"
using namespace std;
int main() {
  int index;
  cin >> index;
  cin.ignore();

  string str;
  getline(cin, str);

  string cmd;
  int cmdStartPos = -1;
  int cmdId = -1;
  int id = 0;
  bool find = false;
  while (id < str.size()) {
    if (str[id] == '_') { // 如果遇到了 '_'
      // 去重
      int cmdLeftPos = id+1;  // 也需要去除多余的下划线
      while (id < str.size() && str[id] == '_') {
        id++;
      }
      // 找下一个 '-' , 过程中如果遇到 " , 则停止
      while (id < str.size() && str[id] != '_') {
        if (str[id] == '"') {
          break;
        }
        id++;
      }

      if (id >= str.size()) {
        break;
      }

      if (str[id] == '"') { // 没有找到下一个 '_', 但找到了 " , 则认为一个命令从 " 开始
        continue;
      }

      // 处理一个命令
      if (str[id] == '_') {
        cmdId++;
        if (cmdId == index) {
          // 找到了这个指定的这个index cmd
          cmd = str.substr(cmdLeftPos, id - cmdLeftPos);  // 包括cmdLeftPos， 不包括 id
          cmdStartPos = cmdLeftPos;
          find = true;
          break;
        }
      }

    } else if (str[id] == '"') {
      // 找下一个 "
      // 去重 _
      int cmdLeftPos = id;
      id = id + 1;
      while (id < str.size() && str[id] != '"') {
        id++;
      }
      if (id >= str.size()) {
        break;
      }
      // 找到了 "
      if (str[id] == '"') {
        cmdId++;
        if (cmdId == index) {
          // 找到了这个指定的这个index cmd
          cmd = str.substr(cmdLeftPos, id - cmdLeftPos + 1); // 包括 cmdLeftPos 和 id
          cmdStartPos = cmdLeftPos;
          find = true;
          break;
        }
      }
    } else {
      // 不是 _, "
      while (id < str.size() && str[id] != '_' && str[id] != '"') {
        id++;
      }
      int cmdLeftPos = 0;
      if (str[id] == '_') {
        cmdId++;
        if (cmdId == index) {
          // 找到了这个指定的这个index cmd
          cmd = str.substr(cmdLeftPos, id - cmdLeftPos + 1); // 包括 cmdLeftPos 和 id
          cmdStartPos = cmdLeftPos;
          find = true;
          break;
        }
      }
    }
  }

  if(find) {
    string ret;
    int rightPos = cmdStartPos + cmd.size();
    while (cmdStartPos - 2 >= 0 && str[cmdStartPos-1] == '_' && str[cmdStartPos-2] == '_') {
      cmdStartPos--;
    }
    while (rightPos+1 < str.size() && str[rightPos] == '_' && str[rightPos+1] == '_') {
      rightPos++;
    }
    ret = str.substr(0, cmdStartPos);  // 前面不包括 cmdStartPos
    ret += "*****";
    ret += str.substr(rightPos);
    cout << ret << endl;
  } else {
    cout << "ERROR" << endl;
  }

//  string str = "123\"123";
//  cout << (str[3] == '"') << endl;
//  cout << (str[3] == '\"') << endl;

  return 0;
}