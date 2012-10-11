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
#include "OSSRequestSigner.h"
#include "HmacSHA1Signature.h"
#include "SignUtil.h"
#include "StringUtil.h"
namespace OSS
{
OSSRequestSigner::OSSRequestSigner(HttpMethod httpMethod,string &resourcePath,ServiceCredentials &serviceCredentials)
{
	_httpMethod  = httpMethod;
	_resourcePath = resourcePath;
	_serviceCredentials = serviceCredentials;
	_pServiceSignature = new HmacSHA1Signature();
}

OSSRequestSigner::~OSSRequestSigner(void)
{
	if(_pServiceSignature != NULL)
	{
		delete []_pServiceSignature;
		_pServiceSignature = NULL;
	}
}
void OSSRequestSigner::sign(RequestMessage &requestMessage)
{
	string strKey = _serviceCredentials.accessKey;
	string strID = _serviceCredentials.accessID;
	if((!strKey.empty()) && (!strID.empty()))
	{
		string canonicalString = SignUtil::buildCanonicalString(_httpMethod,_resourcePath,requestMessage);
	//	string canonicalStringutf8 =StringUtil::s2utfs(canonicalString);
		printf("%s\n",canonicalString.c_str());
		string signString = _pServiceSignature->computeSignature(canonicalString,strKey);
		printf("%s\n",signString.c_str());
		requestMessage.addHeader("Authorization","OSS "+strID+":"+signString);
	}
	else if(!strID.empty())
	{
		requestMessage.addHeader("Authorization",strID);
	}
}
}
