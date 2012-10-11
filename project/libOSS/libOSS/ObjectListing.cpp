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
#include "ObjectListing.h"
#include "xmlParser.h"
#include "HttpUtil.h"
#include "Owner.h"
namespace OSS
{
ObjectListing::ObjectListing(string &strXML)
{
	MakeObjectListing(strXML);
}
ObjectListing::ObjectListing(void)
{
}


ObjectListing::~ObjectListing(void)
{
}
void ObjectListing:: MakeObjectListing(string &strXML)
{
	XMLNode xMainNode = XMLNode::parseString(HttpUtil::Utf8ToUnicode(strXML.c_str()));
	XMLNode xNode=xMainNode.getChildNode(L"ListBucketResult");
	XMLNode xNameNode=xNode.getChildNode(L"Name");
	const wchar_t *pwName = xNameNode.getText();
	string strName="";
	if(pwName != NULL)
	{
		strName.append( HttpUtil::UnicodeToMbcs(pwName));
	}
	bucketName = strName;
	XMLNode xPrefixNode=xNode.getChildNode(L"Prefix");
	const wchar_t *pwPrefix = xPrefixNode.getText();
	string strPrefix="";
	if(pwPrefix != NULL)
	{
		strPrefix.append( HttpUtil::UnicodeToMbcs(pwPrefix));
	}
	prefix = strPrefix;
	XMLNode xMarkerNode=xNode.getChildNode(L"Marker");
	const wchar_t *pwMarker = xMarkerNode.getText();
	string strMarker="";
	if(pwMarker != NULL)
	{
		strMarker.append( HttpUtil::UnicodeToMbcs(pwMarker));
	}
	marker = strMarker;
	XMLNode xMaxKeysNode=xNode.getChildNode(L"MaxKeys");
	const wchar_t *pwMaxKeys = xMaxKeysNode.getText();
	string strMaxKeys="";
	if(pwMaxKeys != NULL)
	{
		strMaxKeys.append( HttpUtil::UnicodeToMbcs(pwMaxKeys));
	}

	XMLNode xNextMarkerNode=xNode.getChildNode(L"NextMarker");
	const wchar_t *pwNextMarker = xNextMarkerNode.getText();
	string strNextMarker="";
	if(pwNextMarker != NULL)
	{
		strNextMarker.append( HttpUtil::UnicodeToMbcs(pwNextMarker));
	}
	nextMarker =strNextMarker;
	
	XMLNode xDelimiterNode=xNode.getChildNode(L"Delimiter");
	const wchar_t *pwDelimiter = xDelimiterNode.getText();
	string strDelimiter="";
	if(pwDelimiter != NULL)
	{
		strDelimiter.append( HttpUtil::UnicodeToMbcs(pwDelimiter));
	}
	delimiter = strDelimiter;

	XMLNode xIsTruncatedNode=xNode.getChildNode(L"IsTruncated");
	const wchar_t *pwIsTruncated = xIsTruncatedNode.getText();
	string strIsTruncated="";
	if(pwIsTruncated != NULL)
	{
		strIsTruncated.append( HttpUtil::UnicodeToMbcs(pwIsTruncated));
	}
	if(strIsTruncated.compare("true") == 0)
	{
		isTruncated = true;
	}
	else
	{
		isTruncated = false;
	}
	

	int i=0;
	while (1)
	{
		XMLNode xContentsNode=xNode.getChildNode(L"Contents",&i);
		if(xContentsNode.isEmpty())
		{
			break;
		}
		XMLNode xKeyNode=xContentsNode.getChildNode(L"Key");
		const wchar_t *pwKey = xKeyNode.getText();
		string strKey="";
		if(pwKey != NULL)
		{
			strKey.append( HttpUtil::UnicodeToMbcs(pwKey));
		}

		XMLNode xLastModifiedNode=xContentsNode.getChildNode(L"LastModified");
		const wchar_t *pwLastModified = xLastModifiedNode.getText();
		string strLastModified="";
		if(pwLastModified != NULL)
		{
			strLastModified.append( HttpUtil::UnicodeToMbcs(pwLastModified));
		}
		XMLNode xETagNode=xContentsNode.getChildNode(L"ETag");
		const wchar_t *pwETag = xETagNode.getText();
		string strETag="";
		if(pwETag != NULL)
		{
			strETag.append( HttpUtil::UnicodeToMbcs(pwETag));
		}
		strETag =strETag.substr(1,strETag.size()-2);

		XMLNode xTypeNode=xContentsNode.getChildNode(L"Type");
		const wchar_t *pwType = xTypeNode.getText();
		string strType="";
		if(pwType != NULL)
		{
			strType.append( HttpUtil::UnicodeToMbcs(pwType));
		}
		XMLNode xSizeNode=xContentsNode.getChildNode(L"Size");
		const wchar_t *pwSize = xSizeNode.getText();
		string strSize="";
		if(pwSize != NULL)
		{
			strSize.append( HttpUtil::UnicodeToMbcs(pwSize));
		}
		long size = atol(strSize.c_str());

		XMLNode xStorageClassNode=xContentsNode.getChildNode(L"StorageClass");
		const wchar_t *pwStorageClass = xStorageClassNode.getText();
		string strStorageClass="";
		if(pwStorageClass != NULL)
		{
			strStorageClass.append( HttpUtil::UnicodeToMbcs(pwStorageClass));
		}
		XMLNode xOwnerNode=xContentsNode.getChildNode(L"Owner");
		XMLNode xIDNode=xOwnerNode.getChildNode(L"ID");
		const wchar_t *pwID = xIDNode.getText();
		string strID="";
		if(pwID != NULL)
		{
			strID.append( HttpUtil::UnicodeToMbcs(pwID));
		}
		XMLNode xDisplayNameNode=xOwnerNode.getChildNode(L"DisplayName");
		const wchar_t *pwDisplayName = xDisplayNameNode.getText();
		string strDisplayName="";
		if(pwDisplayName != NULL)
		{
			strDisplayName.append( HttpUtil::UnicodeToMbcs(pwDisplayName));
		}
		Owner owner;
		owner.displayName = strDisplayName;
		owner.ownerID = strID;
		OSSObjectSummary objSummary;
		objSummary.bucketName = strName;
		objSummary.eTag = strETag;
		objSummary.key = strKey;
		objSummary.lastModified = strLastModified;
		objSummary.size = size;
		objSummary.owner = owner;
		objSummary.storageClass = strStorageClass;
		objectSummaries.push_back(objSummary);
		i++;

	}
	XMLNode xCommonPrefixesNode=xNode.getChildNode(L"CommonPrefixes");
	if(!xCommonPrefixesNode.isEmpty())
	{
		int j = 0;
		while(1)
		{
			XMLNode xPrefixNode1=xCommonPrefixesNode.getChildNode(L"Prefix",&j);
			if(xPrefixNode1.isEmpty())
			{
				break;
			}
			const wchar_t *pwPrefix1 = xPrefixNode1.getText();
			string strPrefix1="";
			if(pwPrefix1 != NULL)
			{
				strPrefix1.append( HttpUtil::UnicodeToMbcs(pwPrefix1));
			}
			commonPrefixes.push_back(strPrefix1);
			j++;
		}
		
	}
}
}
