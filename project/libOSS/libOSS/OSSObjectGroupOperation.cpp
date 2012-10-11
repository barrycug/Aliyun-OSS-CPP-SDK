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
#include "OSSObjectGroupOperation.h"
#include "OSSApi.h"
#include <map>
#include <algorithm>
#include <vector>
#include "OSSError.h"
#include "OSSUtil.h"
#include "HttpUtil.h"

namespace OSS
{
OSSObjectGroupOperation::OSSObjectGroupOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client):OSSOperation(endpoint,serviceCredentials,client)
{
	delegate = NULL;
}


OSSObjectGroupOperation::~OSSObjectGroupOperation(void)
{
}
OSS_RESULTCODE OSSObjectGroupOperation::PostObjectGroup(PostObjectGroupRequest &postObjectGroupRequest,PostObjectGroupResult & result)
{	
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","PostObjectGroup"));

	if(postObjectGroupRequest.bucketName.empty() ||postObjectGroupRequest.objectGroupName.empty()
		||postObjectGroupRequest.objectGroupPartETags.size() <= 0 || postObjectGroupRequest.objectGroupPartETags.size() >1000)
	{
		return OSS_RESULTCODE_INVALID;
	}
	std::sort(postObjectGroupRequest.objectGroupPartETags.begin(), postObjectGroupRequest.objectGroupPartETags.end(),ObjectGroupPartETag::cmp);
	params.insert(map<string, string> :: value_type("group",""));
	string strXMLContent = MakePostObjectGroupXML(postObjectGroupRequest.objectGroupPartETags);

	string utf8XML =HttpUtil::MbcsToUtf8(strXMLContent);

	headers.insert(map<string, string> :: value_type("Content-Type","text/plain"));
	char * data =(char*) utf8XML.c_str();
	ResponseMessage rm =  invoke(HttpMethod_POST,postObjectGroupRequest.bucketName,postObjectGroupRequest.objectGroupName,headers,params,data,utf8XML.size(),userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		if(rm.getContent() != NULL)
		{
			strXML.append(rm.getContent());
			result.MakePostObjectGroupResult(strXML);
		}
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;

}
OSS_RESULTCODE OSSObjectGroupOperation::GetObjectGroupIndex(string &bucketName ,string &key,FetchObjectGroupIndexResult &result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetObjectGroupIndex"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	userInfo.insert(map<string, string> :: value_type("key",key));
	if(bucketName.empty() || key.empty())
	{
		return OSS_RESULTCODE_INVALID;
	}
	headers.insert(map<string, string> :: value_type("x-oss-file-group","NULL"));
	ResponseMessage rm =  invoke(HttpMethod_GET,bucketName,key,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		if(rm.getContent() != NULL)
		{
			strXML.append(rm.getContent());
			result.MakeFetchObjectGroupIndexResult(strXML);
		}
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
}
/**
 GetObjectGroup 没有实现，请使用 GetObject 方法
 @param bucketName string
 @param key string
 */
OSS_RESULTCODE OSSObjectGroupOperation::GetObjectGroup(string &bucketName ,string &key)
{
	return OSS_RESULTCODE_OK;
}
/**
 DeleteObjectGroup 没有实现，请使用 DeleteObject 方法
 @param bucketName string
 @param key string
 */
OSS_RESULTCODE OSSObjectGroupOperation::DeleteObjectGroup(string &bucketName ,string &key)
{
	return OSS_RESULTCODE_OK;
}
/**
 GetObjectGroupMetadata没有实现，请使用 GetObjectMetadata 方法
 @param bucketName string
 @param key string
 */
OSS_RESULTCODE OSSObjectGroupOperation::GetObjectGroupMetadata(string &bucketName ,string &key,ObjectMetadata &objectMetadata)
{
	return OSS_RESULTCODE_OK;
}
//异步调用
bool OSSObjectGroupOperation::PostObjectGroup_Async(PostObjectGroupRequest &postObjectGroupRequest)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","PostObjectGroup"));

	if(postObjectGroupRequest.bucketName.empty() ||postObjectGroupRequest.objectGroupName.empty()
		||postObjectGroupRequest.objectGroupPartETags.size() <= 0 || postObjectGroupRequest.objectGroupPartETags.size() >1000)
	{
		return false;
	}
	std::sort(postObjectGroupRequest.objectGroupPartETags.begin(), postObjectGroupRequest.objectGroupPartETags.end(),ObjectGroupPartETag::cmp);
	params.insert(map<string, string> :: value_type("group",""));
	string strXMLContent = MakePostObjectGroupXML(postObjectGroupRequest.objectGroupPartETags);

	string utf8XML =HttpUtil::MbcsToUtf8(strXMLContent);

	headers.insert(map<string, string> :: value_type("Content-Type","text/plain"));
	char * data =(char*) utf8XML.c_str();
	return invoke_Async(HttpMethod_POST,postObjectGroupRequest.bucketName,postObjectGroupRequest.objectGroupName,headers,params,data,utf8XML.size(),userInfo);
	
}
bool OSSObjectGroupOperation::GetObjectGroupIndex_Async(string &bucketName ,string &key)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetObjectGroupIndex"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	userInfo.insert(map<string, string> :: value_type("key",key));
	if(bucketName.empty() || key.empty())
	{
		return false;
	}
	headers.insert(map<string, string> :: value_type("x-oss-file-group","NULL"));
	return invoke_Async(HttpMethod_GET,bucketName,key,headers,params,NULL,0,userInfo);
}
/**
 GetObjectGroup_Async 没有实现，请使用 GetObject_Async 方法
 @param bucketName string in
 @param key string in 
 */
