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
#include "stdafx.h"
#include "HttpUtil.h"
#include <Windows.h>
#include <assert.h>


namespace OSS
{
HttpUtil::HttpUtil(void)
{
}


HttpUtil::~HttpUtil(void)
{
}

void HttpUtil::convertHeaderChartsetFromIso88591(map<string,string> &headers)
{
	map<string,string>::iterator iter = headers.begin();
	for (iter = headers.begin(); iter != headers.end(); iter++)
	{
		string strKey = iter->first;
		/*
		if(strKey.compare("Content-MD5") == 0)
		{
			continue;
		}
		*/
		string strValue = iter->second;
		string strNewValue = HttpUtil::MbcsToUtf8(strValue);
		iter->second = strNewValue;
	}
}
void HttpUtil::convertHeaderChartsetToIso88591(map<string,string> &headers)
{
	map<string,string>::iterator iter = headers.begin();
	for (iter = headers.begin(); iter != headers.end(); iter++)
	{
		string strKey = iter->first;
		string strValue = iter->second;
		string strNewValue = HttpUtil::Utf8ToMbcs(strValue);
		iter->second = strNewValue;
	}
}


string HttpUtil::paramToQueryString(map<string,string>&dict )
{

	string rtnString =  "";
	if(dict.size() == 0)
	{
		return rtnString;
	}
	int i = 1;
	map<string,string>::iterator iter = dict.begin();
	for (iter = dict.begin(); iter != dict.end(); iter++)
	{
		string strKey = iter->first;
		string strValue = iter->second;
		if(i == 0)
		{
			rtnString+="&";
		}
		rtnString+=strKey;
		if(!strValue.empty())
		{
			rtnString+="=";
			strValue = HttpUtil::UrlEncode(strValue);
			rtnString+=strValue;
		}
		i=0;
	}
	return rtnString;
	
	
}
wchar_t* HttpUtil::Utf8ToUnicode(const char* pUtf8)
{
	assert(pUtf8);
	int nChar = MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, NULL, 0);

	int nSize = nChar*sizeof(wchar_t) + 1;
	wchar_t* pwchBuffer = new wchar_t[nSize];

	nChar = MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, pwchBuffer, nSize);
	if(nChar == 0)
	{
		delete []pwchBuffer;
		return NULL;
	}

	pwchBuffer[nChar] = 0;
	return pwchBuffer;
}

string HttpUtil::MbcsToUtf8(string &str)
{
	wchar_t * strW = HttpUtil::MbcsToUnicode(str.c_str());
	char * strUtf8 = HttpUtil::UnicodeToUtf8(strW);
	string rStr = string(strUtf8);
	delete [] strW;
	delete [] strUtf8;
	return rStr;
}
string HttpUtil::Utf8ToMbcs(string &str)
{
	wchar_t * strW  =Utf8ToUnicode(str.c_str());
	char * strMbcs = HttpUtil::UnicodeToMbcs(strW);
	string rStr = string(strMbcs);
	delete [] strW;
	delete [] strMbcs;
	return rStr;
}
char* HttpUtil::UnicodeToUtf8(const wchar_t* pUnicode)
{
	assert(pUnicode);
	int nChar = WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, 0, 0, 0, 0);

	int nSize = nChar*sizeof(char) + 1;
	char* pchBuffer = new char[nSize];
	
	nChar = WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, pchBuffer, nSize, 0, 0);
	if( nChar == 0 )
	{
		delete[] pchBuffer;
		return NULL;
	}

	pchBuffer[nChar]= 0;
	return pchBuffer;
}

wchar_t*HttpUtil::MbcsToUnicode(const char* pMbcs)
{
	int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
	int nChar = MultiByteToWideChar(codepage, 0, pMbcs, -1, NULL,0);

	int nSize = nChar * sizeof(wchar_t) + 1;
	wchar_t* pwchBuffer = new wchar_t[nSize];

	nChar = MultiByteToWideChar(codepage, 0, pMbcs, -1, pwchBuffer, nSize);
	if(nChar == 0)
	{
		delete[] pwchBuffer;
		return NULL;
	}

	pwchBuffer[nChar]=0;

	return pwchBuffer;
}

char*	HttpUtil::UnicodeToMbcs(const wchar_t* pUnicode)
{
	int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
	int nChar = WideCharToMultiByte(codepage, 0, pUnicode, -1, 0, 0, 0, 0);
	int nSize = nChar * sizeof(char) + 1;

	char* pchBuffer = new char[nSize];
	nChar = WideCharToMultiByte(codepage, 0, pUnicode, -1, pchBuffer, nSize, 0, 0);
	if( nChar == 0 )
	{
		delete[] pchBuffer;
		return NULL;
	}

	pchBuffer[nChar]= 0;
	return pchBuffer;
}

