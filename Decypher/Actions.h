#pragma once
#include "StringF.h"
#include <fstream>
#include <string>
using namespace std;

class Actions
{
public:
	static int Max(const int x, const int y) { return x > y ? x : y; }
	static bool FileValidDEC_ENG(const string FileName){
		ifstream infile;
		infile.open(FileName);
		string l;
		getline(infile, l);
		return l.find("#DEC_ENC::") == 0;
	}
	static bool FileSpiltsCheck(const string FileName) {
		ifstream infile;
		infile.open(FileName);
		string l;
		getline(infile, l);
		vector<string> s = StringF::split(l, ':');
		return s.size() == 8;
	}
	static bool DECFormat(const string FileName) {
		try {
			string s = "";
			vector<string> v = StringF::split(FileName, '.');
			return v[v.size() - 1] == "dec";
		}
		catch (...) {
			return false;
		}
		return false;
	}
};