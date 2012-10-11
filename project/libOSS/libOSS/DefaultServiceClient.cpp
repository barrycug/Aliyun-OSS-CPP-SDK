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
#include "DefaultServiceClient.h"
#include "HttpClient.h"
#include "HttpUtil.h"
namespace OSS
{
DefaultServiceClient::DefaultServiceClient(ClientConfiguration config)
{
	_config = config;
	_httpClient = new HttpClient(_config);
}

DefaultServiceClient::DefaultServiceClient()
{
}

DefaultServiceClient::~DefaultServiceClient(void)
{
	if(_httpClient != NULL)
	{
		delete _httpClient;
		_httpClient = NULL;
	}

}
ResponseMessage DefaultServiceClient::sendRequest(RequestMessage &rm,ExecutionContent &ec)
{
	if(ec.signer != NULL)
	{
		ec.signer->sign(rm);
	}
	Request request;
	bulidRequest(rm,ec,request);
	return sendRequestCore(request,ec);

}
bool DefaultServiceClient::sendRequest_Async(RequestMessage &rm,ExecutionContent &ec)
{
	
	if(ec.signer != NULL)
	{
		ec.signer->sign(rm);
	}
	Request request;
	bulidRequest(rm,ec,request);
	return sendRequestCore_Async(request,ec);
}
void DefaultServiceClient::bulidRequest(RequestMessage &rm,ExecutionContent &ec,Request &request)
{
	
	request.method = rm.method;
	
	request.userInfo = rm.userInfo;
	map<string,string> headers = rm.getHeaders();
	HttpUtil::convertHeaderChartsetFromIso88591(headers);
	request.setHeaders(headers);
	
	string str = rm.endpoint;
	string strRes  = "";
	strRes +=str;
	int pos =str.find_last_of("/");
	int pos2 =rm.resourcePath.find_first_of("/");
	if (!( pos == strRes.length())
		&&(!(pos2 == 0)))
	{
		strRes +="/";
	}
	if (!rm.resourcePath.empty())
	{
		strRes +=rm.resourcePath;
	}
	string str2 =HttpUtil::paramToQueryString(rm.parameters);
	int i = (rm.getContent() != NULL)?1:0;
	int j = (rm.method == HttpMethod_POST)?1:0;
	int k = ((j==0)||(i!=0))?1:0;
	if(!str2.empty() && k != 0)
	{
		strRes +="?";
		strRes +=str2;
	}
	request.uri  = strRes;
	if(j != 0 && rm.getContent() == NULL &&!str2.empty())
	{
		//data Î´×ªÂë
		string str3 =HttpUtil::MbcsToUtf8(str2);
		request.setData((char *)str3.c_str(),str3.size());
	}
	else
	{
		request.setData(rm.getContent(),rm.getContentLength());
	}


}
bool DefaultServiceClient::sendRequestCore_Async(Request &request,ExecutionContent &ec)
 {
	 _httpClient->delegate = this;
	return _httpClient->submit(request,ec);
 }
ResponseMessage  DefaultServiceClient::sendRequestCore(Request &request,ExecutionContent &ec)
 {
	return _httpClient->excute(request,ec);
 }
void DefaultServiceClient::httpClientFinish(HttpClient * httpClient,ResponseMessage &rm)
{
	if(delegate != NULL)
	{
		delegate->serviceClientRequestFinished(this,rm);
	}
}
void DefaultServiceClient::httpClientFailed(HttpClient * httpClient,ResponseMessage &rm)
{
	if(delegate != NULL)
	{
		delegate->serviceClientRequestFailed(this,rm);
	}
}
}
