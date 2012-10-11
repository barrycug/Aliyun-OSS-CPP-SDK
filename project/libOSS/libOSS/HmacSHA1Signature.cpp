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
#include "HmacSHA1Signature.h"
#include "HttpUtil.h"
#include "sha1.h"
#include "base64.h"
#include "OSSUtil.h"
namespace OSS
{
HmacSHA1Signature* g_pHmacSHA1Signature = NULL;
HmacSHA1Signature *HmacSHA1Signature::GetInstance()
{
	if (g_pHmacSHA1Signature == NULL)
	{
		g_pHmacSHA1Signature = new HmacSHA1Signature();

	}

	return g_pHmacSHA1Signature;
}
string HmacSHA1Signature::getAlgorithm()
{
	return "HmacSHA1";
}
string HmacSHA1Signature::getVersion() 
{
	return "1";
}
string HmacSHA1Signature::computeSignature(string &content,string &secret)
{
	string rtnString ;
	unsigned char digest[20];
	string strContent = HttpUtil::MbcsToUtf8(content);
	printf("%s\n",strContent.c_str());
	string strSecret = HttpUtil::MbcsToUtf8(secret);
	hmac_sha1((unsigned char*)strContent.c_str(),strContent.size(), (unsigned char*)strSecret.c_str(),strSecret.size(), digest);
	rtnString = base64_encode(digest,20);
	rtnString = HttpUtil::MbcsToUtf8(rtnString);
	return rtnString;

}
HmacSHA1Signature::HmacSHA1Signature(void)
{
}


HmacSHA1Signature::~HmacSHA1Signature(void)
{
}
}
