#include "stdafx.h"
#include "util.h"
	std::string util::removeStrRegex(std::string& str, const char* pattern) {
		std::regex re(pattern);
		std::string ret = std::regex_replace(str, re, "");
		return ret;
	}


	void util::strReplace(std::string& str, const std::string& from, const std::string& to) {
		std::string::size_type pos = 0;
		while (pos = str.find(from, pos), pos != std::string::npos) {
			str.replace(pos, from.length(), to);
			pos += to.length();
		}
	}

	std::string util::trim(const std::string& string, const char* trimCharacterList)
	{
		std::string result;

		// 左側からトリムする文字以外が見つかる位置を検索します。
		std::string::size_type left = string.find_first_not_of(trimCharacterList);
		if (left != std::string::npos)
		{
			// 左側からトリムする文字以外が見つかった場合は、同じように右側からも検索します。
			std::string::size_type right = string.find_last_not_of(trimCharacterList);

			// 戻り値を決定します。ここでは右側から検索しても、トリムする文字以外が必ず存在するので判定不要です。
			result = string.substr(left, right - left + 1);
		}
		return result;
	}

	void util::removeChars(std::string& str, const char* chars) {
		for (size_t c = str.find_first_of(chars); c != std::string::npos; c = c = str.find_first_of(chars)) {
			str.erase(c, 1);
		}

	}
