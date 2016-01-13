#pragma once

#include <string>
#include <regex>
class util {
public:
	//ワイド文字列(WCHAR*)をマルチバイト文字列(char*)に変換
	static errno_t wide2char(LPWSTR wstr, char* cstr);
	static std::string removeStrRegex(std::string& str, const char* pattern);
	static void strReplace(std::string& str, const std::string& from, const std::string& to);
	static std::string trim(const std::string& string, const char* trimCharacterList = " \t\v\r\n");
	static void removeChars(std::string& str, const char* chars = " \t\v\r\n");
	static bool util::create_cmd_process(TCHAR* opt, std::string& out);
};
