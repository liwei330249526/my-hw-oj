#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

// 函数用于检查一行内容是否包含指定字符串
bool containsDuckDB(const std::string& line) {
  return line.find("duckdb")!= std::string::npos;
}

int main() {
  std::string projectPath = "/home/liwei/mywork/duckdb";  // 替换为实际的项目目录路径

  std::ofstream outputFile("result.txt", std::ios::app);
  if (!outputFile.is_open()) {
    std::cerr << "无法打开输出文件: " <<"result.txt" << std::endl;
    return 0;
  }
  try {
    for (bfs::recursive_directory_iterator it(projectPath); it!= bfs::recursive_directory_iterator(); ++it) {
      if (bfs::is_regular_file(*it)) {
        std::string fileExtension = it->path().extension().string();
        // 只处理常见的源代码文件扩展名，可按需扩展
        if (fileExtension == ".cpp" || fileExtension == ".h" || fileExtension == ".c") {
          std::ifstream file(it->path().string());
          if (file.is_open()) {
            std::string line;
            int lineNumber = 0;
            while (std::getline(file, line)) {
              lineNumber++;
              if(line.find("include") != std::string::npos) {
                continue;
              }
              if (line.find("namespace") != std::string::npos) {
                continue;
              }

              if (line.find("namespace") != std::string::npos) {
                continue;
              }

              if (line.find("using") != std::string::npos) {
                continue;
              }
              if (line.find("duckdb::") != std::string::npos) { // 存在，不考虑
                continue;
              }

//              if (line.find("throw") == std::string::npos) { // 不存在，不考虑
//                continue;
//              }

//              if(line.find("https://duckdb") == std::string::npos) {
//                continue;
//              }


              if (containsDuckDB(line)) {
                outputFile << "文件名: " << it->path().filename().string() << " | ";
                outputFile << "行号: " << lineNumber << " | ";
                outputFile << "内容: " << line << std::endl;
              }
            }
            file.close();
          } else {
            std::cerr << "无法打开文件: " << it->path().string() << std::endl;
          }
        }
      }
    }
  } catch (const bfs::filesystem_error& e) {
    std::cerr << "文件系统错误: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}