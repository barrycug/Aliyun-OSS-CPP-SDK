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
#include "MultipartUploadListing.h"
#include "xmlParser.h"
#include "HttpUtil.h"
#include "StringUtil.h"
namespace OSS
{
MultipartUploadListing::MultipartUploadListing(void)
{
}
MultipartUploadListing::MultipartUploadListing(string & strXML)
{
	MakeMultipartUploadListing(strXML);
}


MultipartUploadListing::~MultipartUploadListing(void)
{
}
void MultipartUploadListing::MakeMultipartUploadListing(string & strXML)
{
	XMLNode xMainNode = XMLNode::parseString(HttpUtil::Utf8ToUnicode(strXML.c_str()));
	XMLNode xNode=xMainNode.getChildNode(L"ListMultipartUploadsResult");
	XMLNode xNodeBucket=xNode.getChildNode(L"Bucket");
	const wchar_t *pwBucket = xNodeBucket.getText();
	string strBucket="";
	if(pwBucket != NULL)
	{
		strBucket.append( HttpUtil::UnicodeToMbcs(pwBucket));
	}
	bucketName = strBucket;
	XMLNode xNodeUploadIdMarker=xNode.getChildNode(L"UploadIdMarker");
	const wchar_t *pwUploadIdMarker = xNodeUploadIdMarker.getText();
	string strUploadIdMarker="";
	if(pwUploadIdMarker != NULL)
	{
		strUploadIdMarker.append( HttpUtil::UnicodeToMbcs(pwUploadIdMarker));
	}
	uploadIdMarker = strUploadIdMarker;
	XMLNode xNodeNextKeyMarker=xNode.getChildNode(L"NextKeyMarker");
	const wchar_t *pwNextKeyMarker = xNodeNextKeyMarker.getText();
	string strNextKeyMarker="";
	if(pwNextKeyMarker != NULL)
	{
		strNextKeyMarker.append( HttpUtil::UnicodeToMbcs(pwNextKeyMarker));
	}
	nextKeyMarker = strNextKeyMarker;
	XMLNode xNodeNextUploadIdMarker=xNode.getChildNode(L"NextUploadIdMarker");
	const wchar_t *pwNextUploadIdMarker = xNodeNextUploadIdMarker.getText();
	string strNextUploadIdMarker="";
	if(pwNextUploadIdMarker != NULL)
	{
		strNextUploadIdMarker.append( HttpUtil::UnicodeToMbcs(pwNextUploadIdMarker));
	}
	nextUploadIdMarker = strNextUploadIdMarker;
	XMLNode xNodeDelimiter=xNode.getChildNode(L"Delimiter");
	const wchar_t *pwDelimiter = xNodeDelimiter.getText();
	string strDelimiter="";
	if(pwDelimiter != NULL)
	{
		strDelimiter.append( HttpUtil::UnicodeToMbcs(pwDelimiter));
	}
	delimiter = strDelimiter;
	XMLNode xNodePrefix=xNode.getChildNode(L"Prefix");
	const wchar_t *pwPrefix = xNodePrefix.getText();
	string strPrefix="";
	if(pwPrefix != NULL)
	{
		strPrefix.append( HttpUtil::UnicodeToMbcs(pwPrefix));
	}
	prefix = strPrefix;
	XMLNode xNodeMaxUploads=xNode.getChildNode(L"MaxUploads");
	const wchar_t *pwMaxUploads= xNodeMaxUploads.getText();
	string strMaxUploads="";
	if(pwMaxUploads != NULL)
	{
		strMaxUploads.append( HttpUtil::UnicodeToMbcs(pwMaxUploads));
	}
	maxUploads = atol(strMaxUploads.c_str());
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
	int i = 0;
	while (1)
	{
		XMLNode xNodeUpload=xNode.getChildNode(L"Upload",&i);
		if(xNodeUpload.isEmpty())
		{
			break;
		}
		MultipartUpload multipartUpload;
		XMLNode xNodeKey=xNodeUpload.getChildNode(L"Key");
		const wchar_t *pwKey= xNodeKey.getText();
		string strKey="";
		if(pwKey != NULL)
		{
			strKey.append( HttpUtil::UnicodeToMbcs(pwKey));
		}
		multipartUpload.key = strKey;
		XMLNode xNodeUploadId=xNodeUpload.getChildNode(L"UploadId");
		const wchar_t *pwUploadId= xNodeUploadId.getText();
		string strUploadId="";
		if(pwUploadId!= NULL)
		{
			strUploadId.append( HttpUtil::UnicodeToMbcs(pwUploadId));
		}
		multipartUpload.uploadId = strUploadId;
		XMLNode xNodeInitiated=xNodeUpload.getChildNode(L"Initiated");
		const wchar_t *pwInitiated= xNodeInitiated.getText();
		string strInitiated="";
		if(pwInitiated!= NULL)
		{
			strInitiated.append( HttpUtil::UnicodeToMbcs(pwInitiated));
		}
		multipartUpload.initiated = strInitiated;

		XMLNode xNodeStorageClass=xNodeUpload.getChildNode(L"StorageClass");
		const wchar_t *pwStorageClass= xNodeStorageClass.getText();
		string strStorageClass="";
		if(pwStorageClass!= NULL)
		{
			strStorageClass.append( HttpUtil::UnicodeToMbcs(pwStorageClass));
		}
		multipartUpload.storageClass =strStorageClass;
		multipartUploads.push_back(multipartUpload);
		i++;
	}
	i = 0;
	XMLNode xNodeCommonPrefixes=xNode.getChildNode(L"CommonPrefixes");
	if(!xNodeCommonPrefixes.isEmpty())
	{
		while (1)
		{
			XMLNode xNodePrefix=xNode.getChildNode(L"Prefix",&i);
			if(xNodePrefix.isEmpty())
			{
				break;
			}
			const wchar_t *pwPrefix= xNodePrefix.getText();
			string strPrefix="";
			if(pwPrefix!= NULL)
			{
				strPrefix.append( HttpUtil::UnicodeToMbcs(pwPrefix));
			}
			commonPrefixes.push_back(strPrefix);
			i++;
		}
	}
	
}
 }
