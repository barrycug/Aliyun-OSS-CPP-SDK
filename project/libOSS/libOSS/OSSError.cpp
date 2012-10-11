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
#include "OSSError.h"
#include "xmlParser.h"
#include "HttpUtil.h"
namespace OSS
{
OSSError::OSSError(void)
{
}


OSSError::~OSSError(void)
{
}
OSSError::OSSError(string &strXML)
{
	XMLNode xMainNode = XMLNode::parseString(HttpUtil::Utf8ToUnicode(strXML.c_str()));
	XMLNode xNode=xMainNode.getChildNode(L"Error");
	XMLNode xCodeNode=xNode.getChildNode(L"Code");
	const wchar_t *pwcode = xCodeNode.getText();
	if(pwcode != NULL)
	{
		code.append( HttpUtil::UnicodeToMbcs(pwcode));
	}
	XMLNode xMessageNode=xNode.getChildNode(L"Message");
	const wchar_t *pwmessage = xMessageNode.getText();
	message.append( HttpUtil::UnicodeToMbcs(pwmessage));

	XMLNode xStringToSignBytesNode=xNode.getChildNode(L"StringToSignBytes");
	const wchar_t *pwstringToSignBytes = xStringToSignBytesNode.getText();
	if(pwstringToSignBytes != NULL)
	{
		stringToSignBytes.append( HttpUtil::UnicodeToMbcs(pwstringToSignBytes));
	}

	XMLNode xSignatureProvidedNode=xNode.getChildNode(L"SignatureProvided");
	const wchar_t *pwsignatureProvided = xSignatureProvidedNode.getText();
	if(pwsignatureProvided != NULL)
	{
		signatureProvided.append( HttpUtil::UnicodeToMbcs(pwsignatureProvided));
	}

	XMLNode xStringToSignNode=xNode.getChildNode(L"StringToSign");
	const wchar_t *pwstringToSign = xStringToSignNode.getText();
	if(pwstringToSign != NULL)
	{
		stringToSign.append( HttpUtil::UnicodeToMbcs(pwstringToSign));
	}

	XMLNode xOSSAccessKeyIdNode=xNode.getChildNode(L"OSSAccessKeyId");
	const wchar_t *pwaccessKeyID = xOSSAccessKeyIdNode.getText();
	if(pwaccessKeyID != NULL)
	{
		accessKeyID.append( HttpUtil::UnicodeToMbcs(pwaccessKeyID));
	}

	XMLNode xRequestIdNode=xNode.getChildNode(L"RequestId");
	const wchar_t *pwrequestID = xRequestIdNode.getText();
	if(pwrequestID != NULL)
	{
		requestID.append( HttpUtil::UnicodeToMbcs(pwrequestID));
	}

	XMLNode xHostIdNode=xNode.getChildNode(L"HostId");
	const wchar_t *pwrHostID = xHostIdNode.getText();
	if(pwrHostID != NULL)
	{
		hostID.append( HttpUtil::UnicodeToMbcs(pwrHostID));
	}
}
}
