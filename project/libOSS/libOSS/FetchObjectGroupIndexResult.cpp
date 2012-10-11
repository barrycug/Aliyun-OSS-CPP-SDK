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
#include "FetchObjectGroupIndexResult.h"
#include "xmlParser.h"
#include "HttpUtil.h"
#include "StringUtil.h"

namespace OSS
{
FetchObjectGroupIndexResult::FetchObjectGroupIndexResult(void)
{
	size = 0;
}
FetchObjectGroupIndexResult::FetchObjectGroupIndexResult(string &strXML)
{
	size = 0;
	MakeFetchObjectGroupIndexResult(strXML);
}


FetchObjectGroupIndexResult::~FetchObjectGroupIndexResult(void)
{
}
void FetchObjectGroupIndexResult::MakeFetchObjectGroupIndexResult(string &strXML)
{
	
	XMLNode xMainNode = XMLNode::parseString(HttpUtil::Utf8ToUnicode(strXML.c_str()));
	XMLNode xNode=xMainNode.getChildNode(L"FileGroup");
	XMLNode xFilePartNode=xNode.getChildNode(L"FilePart");
	int i = 0;
	while(1)
	{
	
		XMLNode xPartNode=xFilePartNode.getChildNode(L"Part",&i);
		if(xPartNode.isEmpty())
		{
			break;
		}
		FilePart filePart;
		XMLNode xETagNode=xPartNode.getChildNode(L"ETag");
		const wchar_t *pwETag = xETagNode.getText();
		string strETag="";
		if(pwETag != NULL)
		{
			strETag.append( HttpUtil::UnicodeToMbcs(pwETag));
		}
		filePart.eTag =StringUtil::trimQuote(strETag);
		XMLNode xPartNameNode=xPartNode.getChildNode(L"PartName");
		const wchar_t *pwPartName = xPartNameNode.getText();
		string strPartName="";
		if(pwPartName != NULL)
		{
			strPartName.append( HttpUtil::UnicodeToMbcs(pwPartName));
		}
		filePart.partName = strPartName;
		XMLNode xPartNumberNode=xPartNode.getChildNode(L"PartNumber");
		const wchar_t *pwPartNumber = xPartNumberNode.getText();
		string strPartNumber="";
		if(pwPartNumber != NULL)
		{
			strPartNumber.append( HttpUtil::UnicodeToMbcs(pwPartNumber));
		}
		filePart.partNumber = atol(strPartNumber.c_str());
		XMLNode xPartSizeNode=xPartNode.getChildNode(L"PartSize");
		const wchar_t *pwPartSize = xPartSizeNode.getText();
		string strPartSize="";
		if(pwPartSize != NULL)
		{
			strPartSize.append( HttpUtil::UnicodeToMbcs(pwPartSize));
		}
		filePart.partSize = atol(strPartSize.c_str());
		filePartsArray.push_back(filePart);
		i++;
	}
	XMLNode xBucketNode=xNode.getChildNode(L"Bucket");
	const wchar_t *pwBucket = xBucketNode.getText();
	string strBucket="";
	if(pwBucket != NULL)
	{
		strBucket.append( HttpUtil::UnicodeToMbcs(pwBucket));
	}
	bucketName = strBucket;

	XMLNode xKeyNode=xNode.getChildNode(L"Key");
	const wchar_t *pwKey = xKeyNode.getText();
	string strKey="";
	if(pwKey != NULL)
	{
		strKey.append( HttpUtil::UnicodeToMbcs(pwKey));
	}
	key = strKey;

	XMLNode xETagNode1=xNode.getChildNode(L"ETag");
	const wchar_t *pwETag1 = xETagNode1.getText();
	string strETag1="";
	if(pwETag1 != NULL)
	{
		strETag1.append( HttpUtil::UnicodeToMbcs(pwETag1));
	}
	eTag =StringUtil::trimQuote(strETag1);

	XMLNode xFileLengthNode=xNode.getChildNode(L"FileLength");
	const wchar_t *pwFileLength = xFileLengthNode.getText();
	string strFileLength="";
	if(pwFileLength != NULL)
	{
		strFileLength.append( HttpUtil::UnicodeToMbcs(pwFileLength));
	}
	size = atol(strFileLength.c_str());

}
}