/*
string HttpUtil::UrlEncode(string& szToEncode)
{
	std::string src = szToEncode;
	char hex[] = "0123456789ABCDEF";
	string dst;

	for (size_t i = 0; i < src.size(); ++i)
	{
		unsigned char cc = src[i];
		if (isascii(cc))
		{
			if (cc == ' ')
			{
				dst += "%20";
			}
			else
				dst += cc;
		}
		else
		{
			unsigned char c = static_cast<unsigned char>(src[i]);
			dst += '%';
			dst += hex[c / 16];
			dst += hex[c % 16];
		}
	}
	return dst;
}


string HttpUtil::UrlDecode(string& szToDecode)
{
	std::string result;
	int hex = 0;
	for (size_t i = 0; i < szToDecode.length(); ++i)
	{
		switch (szToDecode[i])
		{
		case '+':
			result += ' ';
			break;
		case '%':
			if (isxdigit(szToDecode[i + 1]) && isxdigit(szToDecode[i + 2]))
			{
				std::string hexStr = szToDecode.substr(i + 1, 2);
				hex = strtol(hexStr.c_str(), 0, 16);
				//字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@]
				//可以不经过编码直接用于URL
				if (!((hex >= 48 && hex <= 57) ||	//0-9
					(hex >=97 && hex <= 122) ||	//a-z
					(hex >=65 && hex <= 90) ||	//A-Z
					//一些特殊符号及保留字[$-_.+!*'(),]  [$&+,/:;=?@]
					hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
					|| hex == 0x2a || hex == 0x2b|| hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
					|| hex == 0x3A || hex == 0x3B|| hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
					))
				{
					result += char(hex);
					i += 2;
				}
				else result += '%';
			}else {
				result += '%';
			}
			break;
		default:
			result += szToDecode[i];
			break;
		}
	}
	return result;
}
*/
unsigned int HttpUtil::utf8_decode( char *s, unsigned int *pi )
{
    unsigned int c;
    int i = *pi;

    if ((s[i] & 128)== 0 ) {
        c = (unsigned int) s[i];
        i += 1;
    } else if ((s[i] & 224)== 192 ) { /* 110xxxxx & 111xxxxx == 110xxxxx */
        c = (( (unsigned int) s[i] & 31 ) << 6) +
            ( (unsigned int) s[i+1] & 63 );
        i += 2;
    } else if ((s[i] & 240)== 224 ) { /* 1110xxxx & 1111xxxx == 1110xxxx */
        c = ( ( (unsigned int) s[i] & 15 ) << 12 ) +
            ( ( (unsigned int) s[i+1] & 63 ) << 6 ) +
            ( (unsigned int) s[i+2] & 63 );
        i += 3;
    } else if ((s[i] & 248)== 240 ) { /* 11110xxx & 11111xxx == 11110xxx */
        c =  ( ( (unsigned int) s[i] & 7 ) << 18 ) +
            ( ( (unsigned int) s[i+1] & 63 ) << 12 ) +
            ( ( (unsigned int) s[i+2] & 63 ) << 6 ) +
            ( (unsigned int) s[i+3] & 63 );
        i+= 4;
    } else if ((s[i] & 252)== 248 ) { /* 111110xx & 111111xx == 111110xx */
        c = ( ( (unsigned int) s[i] & 3 ) << 24 ) +
            ( ( (unsigned int) s[i+1] & 63 ) << 18 ) +
            ( ( (unsigned int) s[i+2] & 63 ) << 12 ) +
            ( ( (unsigned int) s[i+3] & 63 ) << 6 ) +
            ( (unsigned int) s[i+4] & 63 );
        i += 5;
    } else if ((s[i] & 254)== 252 ) { /* 1111110x & 1111111x == 1111110x */
        c = ( ( (unsigned int) s[i] & 1 ) << 30 ) +
            ( ( (unsigned int) s[i+1] & 63 ) << 24 ) +
            ( ( (unsigned int) s[i+2] & 63 ) << 18 ) +
            ( ( (unsigned int) s[i+3] & 63 ) << 12 ) +
            ( ( (unsigned int) s[i+4] & 63 ) << 6 ) +
            ( (unsigned int) s[i+5] & 63 );
        i += 6;
    } else {
        c = '?';
        i++;
    }
    *pi = i;
    return c;
}
string HttpUtil::UrlEncode(string& src)
{
    static    char hex[] = "0123456789ABCDEF";
    std::string dst;
    
    for (size_t i = 0; i < src.size(); i++)
    {
        unsigned char ch = src[i];
        if (isalnum(ch))
        {
            dst += ch;
        }
        else
            if (src[i] == ' ')
            {
                dst += '+';
            }
            else
            {
                unsigned char c = static_cast<unsigned char>(src[i]);
                dst += '%';
                dst += hex[c / 16];
                dst += hex[c % 16];
            }
    }
    return dst;
}
string HttpUtil::UrlDecode(string& src)
{
    std::string dst, dsturl;
    int srclen = src.size();
    for (size_t i = 0; i < srclen; i++)
    {
        if (src[i] == '%')
        {
            if(isxdigit(src[i + 1]) && isxdigit(src[i + 2]))
            {
                char c1 = src[++i];
                char c2 = src[++i];
                c1 = c1 - 48 - ((c1 >= 'A') ? 7 : 0) - ((c1 >= 'a') ? 32 : 0);
                c2 = c2 - 48 - ((c2 >= 'A') ? 7 : 0) - ((c2 >= 'a') ? 32 : 0);
                dst += (unsigned char)(c1 * 16 + c2);
            }
        }
        else
            if (src[i] == '+')
            {
                dst += ' ';
            }
            else
            {
                dst += src[i];
            }
    }
    int len = dst.size();
    
    for(unsigned int pos = 0; pos < len;)
    {
        unsigned int nvalue = utf8_decode((char *)dst.c_str(), &pos);
        dsturl += (unsigned char)nvalue;
    }
    return dsturl;
}
}