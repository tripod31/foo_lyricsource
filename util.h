#pragma once

#include <string>
#include <regex>

std::string removeStrRegex(std::string& str, const char* pattern);
void strReplace(std::string& str, const std::string& from, const std::string& to);
std::string trim(const std::string& string, const char* trimCharacterList = " \t\v\r\n");
void removeChars(std::string& str, const char* chars = " \t\v\r\n");
