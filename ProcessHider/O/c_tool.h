#pragma once

#include <windows.h>    
#include <stdio.h>
#include <string>
#include <time.h>
#include <boost/locale.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#include "lib/aes256cbc/base64.h"
#include "lib/aes256cbc/aes256cbc.h"

using namespace std;
using namespace boost::archive::iterators;

namespace cTool {
	string aes_encode(string _data, string _key, string _iv);
	string aes_decode(string _base64_encode, string _key, string _iv);

	string base64_encode(const string &input);
	string base64_decode(const string &input);

	wstring s2ws(string str);
	string ws2s(wstring wstr);

	string exeName();
	string exePath();

	BOOL isRun(); // �����Ƿ��Ѿ�����

	BOOL checkAppRun(string _mutexName);// ���ָ��mutex�����Ƿ����

	BOOL runApp(string CommandLine); // ���������г���

	string getTime(char* _format); // ����ʱ���ʽ���ص�ǰʱ�� %Y-%m-%d %H:%M:%S
}