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
#include "Buckets.h"
#include "xmlParser.h"
#include "HttpUtil.h"
namespace OSS
{
Buckets::Buckets(string & strXML)
{
	MakeBuckets(strXML);
}
Buckets::Buckets(void)
{
}

Buckets::~Buckets(void)
{
}
void Buckets::MakeBuckets(string & strXML)
{
	XMLNode xMainNode = XMLNode::parseString(HttpUtil::Utf8ToUnicode(strXML.c_str()));
	XMLNode xNode=xMainNode.getChildNode(L"ListAllMyBucketsResult");
	XMLNode xOwnerNode=xNode.getChildNode(L"Owner");
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
	XMLNode xBucketsNode=xNode.getChildNode(L"Buckets");
	int i = 0;
	while (1)
	{
		string strName="";
		string strCreateDate = "";
		XMLNode xBucketNode =xBucketsNode.getChildNode(L"Bucket",&i);
		if(xBucketNode.isEmpty())
		{
			break;
		}
		XMLNode xNameNode=xBucketNode.getChildNode(L"Name");
		const wchar_t *pwName = xNameNode.getText();
		if(pwName != NULL)
		{
			strName.append( HttpUtil::UnicodeToMbcs(pwName));
		}
		XMLNode xCreationDateNode=xBucketNode.getChildNode(L"CreationDate");
		const wchar_t *pwCreationDate = xCreationDateNode.getText();
		if(pwCreationDate != NULL)
		{
			strCreateDate.append( HttpUtil::UnicodeToMbcs(pwCreationDate));
		}
		Bucket bucket;
		bucket.createDate = strCreateDate;
		bucket.owner = owner;
		bucket.name = strName;
		bucketList.push_back(bucket);
		i++;
	}
}
}