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
#include "OSSOperation.h"
#include "OSSUtil.h"
#include "DateUtil.h"
#include <time.h>
#include "OSSRequestSigner.h"
#include "HttpUtil.h"

namespace OSS
{
OSSOperation::OSSOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client)
{
	_endpoint = endpoint;
	_serviceCredentials = serviceCredentials;
	_ptClient = client;
	_ptClient->delegate = this;
	_signer = NULL;
}


OSSOperation::~OSSOperation(void)
{
	if(_signer != NULL)
	{
		delete _signer;
		_signer = NULL;
	}
}
ResponseMessage OSSOperation::request(HttpMethod httpMethod,string bucketName,string objName,map<string,string> headers,map<string,string> params,char *content,long contentLength,map<string,string> userInfo)
{
	string str = OSSUtil::makeResourcePath(bucketName,objName);
//	string strUtf8 = HttpUtil::MbcsToUtf8(str);
	tm today;
	time_t ltime;
	errno_t err;
	_time64(&ltime);
	 err = _gmtime64_s( &today, &ltime );
	string strDate = DateUtil::formatRfc822Date(today);
	headers.insert(map<string, string> :: value_type("Date",strDate));
	map<string, string>::iterator iter ;
	iter = headers.find("Content-Type");
	if(iter == headers.end())
	{
		headers.insert(map<string, string> :: value_type("Content-Type",""));
	}
	RequestMessage rm;
	rm.endpoint = _endpoint;
	rm.resourcePath = str;
	rm.setHeaders(headers); 
	rm.parameters = params;
	rm.method = httpMethod;
	rm.setData(content,contentLength);
	rm.userInfo = userInfo;
	ExecutionContent ec ;
	ec.chartset = Chartset_UTF8;
	ec.signer = CreateSigner(httpMethod,bucketName,objName);
	return _ptClient->sendRequest(rm,ec);

}
bool OSSOperation::request_Async(HttpMethod httpMethod,string bucketName,string objName,map<string,string> headers,map<string,string> params,char *content,long contentLength,map<string,string> userInfo)
{
	string str = OSSUtil::makeResourcePath(bucketName,objName);
	tm today;
	time_t ltime;
	errno_t err;
	_time64(&ltime);
	 err = _gmtime64_s( &today, &ltime );
	string strDate = DateUtil::formatRfc822Date(today);
	headers.insert(map<string, string> :: value_type("Date",strDate));
	map<string, string>::iterator iter ;
	iter = headers.find("Content-Type");
	if(iter == headers.end())
	{
		headers.insert(map<string, string> :: value_type("Content-Type",""));
	}
	RequestMessage rm;
	rm.endpoint = _endpoint;
	rm.resourcePath = str;
	rm.setHeaders(headers); 
	rm.parameters = params;
	rm.method = httpMethod;
	rm.setData(content,contentLength);
	rm.userInfo = userInfo;
	ExecutionContent ec ;
	ec.chartset = Chartset_UTF8;
	ec.signer = CreateSigner(httpMethod,bucketName,objName);
	return _ptClient->sendRequest_Async(rm,ec);

}
RequestSigner *OSSOperation::CreateSigner(HttpMethod httpMethod,string &bucketName,string &objName)
{
	string str;
	if(_signer != NULL)
	{
		delete _signer;
		_signer = NULL;
	}
	str +="/";
	if(!bucketName.empty())
	{
		str +=bucketName;
	}
	if(!objName.empty())
	{
		str +="/";
		str +=objName;
	}
    _signer = new OSSRequestSigner(httpMethod,str,_serviceCredentials);
	return _signer;

}

}
