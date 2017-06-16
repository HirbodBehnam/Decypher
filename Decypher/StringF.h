#include <algorithm>
#include <cctype>
#include <functional> 
#include <string>
#include <sstream>
#include <vector>
#pragma once
using namespace std;

class StringF {
public:
	static vector<string> split(const string &s, const char delim) {
		stringstream ss(s);
		string item;
		vector<string> tokens;
		while (getline(ss, item, delim)) {
			tokens.push_back(item);
		}
		tokens.shrink_to_fit();
		return tokens;
	}
	static string toUpper(string str) {
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		return str;
	}
	static inline std::string &rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}
};