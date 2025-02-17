#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <regex>

using namespace std;
struct tableLifeInfo {
		string tableName; // 表名
		string lifeTime; // 生命周期
};

// 检查字符串是否以给定前缀开头
bool startsWith(const std::string& str, const std::string& prefix) {
	return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}
// 检查字符串的前缀是否为指定列表中的之一
bool checkPrefix(const std::string& str, const std::vector<std::string>& prefixes) {
	for (const auto& prefix : prefixes) {
		if (startsWith(str, prefix)) {
			return true;
		}
	}
	return false;
}
// 解析配置文件中的正则表达式配置
std::unordered_map<std::string, std::string> parseSchemaRegexConfig(const std::string& line) {
	std::unordered_map<std::string, std::string> config;
	size_t equalPos = line.find('=');
	if (equalPos != std::string::npos) {
		std::string regexPart = line.substr(1, equalPos-2); // 跳过 [    ]
		std::string timePart = line.substr(equalPos + 1);

		std::istringstream regexStream(regexPart);
		std::string regex;
		while (std::getline(regexStream, regex, ',')) {
			// 去除前后空格
			regex.erase(0, regex.find_first_not_of(" \t"));
			regex.erase(regex.find_last_not_of(" \t") + 1);
//			config[regex] = timePart;
			if (regex.size() > 2 && regex.substr(regex.size()-2) == ".*") {
				config[regex.substr(0, regex.size()-2)] = timePart; // schema 的生命周期
			}
		}
	}
	return config;
}

// 解析配置文件中的指定表配置
std::unordered_map<std::string, unordered_map<string, string>> parseTableConfig(const std::string& line) {
	std::unordered_map<std::string, unordered_map<string, string>> config;
	size_t equalPos = line.find('=');
	if (equalPos != std::string::npos) {
		std::string tablePart = line.substr(1, equalPos-2); // // 跳过 [    ]
		std::string timePart = line.substr(equalPos + 1);

		std::istringstream tableStream(tablePart);
		std::string table;
		while (std::getline(tableStream, table, ',')) {
			// 去除前后空格
			table.erase(0, table.find_first_not_of(" \t"));
			table.erase(table.find_last_not_of(" \t") + 1);
//			config[table] = timePart;
			int dot_pos = table.find('.');
			if (dot_pos != string::npos) {
				config[table.substr(0, dot_pos)][table.substr(dot_pos+1)] = timePart; // table 的生命周期
//				config[table.substr(0, dot_pos)].push_back(tableLifeInfo{table.substr(dot_pos), timePart});
			}
		}
	}
	return config;
}

// 解析配置文件中的指定表配置
bool isValid(const std::string& line) {
	std::vector<std::string> validPrefixes = {"schemas_reg", "schema.tables", "cronTask"};
	if (!checkPrefix(line, validPrefixes)) {
		std::cerr << "Error: The string does not start with a valid prefix." << std::endl;
		return false;
	}
	std::cout << "The string starts with a valid prefix." << std::endl;
	return true;
}


// 解析配置文件中的周期调度配置
// 解析 CronTask 配置的函数
std::pair<std::string, std::string> parseCronTask(const std::string& line) {
	std::pair<std::string, std::string> result;
	size_t commaPos = line.find(',');
	if (commaPos != std::string::npos) {
		// 提取任务名
		result.first = line.substr(0, commaPos);
		// 提取调度周期
		result.second = line.substr(commaPos + 1);
	}
	return result;
}


// 解析整个配置文件
void parseConfigFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	std::unordered_map<std::string, std::string> schemaRegexConfigs;
	std::unordered_map<std::string, unordered_map<string, string>> tableConfigs; // schema1:table1:10s ;  schema1:table2:20s
	std::pair<std::string, std::string> cronTaskConfig;

	std::string line;
	while (std::getline(file, line)) {
		// 忽略注释行
		if (line.empty() || line[0] == '#') continue;
		if (!isValid(line)) {
			std::cout << "test" << std::endl;
			return;
		}

		string schemas_ = "schemas_reg";
		string schema_mat = "schemas_reg";
		string table_mat = "schema.tables";
		string cron_mat = "cronTask";
		if (line.find("schemas_reg") != std::string::npos) {
			auto config = parseSchemaRegexConfig(line.substr(schema_mat.size()+1));
			schemaRegexConfigs.insert(config.begin(), config.end());
		} else if (line.find("schema.tables") != std::string::npos) {
			auto config = parseTableConfig(line.substr(table_mat.size()+1));
			for(auto &pairs : config) { // 遍历每个新配置配置
				for (auto &tablePair : pairs.second) {
					tableConfigs[pairs.first][tablePair.first] = tablePair.second;
				}
			}
		} else if (line.find("cronTask") != std::string::npos) {
			cronTaskConfig = parseCronTask(line.substr(cron_mat.size()+1));
		}
	}

	// 输出解析结果
	std::cout << "Schema Regex Configs:" << std::endl;
	for (const auto& pair : schemaRegexConfigs) {
		std::cout << "Regex: " << pair.first << ", Time: " << pair.second << std::endl;
	}

	std::cout << "\nTable Configs:" << std::endl;
	for (const auto& pair : tableConfigs) {
		for(auto &it : pair.second) {
			std::cout << "Schema: " << pair.first << ", table: " << it.first << ", time: " << it.second << std::endl;
		}
	}

	std::cout << "\nCron Task Config:" << std::endl;
	std::cout << "Task: " << cronTaskConfig.first << ", Time: " << cronTaskConfig.second << std::endl;
}



int test() {
	std::string filename = "config.cfg"; // 替换为实际的配置文件名



	parseConfigFile(filename);
	return 0;
}

int main() {
	test();
	vector<int> a;
	vector<int> b;
	a.insert(a.end(), b.begin(), b.end());
	return 0;
}
