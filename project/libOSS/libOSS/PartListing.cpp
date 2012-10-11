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
#include "PartListing.h"
#include "xmlParser.h"
#include "HttpUtil.h"
#include "StringUtil.h"
namespace OSS
{
PartListing::PartListing(void)
{
	maxParts = 0;
    partNumberMarker = 0;
    isTruncated = false;
    nextPartNumberMarker = 0;
}
PartListing::PartListing(string & strXML)
{
	maxParts = 0;
    partNumberMarker = 0;
    isTruncated = false;
    nextPartNumberMarker = 0;
	MakePartListing(strXML);
}

PartListing::~PartListing(void)
{
}
void PartListing::MakePartListing(string & strXML)
{
	XMLNode xMainNode = XMLNode::parseString(HttpUtil::Utf8ToUnicode(strXML.c_str()));
	XMLNode xNode=xMainNode.getChildNode(L"ListpartsResult");
	XMLNode xNodeBucket=xNode.getChildNode(L"Bucket");
	const wchar_t *pwBucket = xNodeBucket.getText();
	string strBucket="";
	if(pwBucket != NULL)
	{
		strBucket.append( HttpUtil::UnicodeToMbcs(pwBucket));
	}
	bucketName = strBucket;

	XMLNode xNodeKey=xNode.getChildNode(L"Key");
	const wchar_t *pwKey= xNodeKey.getText();
	string strKey="";
	if(pwKey != NULL)
	{
		strKey.append( HttpUtil::UnicodeToMbcs(pwKey));
	}
	key = strKey;
	XMLNode xNodeUploadId=xNode.getChildNode(L"UploadId");
	const wchar_t *pwUploadId = xNodeUploadId.getText();
	string strUploadId="";
	if(pwUploadId != NULL)
	{
		strUploadId.append( HttpUtil::UnicodeToMbcs(pwUploadId));
	}
	uploadId = strUploadId;
	XMLNode xNodeNextPartNumberMarker=xNode.getChildNode(L"NextPartNumberMarker");
	const wchar_t *pwNextPartNumberMarker = xNodeNextPartNumberMarker.getText();
	string strNextPartNumberMarker="";
	if(pwNextPartNumberMarker != NULL)
	{
		strNextPartNumberMarker.append( HttpUtil::UnicodeToMbcs(pwNextPartNumberMarker));
	}
	nextPartNumberMarker = atol(strNextPartNumberMarker.c_str());

	XMLNode xNodeMaxParts=xNode.getChildNode(L"MaxParts");
	const wchar_t *pwMaxParts = xNodeMaxParts.getText();
	string strMaxParts="";
	if(pwMaxParts != NULL)
	{
		strMaxParts.append( HttpUtil::UnicodeToMbcs(pwMaxParts));
	}
	maxParts = atol(strMaxParts.c_str());

	XMLNode xNodeIsTruncated=xNode.getChildNode(L"IsTruncated");
	const wchar_t *pwIsTruncated= xNodeIsTruncated.getText();
	string strIsTruncated="";
	if(pwIsTruncated != NULL)
	{
		strIsTruncated.append( HttpUtil::UnicodeToMbcs(pwIsTruncated));
	}
	if(strIsTruncated.compare("true")==0)
	{
		isTruncated = true;
	}
	else
	{
		isTruncated = false;
	}
	XMLNode xNodeStorageClass=xNode.getChildNode(L"StorageClass");
	const wchar_t *pwStorageClass= xNodeStorageClass.getText();
	string strStorageClass="";
	if(pwStorageClass!= NULL)
	{
		strStorageClass.append( HttpUtil::UnicodeToMbcs(pwStorageClass));
	}
	storageClass = strStorageClass;
	int i=0;
	while (1)
	{
		XMLNode xNodePart=xNode.getChildNode(L"Part");
		if(xNodePart.isEmpty())
		{
			break;
		}
		PartSummary partSummary;
		XMLNode xNodePartNumber=xNodePart.getChildNode(L"PartNumber");
		const wchar_t *pwPartNumber= xNodePartNumber.getText();
		string strPartNumber="";
		if(pwPartNumber != NULL)
		{
			strPartNumber.append( HttpUtil::UnicodeToMbcs(pwPartNumber));
		}
		partSummary.partNumber = atoi(strPartNumber.c_str());
		XMLNode xNodeLastModified=xNodePart.getChildNode(L"LastModified");
		const wchar_t *pwLastModified= xNodeLastModified.getText();
		string strLastModified="";
		if(pwLastModified != NULL)
		{
			strLastModified.append( HttpUtil::UnicodeToMbcs(pwLastModified));
		}
		partSummary.lastModified = strLastModified;
		XMLNode xNodeETag=xNodePart.getChildNode(L"ETag");
		const wchar_t *pwETag= xNodeETag.getText();
		string strETag="";
		if(pwETag != NULL)
		{
			strETag.append( HttpUtil::UnicodeToMbcs(pwETag));
		}
		partSummary.eTag = StringUtil::trimQuote(strETag);
		XMLNode xNodeSize=xNodePart.getChildNode(L"Size");
		const wchar_t *pwSize= xNodeSize.getText();
		string strSize="";
		if(pwSize != NULL)
		{
			strSize.append( HttpUtil::UnicodeToMbcs(pwSize));
		}
		partSummary.size = atol(strSize.c_str());
		parts.push_back(partSummary);
	}
}
}