bool OSSObjectGroupOperation::GetObjectGroup_Async(string &bucketName ,string &key)
{
	return false;
}
/**
 DeleteObjectGroup_Async 没有实现，请使用 DeleteObject_Async 方法
 @param bucketName string in
 @param key string in
 */
bool OSSObjectGroupOperation::DeleteObjectGroup_Async(string &bucketName ,string &key)
{
	return false;
}

/**
 GetObjectGroupMetadata_Async没有实现，请使用 GetObjectMetadata_Async 方法
 @param bucketName string in
 @param key string in
 */
bool OSSObjectGroupOperation::GetObjectGroupMetadata_Async(string &bucketName,string &key)
{
	return false;
}
ResponseMessage OSSObjectGroupOperation::invoke(HttpMethod httpMethod,string &bucketName,string &objName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo)
{
	ResponseMessage rm = request(httpMethod,bucketName,objName,headers,params,content,contentLength,userInfo);
	return rm;
}
bool OSSObjectGroupOperation::invoke_Async(HttpMethod httpMethod,string &bucketName,string &objName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo)
{
	return request_Async(httpMethod,bucketName,objName,headers,params,content,contentLength,userInfo);
}
void OSSObjectGroupOperation::serviceClientRequestFinished(DefaultServiceClient*defaultServiceClient,ResponseMessage &responseMessage)
{
	if(delegate != NULL)
	{
		map<string,string> userInfo = responseMessage.userInfo;
		map<string,string>::iterator iter ;
		iter = userInfo.find("method");
		string method = "";
		if(iter != userInfo.end())
		{
			method = iter->second;
		}
		if (responseMessage.isSuccessful())
		{
			if(method.compare("PostObjectGroup")==0)
			{
				string strXML ;
				PostObjectGroupResult result;
				if(responseMessage.getContent() != NULL)
				{
					strXML.append(responseMessage.getContent());
					result.MakePostObjectGroupResult(strXML);
				}
				delegate->OnPostObjectGroupComplete(this,result);
			} 
			else if(method.compare("GetObjectGroupIndex")==0)
			{
				string strXML ;
				FetchObjectGroupIndexResult result;
				if(responseMessage.getContent() != NULL)
				{
					strXML.append(responseMessage.getContent());
					result.MakeFetchObjectGroupIndexResult(strXML);
					delegate->OnGetObjectGroupIndexComplete(this,result);
				}
			} 
			
		}
		else
		{
			OSS_RESULTCODE rCode;
			string strError(responseMessage.getContent());
			OSSError error(strError);
			rCode = OSSUtil::codeFromString(error.code);
			//PostObjectGroup
			if(method.compare("PostObjectGroup")==0)
			{
				delegate->OnPostObjectGroupFailed(this,rCode);
			} 
			//GetObjectGroupIndex
			else if(method.compare("GetObjectGroupIndex")==0)
			{
				delegate->OnGetObjectGroupIndexFailed(this,rCode);
			} 
			
		}
	}
}
void OSSObjectGroupOperation::serviceClientRequestFailed(DefaultServiceClient*defaultServiceClient, ResponseMessage &responseMessage)
{
	OSSError error;
	error.message = "network error";
	if(delegate != NULL)
	{
		delegate->OnNetworkFailed(this,OSS_RESULTCODE_INVALID);
	}
}
string OSSObjectGroupOperation::MakePostObjectGroupXML(vector<ObjectGroupPartETag> &objectGroupPartETags)
{
    string rtnString="";
    rtnString+="<CreateFileGroup>";
	for(int i=0;i<objectGroupPartETags.size();i++)
	{
		ObjectGroupPartETag  partEtag = objectGroupPartETags[i];
		rtnString+="<Part>";
        rtnString+="<PartNumber>";
		char cPartNumber[64];
		sprintf(cPartNumber,"%ld",partEtag.partNumber);
        rtnString+=cPartNumber;
        rtnString+="</PartNumber>";
        rtnString+="<PartName>";
        rtnString+=partEtag.partName;
        rtnString+="</PartName>";
        rtnString+="<ETag>";
        rtnString+=partEtag.eTag;
        rtnString+="</ETag>";        
        rtnString+="</Part>";
	}
    
    rtnString+="</CreateFileGroup>";
    return rtnString;
}
}
