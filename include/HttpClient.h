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
#include "HttpClientCallback.h"
#include "ExecutionContent.h"
#include "Request.h"
#include "HttpCallback.h"
#include "ClientConfiguration.h"
#include "ResponseMessage.h"
#include <map>
#include <vector>
using namespace std;
namespace OSS
{
/**
@class HttpClient
@brief web请求封装类，用来发起同步和异步的请求，并维护异步请求队列
*/
class OSSDLL_API HttpClient:HttpCallback
{
public:
	HttpClient(ClientConfiguration &clientConfiguration);
	~HttpClient(void);
public:
	HttpClientCallback *delegate;
	map<string,string> userInfo;
private:
	//同步请求对象
	HTTPRequest *_ptHttpRequest;
	
	ClientConfiguration _clientConfiguration;
	//异步请求队列
	vector<HTTPRequest*> _asyncHttpRequests;
	map<HTTPRequest*,map<string,string>> _userInfos;
public:
	/**
	同步调用
	*/
	ResponseMessage  excute(Request &request,ExecutionContent &executionContent);
	/**
	异步调用
	*/
	bool submit(Request &request,ExecutionContent &executionContent);
private:
	bool init(HTTPRequest *pHRequest,Request &request,ExecutionContent &executionContent);
	void makeResponseMessage(HTTPRequest *httpRequest,ResponseMessage &rm);
private:
	virtual  void OnHttpComplete(HTTPRequest * request);
	virtual  void OnHttpFailed(HTTPRequest * request,  HTTP_RESULTCODE code);
};
}

