/*
 Copyright 2012 baocai zhang. All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 The views and conclusions contained in the software and documentation are those of the authors and should not be interpreted as representing official policies, either expressed or implied, of the FreeBSD Project.
 */

/*
 @author baocai zhang
 website:www.giser.net
 email:zhangbaocaicug@gmail.com
 */
#pragma warning(disable:4251)
#ifdef LIBOSS_EXPORTS
#define OSSDLL_API __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define OSSDLL_API __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif 

#pragma once
#include <map>
#include <xstring>
#include "OSSApi.h"
using namespace std;
namespace OSS
{
/**
@class HttpUtil
@brief Http相关通用处理类
*/
class OSSDLL_API HttpUtil
{
public:
	HttpUtil(void);
	~HttpUtil(void);
public:
	static void convertHeaderChartsetFromIso88591(map<string,string> &headers);
	static void convertHeaderChartsetToIso88591(map<string,string> &headers);
	static string paramToQueryString(map<string,string>&dict);
	static string UrlEncode(string& szToEncode);
	static string UrlDecode(string& szToDecode);
	static unsigned int utf8_decode( char *s, unsigned int *pi );

	static char* MbcsToUtf8(const char* pMbcs);
	static char* Utf8ToMbcs(const char* pUtf8);
	static char*	 UnicodeToMbcs(const wchar_t* pUnicode);
	static wchar_t* MbcsToUnicode(const char* pMbcs);
	static char*  UnicodeToUtf8(const wchar_t* pUnicode);
	static wchar_t*  Utf8ToUnicode(const char* pUtf8);
	static string MbcsToUtf8(string &str);
	static string Utf8ToMbcs(string &str);
};
}

