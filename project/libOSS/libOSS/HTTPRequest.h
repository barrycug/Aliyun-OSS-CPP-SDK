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
#include "HTTPRequest.h"
#include "HttpCallback.h"
#include <curl/curl.h> 
#include <string>
#include <map>
#include "OSSApi.h"
using namespace std;
namespace OSS
{
struct data {
  char trace_ascii; /* 1 or 0 */ 
};
/**
@class HTTPRequest
@brief 对libcurl封装，完成基本的web请求，包括get,post,head,put,delete
*/
class OSSDLL_API HTTPRequest
{
public:
	HTTPRequest(string url_ );
	virtual~HTTPRequest(void);
public:
	string  userAgent;
	string  proxyHost;
	long    proxyPort;
	long    timeOutSeconds;
	string  proxyUserName;
	string  proxyPassword;
	string  proxyDomain;
	HttpMethod  requestMethod;
	HttpCallback * delegate;
	string url;
	int    statusCode;
	
	
public:
	bool isRunning;
private:
	char * _data;
	char * _dataStart;
	long   _dataLength;
	map<string,string> _headers;
	map<string,string> _responseHeaders;
private:
	char *			_pchResultData; 
	unsigned long	_uLength;		 
	unsigned long	_uWritePos;	 
	//文件输出对象
	FILE  *_pf;
public:
	void addPostData(char * data,long length);
	void addRequestHeader(string key,string value);
	void reset();
	HTTP_RESULTCODE startSynchronous();
	bool startAsyncSynchronous();
	char * resposeData();
	long   resposeDataLength();
	map<string,string> getResponseHeaders();
public:
	static   size_t	ProcessResult( void* data, size_t size, size_t nmemb, void *pHttp );
	static   size_t	Reader( void* data, size_t size, size_t nmemb, void *pHttp );
	static   int  my_trace(CURL *handle, curl_infotype type,char *data, size_t size,void *userp);
	static   void dump(const char *text,FILE *stream, unsigned char *ptr, size_t size,char nohex);
	static   size_t ProcessHeaders(void *ptr, size_t size, size_t nmemb, void *pHttp) ;
public:
	CURLcode DoHttpGet();
	CURLcode DoHttpPost();
	CURLcode DoHttpHead();
	CURLcode DoHttpPut();
	CURLcode DoHttpDelete();
public:	
	bool AsyncDoHttpGet();
	bool AsyncDoHttpPost();
	bool AsyncDoHttpHead();
	bool AsyncDoHttpPut();
	bool AsyncDoHttpDelete();
public:
	bool SetReciveFile(string & filePath);
private:
	curl_slist * MakeHeaders(CURL *curl);
	void SetBaseParam(CURL *curl);
private:
	bool WriteResultData(char* pchData, unsigned long  uLength);
	size_t ReadData(char* pchData, size_t size, size_t nmemb);
	size_t GetHeaders(void *ptr, size_t size, size_t nmemb) ;


};
};

