#pragma once
#include <conio.h>
#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
class File {
public:
	static bool Exists(const string& name) {
		DWORD dwAttrib = GetFileAttributesA(name.c_str());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
	static long long FileSize(const string Path) {
		struct __stat64 st;
		__stat64(Path.c_str(), &st);
		return st.st_size;
	}
};