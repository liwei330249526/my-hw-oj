/*
 *
题目描述
实现一个模拟目录管理功能，输入一个命令序列，输出最后一条命令运行结果。
支持命令：
1 创建目录命令， mdkir 目录名称，如 mkdir abc 为在当前目录创建目录abc 目录，如果已经存在同名目录则不执行任何操作，此命令无输出。
2 进入目录命令， cd 目录名称，如cd abc 为进入abc 目录，特别的， cd ..  ， 为返回上级目录，如果目录不存在则不执行任何操作，此命令无输出。
3 查看当前所在路径命令： pwd， 输出当前路径字符串

约束：
1 目录名称仅支持小写字母： mkdir 和 cd 命令的参数仅支持单个目录，如： mkdir abc 和 cd abc；不支持嵌套路径和绝对路径，如：
  mkdir abc/efg, mkdir /abc/efg, cd /abc/efg , 是不支持的。
2 根目录符号位 / , 根目录作为初始目录
3 任何不符合上述定义的无效命令不做任何处理并无输出。

输入
第1行输入N
接下来输入N行字符串，每一行字符串是一条命令
输出
输出最后一条命令运行结果字符串。

样例1
输入
3
mkdir abc
cd abc
pwd



输出
/abc/


说明：
在根目录创建一个abc的目录并进入abc目录中查看当前目录路径，输出当前路径/abc/



7
mkdir abc
cd abc
mkdir e
cd e
mkdir f
cd f
pwd


 *
 * */

/*
 *
 * 字典树
 * 或嵌套map
 *
 * DirectoryManager {
 *   run
 *   cd
 *   mkdir
 *
 *
 *   privete:
 *
 *   string curPath;
 *   map<string, set<string>> dirs;  某个目录string， 下有哪些目录
 *   string root;
 *
 * }
 *
 * */

#include "iostream"
#include "unordered_map"
#include "unordered_set"
#include "vector"
#include "sstream"
using namespace std;

class DirectoryManager {
    // 初始化目录管理器
public:
    DirectoryManager() {
      this->root = "/";
      this->curPath = this->root;
      dirs[this->root] = unordered_set<string>();  // 所有路径都在有个Key
    }

    void cd(string arg) {
      if (arg == "..") {
        if (curPath != "/") {
          curPath = curPath.substr(0, curPath.size()-1);
          int id = curPath.rfind("/");
          curPath = curPath.substr(0, id+1);
        }
      } else {
        string npath = curPath + arg + "/";
        if (dirs.find(npath) != dirs.end()) { // 如果存在
          curPath = npath;
        }
      }

      return; // 无输出
    }

    string mkdir(string arg) {
      // curpath + arg + /  作为key 加入到 map中
      // 先查看 key 是否存在， 如果不存在， 则加入搭配map中；
      // 且cur path  的  value 加入 arg
      string npath = curPath + arg + "/";
      if (dirs.find(npath) == dirs.end()) { // 如果不存在
        dirs[npath] = unordered_set<string>();
        dirs[curPath].insert(arg);
      }
      return ""; // 无输出
    }

    string pwd() {
      return curPath;
    }

    string run(string cmdStr) {
      istringstream str(cmdStr);
      string cmd;
      string arg;
      str >> cmd >> arg;
      string ret;
      if (cmd == "mkdir" && !arg.empty()) {
        mkdir(arg);
      } else if (cmd == "cd" && !arg.empty()) {
        cd(arg);
      } else if (cmd == "pwd") {
        ret = pwd();
      } else { // 无效
        // nothing
      }
      return ret;
    }


private:
    string curPath;
    unordered_map<string, unordered_set<string>> dirs;
    string root;
};

int main() {
  int n;
  cin >> n;
  cin.ignore();
  vector<string> cmds(n);
  for (int i = 0; i < n; i++) {
    getline(cin, cmds[i]);
  }

  DirectoryManager dm;
  string ret;
  string outRet;
  for (int i = 0; i < cmds.size(); i++) {
    ret = dm.run(cmds[i]);
    if (!ret.empty()) {
      outRet = ret;
    }
  }

  cout << outRet << endl;

  return 0;
}