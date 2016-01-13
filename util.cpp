#include "stdafx.h"
#include "util.h"

//ワイド文字列(WCHAR*)をマルチバイト文字列(char*)に変換
errno_t util::wide2char(LPWSTR wstr, char* cstr) {


	size_t wLen = 0;
	errno_t err = 0;

	//ロケール指定
	setlocale(LC_ALL, "japanese");
	//変換
	err = wcstombs_s(&wLen, cstr, 255, wstr, _TRUNCATE);
	return err;
}

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


bool util::create_cmd_process(TCHAR* opt, std::string& out) {
	char mem[80 * 25 * 10];	//	標準出力のバッファ
	DWORD memSz = 0;	//	標準出力のバッファの有効データー数

	//	パイプの作成
	HANDLE readPipe;
	HANDLE writePipe;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	if (CreatePipe(&readPipe, &writePipe, &sa, 0) == 0) {
		//MessageBox(0, _TEXT("パイプが作成できませんでした"), _TEXT("エラー"), MB_OK);
		return false;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.hStdOutput = writePipe;
	si.hStdError = writePipe;
	si.wShowWindow = SW_HIDE;
	TCHAR cmd[MAX_PATH];
	//	プロセスの起動(cmd.exe)
	_stprintf_s(cmd, sizeof(cmd) / sizeof(TCHAR), _TEXT("cmd.exe /K %s"), opt);
	if (CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi) == 0) {
		//MessageBox(0, _TEXT("プロセスの作成に失敗しました"), _TEXT("エラー"), MB_OK);
		return false;
	}
	HANDLE childProcess = pi.hProcess;
	CloseHandle(pi.hThread);
	char readBuf[1025];
	bool end = false;
	do {
		DWORD totalLen, len;
		if (WaitForSingleObject(childProcess, 100) == WAIT_OBJECT_0)
			end = true;
		if (PeekNamedPipe(readPipe, NULL, 0, NULL, &totalLen, NULL) == 0)
			break;
		if (0 < totalLen) {
			if (ReadFile(readPipe, readBuf, sizeof(readBuf) - 1, &len, NULL) == 0)
				return false;
			readBuf[len] = 0;

			if (sizeof(mem) - 1<memSz + len) {	//メモリがあふれないようにクリアする
				mem[0] = 0;
				memSz = 0;
			}
			memSz += len;
			strcat_s(mem, sizeof(mem), readBuf);
			if (totalLen>len)	//	プロセスは終了しているがまだデータがーが残っているので終了を保留
				end = false;
		}
	} while (end == false);

	if (CloseHandle(writePipe) == 0) {
		//MessageBox(0, _TEXT("パイプのクローズに失敗しました"), _TEXT("エラー"), MB_OK);
		return false;
	}
	if (CloseHandle(readPipe) == 0) {
		//MessageBox(0, _TEXT("パイプのクローズに失敗しました"), _TEXT("エラー"), MB_OK);
		return false;
	}
	CloseHandle(pi.hProcess);

	out = mem;
	return true;
}

