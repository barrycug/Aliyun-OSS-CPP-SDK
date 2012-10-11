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
#include "HttpClient.h"
#include <algorithm>
#include <iostream>
#include <vector>

namespace OSS
{
HttpClient::~HttpClient(void)
{
	/*
	if(_ptHttpRequest != NULL)
	{
		delete _ptHttpRequest;
		_ptHttpRequest = NULL;
	}
	*/
	if(_asyncHttpRequests.size() >0)
	{
		//释放异步队列
		for(int i=0; i< _asyncHttpRequests.size();i++)
		{
			HTTPRequest * pHRequest = _asyncHttpRequests[i];
			delete pHRequest;
		}
	}
}
HttpClient::HttpClient(ClientConfiguration &clientConfiguration)
{	
	_clientConfiguration  = clientConfiguration;
	
}
bool HttpClient::init(HTTPRequest *ptHttpRequest,Request &request,ExecutionContent &executionContent)
{
	bool rtn = false;
	ptHttpRequest->delegate = this;
	ptHttpRequest->timeOutSeconds = _clientConfiguration.connectionTimeout;
	ptHttpRequest->userAgent = _clientConfiguration.userAgent;
	if ( !_clientConfiguration.proxyHost.empty() && _clientConfiguration.proxyPort > 0)
	{
		ptHttpRequest->proxyHost = _clientConfiguration.proxyHost;
		ptHttpRequest->proxyPort = _clientConfiguration.proxyPort;
		ptHttpRequest->proxyUserName = _clientConfiguration.proxyUserName;
		ptHttpRequest->proxyPassword = _clientConfiguration.proxyPassword;
		ptHttpRequest->proxyDomain = _clientConfiguration.proxyWorkstation;
	}
	ptHttpRequest->requestMethod = request.method;
	switch (request.method)
	{
	case HttpMethod_GET:
		{
		}
		break;
		case HttpMethod_PUT:
		{
			ptHttpRequest->addPostData(request.getContent(),request.getContentLength());
		}
		break;
		case HttpMethod_POST:
		{
			ptHttpRequest->addPostData(request.getContent(),request.getContentLength());
		}
		break;
		case HttpMethod_HEAD:
		{
		}
		break;
		case HttpMethod_DELETE:
		{
		}
		break;
		
	default:
		break;
	}
	map<string,string> dictHeaders = request.getHeaders();
	map < string, string >::iterator iter=dictHeaders.begin();
	for (iter = dictHeaders.begin(); iter != dictHeaders.end(); iter++ ) 
	{
		string key = iter->first;
		string value = iter->second;
	//	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
		if(key.compare("Content-Length")==0 ||key.compare("Host")==0) 
		{
			continue;
		}
		ptHttpRequest->addRequestHeader(key,value);
	}

	iter= dictHeaders.find("Content-Type");
	if(iter == dictHeaders.end()) {
		ptHttpRequest->addRequestHeader("Content-Type","");
	}
	rtn = true;
	iter = request.userInfo.find("method");
	if(iter != request.userInfo.end())
	{
		if(iter->second.compare("FetchObject") == 0)
		{
			map < string, string >::iterator iter2 = request.userInfo.find("path");
			if(iter2 != request.userInfo.end())
			{
				rtn = ptHttpRequest->SetReciveFile(iter2->second);
			}
		}
	}

	return rtn ;
}
ResponseMessage  HttpClient::excute(Request &request_,ExecutionContent &executionContent_)
{

	HTTPRequest *ptHttpRequest = new HTTPRequest(request_.uri);
	
	_userInfos[ptHttpRequest] = request_.userInfo;
	ResponseMessage rm;
	if(init(ptHttpRequest,request_,executionContent_))
	{
		ptHttpRequest->startSynchronous();		
		makeResponseMessage(ptHttpRequest,rm);
	}
	else
	{
		rm.statusCode = 400;
	}
	delete ptHttpRequest;
	ptHttpRequest = NULL;
	return rm;
}
bool HttpClient::submit(Request &request_,ExecutionContent &executionContent_)
{
	HTTPRequest * pHRequest = new HTTPRequest(request_.uri);
	if(init(pHRequest,request_,executionContent_))
	{
		_asyncHttpRequests.push_back(pHRequest);
		_userInfos[pHRequest] = request_.userInfo;
		pHRequest->startAsyncSynchronous();
		return true;
	}
	else
	{
		return false;
	}

}
void HttpClient::makeResponseMessage(HTTPRequest *httpRequest,ResponseMessage &rm)
{
	rm.uri = httpRequest->url;
	rm.statusCode = httpRequest->statusCode;
	rm.setData(httpRequest->resposeData(),httpRequest->resposeDataLength());
	map<HTTPRequest*,map<string,string>>::iterator iter;
	iter = _userInfos.find(httpRequest);
	if(iter != _userInfos.end())
	{
		rm.userInfo = iter->second;
	}

	map<string,string> dict = httpRequest->getResponseHeaders();
	map<string,string> headers = map<string,string>(dict);
	rm.setHeaders(headers);
}
void HttpClient:: OnHttpComplete(HTTPRequest * request)
{
	if(delegate != NULL)
	{
		ResponseMessage rm;
		makeResponseMessage(request,rm);
		delegate->httpClientFinish(this,rm);
	}
	vector<HTTPRequest *>::iterator iter = find(_asyncHttpRequests.begin(), _asyncHttpRequests.end(), request);
    if (iter != _asyncHttpRequests.end()) {
        _asyncHttpRequests.erase(iter);
		delete request;
    }
	
}
void HttpClient:: OnHttpFailed(HTTPRequest * request,HTTP_RESULTCODE code)
{

	
	if(delegate != NULL)
	{
		ResponseMessage rm ;
		makeResponseMessage(request,rm);
		delegate->httpClientFailed(this,rm);
	}
	vector<HTTPRequest *>::iterator iter = find(_asyncHttpRequests.begin(), _asyncHttpRequests.end(), request);
    if (iter != _asyncHttpRequests.end()) {
        _asyncHttpRequests.erase(iter);
		delete request;
    }
}

}
