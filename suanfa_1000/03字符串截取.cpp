#include "iostream"
#include "sstream"
#include "vector"
using namespace std;
int main() {
  int n = 100;
  string str;
  istringstream ist;
  string str1,str2,str3,str4,str5;
  vector<string> res;
  for (int i = 0; i < 200; i++) {
    getline(cin, str);
    if(str.size() == 0) {
      continue;
    }
    if (str == "quit") {
      break;
    }
    ist.clear();
    ist.str(str);
    ist >> str1 >> str2 >> str3 >> str4 >> str5;
    res.push_back(str4);
  }

  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << endl;
  }

  return 0;
}