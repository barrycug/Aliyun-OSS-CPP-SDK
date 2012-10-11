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
#include "OSSObjectOperation.h"
#include "OSSApi.h"
#include <map>
#include "OSSError.h"
#include "OSSUtil.h"
#include "StringUtil.h"
#include "base64.h"
#include "md5.h"
#include "HttpUtil.h"
namespace OSS
{
OSSObjectOperation::OSSObjectOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client):OSSOperation(endpoint,serviceCredentials,client)
{
	delegate = NULL;
}


OSSObjectOperation::~OSSObjectOperation(void)
{
}
OSS_RESULTCODE OSSObjectOperation::PutObject(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata,PutObjectResult &result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","PutObject"));
	OSSUtil::populateRequestMetadata(headers,objectMetadata);
	ResponseMessage rm ;
	rm =  invoke(HttpMethod_PUT,bucketName,key,headers,params,data,dataLength,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		map<string,string> headers =rm.getHeaders();
		map<string,string>::iterator iter = headers.find("ETag");
		string eTag="";
		if(iter != headers.end())
		{
			eTag = iter->second;
		}
		eTag = StringUtil::trimQuote(eTag);
		result.eTag = eTag;
	
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
}
OSS_RESULTCODE OSSObjectOperation::FetchObject(string &bucketName,string &key,OSSObject & object)
{
	FetchObjectRequest request;
	request.bucketName = bucketName;
	request.key = key;
	return FetchObject(request,object);
}
OSS_RESULTCODE OSSObjectOperation::FetchObject(FetchObjectRequest &request,OSSObject & object)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetObject"));
	userInfo.insert(map<string, string> :: value_type("bucketName",request.bucketName));
	userInfo.insert(map<string, string> :: value_type("key",request.key));
	if(request.bucketName.empty() || request.key.empty())
	{
		return OSS_RESULTCODE_INVALID;
	}
	if (request.min >=0&& request.min < request.max )
    {
		char cMin[64];
		char cMax[64];
		sprintf_s(cMin,"%ld",request.min);
		sprintf_s(cMax,"%ld",request.max);
		string strRange = "bytes=";
		strRange += cMin;
		strRange += "-";
		strRange += cMax;
		headers.insert(map<string,string>::value_type("Range",strRange));
    }
	if(!request.modifiedSinceConstraint.empty())
	{
		headers.insert(map<string,string>::value_type("If-Modified-Since",request.modifiedSinceConstraint));
	}
   if(!request.unmodifiedSinceConstraint.empty())
	{
		headers.insert(map<string,string>::value_type("If-Unmodified-Since",request.unmodifiedSinceConstraint));
	}
   if(request.matchingETagConstraints.size() > 0)
	{
		headers.insert(map<string,string>::value_type("If-Match",joinETag(request.matchingETagConstraints)));
	}
   if(request.nonmatchingEtagConstraints.size() > 0)
	{
		headers.insert(map<string,string>::value_type("If-None-Match",joinETag(request.nonmatchingEtagConstraints)));
	}
	OSSUtil::GetResponseHeaderParameters(request.responseHeaders,params);

	ResponseMessage rm =  invoke(HttpMethod_GET,request.bucketName,request.key,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		if(rm.getContent()!= NULL)
		{
			object.SetData(rm.getContent(),rm.getContentLength());
		}
		object.bucketName = request.bucketName;
		object.key = request.key;
		ObjectMetadata objMetadata;
		OSSUtil::ParserObjectMetadata(rm.getHeaders(),objMetadata);
		object.metadata = objMetadata;
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
}

OSS_RESULTCODE OSSObjectOperation::FetchObject(string &bucketName,string &key,string &filePath)
{
	FetchObjectRequest request;
	request.bucketName = bucketName;
	request.key = key;
	return FetchObject(request,filePath);
}
OSS_RESULTCODE OSSObjectOperation::FetchObject(FetchObjectRequest &request,string &filePath)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetObjectToFile"));
	userInfo.insert(map<string, string> :: value_type("bucketName",request.bucketName));
	userInfo.insert(map<string, string> :: value_type("key",request.key));
	userInfo.insert(map<string, string> :: value_type("path",filePath));
	if(request.bucketName.empty() || request.key.empty())
	{
		return OSS_RESULTCODE_INVALID;
	}
	if (request.min >=0&& request.min < request.max )
    {
		char cMin[64];
		char cMax[64];
		sprintf_s(cMin,"%ld",request.min);
		sprintf_s(cMax,"%ld",request.max);
		string strRange = "bytes=";
		strRange += cMin;
		strRange += "-";
		strRange += cMax;
		headers.insert(map<string,string>::value_type("Range",strRange));
    }
	if(!request.modifiedSinceConstraint.empty())
	{
		headers.insert(map<string,string>::value_type("If-Modified-Since",request.modifiedSinceConstraint));
	}
	else
   {
	   headers.insert(map<string,string>::value_type("If-Modified-Since",""));
   }
   if(!request.unmodifiedSinceConstraint.empty())
	{
		headers.insert(map<string,string>::value_type("If-Unmodified-Since",request.unmodifiedSinceConstraint));
	}
   else
   {
	   headers.insert(map<string,string>::value_type("If-Unmodified-Since",""));
   }
   if(request.matchingETagConstraints.size() > 0)
	{
		headers.insert(map<string,string>::value_type("If-Match",joinETag(request.matchingETagConstraints)));
	}
   if(request.nonmatchingEtagConstraints.size() > 0)
	{
		headers.insert(map<string,string>::value_type("If-None-Match",joinETag(request.nonmatchingEtagConstraints)));
	}
   OSSUtil::GetResponseHeaderParameters(request.responseHeaders,params);

   ResponseMessage rm =  invoke(HttpMethod_GET,request.bucketName,request.key,headers,params,NULL,0,userInfo);
   OSS_RESULTCODE rCode;
   if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		/*
		if(rm.getContent()!= NULL)
		{
			object.SetData(rm.getContent(),rm.getContentLength());
		}
		object.bucketName = request.bucketName;
		object.key = request.key;
		ObjectMetadata objMetadata;
		OSSUtil::ParserObjectMetadata(rm.getHeaders(),objMetadata);
		object.metadata = objMetadata;
		*/
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
}
OSS_RESULTCODE OSSObjectOperation::GetObjectMetadata(string &bucketName,string &key,ObjectMetadata &objectMetadata)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetObjectMetadata"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	userInfo.insert(map<string, string> :: value_type("key",key));
	if(bucketName.empty() || key.empty())
	{
		return OSS_RESULTCODE_INVALID;
	}
	ResponseMessage rm =  invoke(HttpMethod_HEAD,bucketName,key,headers,params,NULL,0,userInfo);
   OSS_RESULTCODE rCode;
   if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		OSSUtil::ParserObjectMetadata(rm.getHeaders(),objectMetadata);
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;

}
OSS_RESULTCODE OSSObjectOperation::CopyObject(CopyObjectRequest & request,CopyObjectResult &result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","CopyObject"));
	if(request.sourceBucketName.empty() || request.sourceKey.empty() 
		||request.destinationBucketName.empty() ||request.destinationkey.empty())
	{
		return OSS_RESULTCODE_INVALID;
	}
	populateCopyObjectHeaders(request,headers);
	map<string,string>::iterator iter = headers.find("Content-Length");
	if(iter != headers.end())
	{
		headers.erase(iter);
	}
	ResponseMessage rm =  invoke(HttpMethod_PUT,request.destinationBucketName,request.destinationkey,headers,params,NULL,0,userInfo);
   OSS_RESULTCODE rCode;
   if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		if(rm.getContent() != NULL)
		{
			strXML.append(rm.getContent());
			result.MakeCopyObjectResult(strXML);
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
void OSSObjectOperation::populateCopyObjectHeaders(CopyObjectRequest&copyObjectRequest ,map<string,string>&headers)
{
    string str;
	str+="/";
	str+= copyObjectRequest.sourceBucketName;
	str+="/";
	str+= copyObjectRequest.sourceKey;
	headers.insert(map<string, string> :: value_type("x-oss-copy-source",str));
	if(!copyObjectRequest.modifiedSinceConstraint.empty())
	{
		headers.insert(map<string, string> :: value_type("x-oss-copy-source-if-modified-since",copyObjectRequest.modifiedSinceConstraint));
	}
	if(!copyObjectRequest.unmodifiedSinceConstraint.empty())
	{	
		headers.insert(map<string, string> :: value_type("x-oss-copy-source-if-unmodified-since",copyObjectRequest.unmodifiedSinceConstraint));
	}
	OSSUtil::AddListHeader(headers,"x-oss-copy-source-if-match",copyObjectRequest.matchingETagConstraints);
	OSSUtil::AddListHeader(headers,"x-oss-copy-source-if-none-match",copyObjectRequest.nonmatchingETagConstraints);
	if(copyObjectRequest.pNewObjectMetadata != NULL)
	{
		headers.insert(map<string, string> :: value_type("x-oss-metadata-directiv","REPLACE"));
		OSSUtil::populateRequestMetadata(headers,*copyObjectRequest.pNewObjectMetadata);
	}
    
}
OSS_RESULTCODE OSSObjectOperation::DeleteObject(string &bucketName,string &key)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","DeleteObject"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	userInfo.insert(map<string, string> :: value_type("key",key));
	if(bucketName.empty() || key.empty())
	{
		return OSS_RESULTCODE_INVALID;
	}
	ResponseMessage rm =  invoke(HttpMethod_DELETE,bucketName,key,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;

}
OSS_RESULTCODE OSSObjectOperation::DeleteMultipleObjects(string &bucketName,vector<string> &objNames, bool isQuiet,DeleteObjectsResult & result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","DeleteMultipleObjects"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	if(bucketName.empty() || (objNames.size() ==0))
	{
		return OSS_RESULTCODE_INVALID;
	}
	params.insert(map<string, string> :: value_type("delete",""));
	string strXMLContent = makeDeleteObjectsXMLContent(objNames,isQuiet);
	string utf8XML =HttpUtil::MbcsToUtf8(strXMLContent);
	md5_context content;
	md5_starts(&content);
	md5_update(&content,(unsigned char*)utf8XML.c_str(),utf8XML.size() );
	uint8 digest[16];
    md5_finish( &content, digest );
	string strXMLContentMd5;
	strXMLContentMd5.append((const char *)digest);
	string base64String =base64_encode((const unsigned char*)strXMLContentMd5.c_str(),strXMLContentMd5.size());
	headers.insert(map<string, string> :: value_type("Content-MD5",base64String));
	char * data =(char*) utf8XML.c_str();
	string key="";
	ResponseMessage rm =  invoke(HttpMethod_POST,bucketName,key,headers,params,data,utf8XML.size(),userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		if(rm.getContent() != NULL)
		{
			strXML.append(rm.getContent());
			result.MakeDeleteObjectsResult(strXML);
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
 

bool OSSObjectOperation::PutObject_Async(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	if(bucketName.empty() || key.empty())
	{
		return false;
	}
	userInfo.insert(map<string, string> :: value_type("method","PutObject"));
	OSSUtil::populateRequestMetadata(headers,objectMetadata);
	return invoke_Async(HttpMethod_PUT,bucketName,key,headers,params,data,dataLength,userInfo);
}

bool OSSObjectOperation::FetchObject_Async(string &bucketName,string &key)
{
	FetchObjectRequest request;
	request.bucketName = bucketName;
	request.key = key;
	return FetchObject_Async(request);
}
bool OSSObjectOperation::FetchObject_Async(FetchObjectRequest &request)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetObject"));
	userInfo.insert(map<string, string> :: value_type("bucketName",request.bucketName));
	userInfo.insert(map<string, string> :: value_type("key",request.key));
	if(request.bucketName.empty() || request.key.empty())
	{
		return false;
	}
	if (request.min >=0&& request.min < request.max )
    {
		char cMin[64];
		char cMax[64];
		sprintf_s(cMin,"%ld",request.min);
		sprintf_s(cMax,"%ld",request.max);
		string strRange = "bytes=";
		strRange += cMin;
		strRange += "-";
		strRange += cMax;
		headers.insert(map<string,string>::value_type("Range",strRange));
    }
	if(!request.modifiedSinceConstraint.empty())
	{
		headers.insert(map<string,string>::value_type("If-Modified-Since",request.modifiedSinceConstraint));
	}
   if(!request.unmodifiedSinceConstraint.empty())
	{
		headers.insert(map<string,string>::value_type("If-Unmodified-Since",request.unmodifiedSinceConstraint));
	}
   if(request.matchingETagConstraints.size() > 0)
	{
		headers.insert(map<string,string>::value_type("If-Match",joinETag(request.matchingETagConstraints)));
	}
   if(request.nonmatchingEtagConstraints.size() > 0)
	{
		headers.insert(map<string,string>::value_type("If-None-Match",joinETag(request.nonmatchingEtagConstraints)));
	}
	OSSUtil::GetResponseHeaderParameters(request.responseHeaders,params);

	return invoke_Async(HttpMethod_GET,request.bucketName,request.key,headers,params,NULL,0,userInfo);

}
//大文件请使用该方法
bool OSSObjectOperation::FetchObject_Async(string &bucketName,string &key,string &filePath)
{
	FetchObjectRequest request;
	request.bucketName = bucketName;
	request.key = key;
	return FetchObject_Async(request,filePath);
}
bool OSSObjectOperation::FetchObject_Async(FetchObjectRequest &request,string &filePath)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetObjectToFile"));
	userInfo.insert(map<string, string> :: value_type("bucketName",request.bucketName));
	userInfo.insert(map<string, string> :: value_type("key",request.key));
	userInfo.insert(map<string, string> :: value_type("path",filePath));
	if(request.bucketName.empty() || request.key.empty())
	{
		return false;
	}
	if (request.min >=0&& request.min < request.max )
    {
		char cMin[64];
		char cMax[64];
		sprintf_s(cMin,"%ld",request.min);
		sprintf_s(cMax,"%ld",request.max);
		string strRange = "bytes=";
		strRange += cMin;
		strRange += "-";
		strRange += cMax;
		headers.insert(map<string,string>::value_type("Range",strRange));
    }
	if(!request.modifiedSinceConstraint.empty())
	{
		headers.insert(map<string,string>::value_type("If-Modified-Since",request.modifiedSinceConstraint));
	}
	else
   {
	   headers.insert(map<string,string>::value_type("If-Modified-Since",""));
   }
   if(!request.unmodifiedSinceConstraint.empty())
	{
		headers.insert(map<string,string>::value_type("If-Unmodified-Since",request.unmodifiedSinceConstraint));
	}
   else
   {
	   headers.insert(map<string,string>::value_type("If-Unmodified-Since",""));
   }
   if(request.matchingETagConstraints.size() > 0)
	{
		headers.insert(map<string,string>::value_type("If-Match",joinETag(request.matchingETagConstraints)));
	}
   if(request.nonmatchingEtagConstraints.size() > 0)
	{
		headers.insert(map<string,string>::value_type("If-None-Match",joinETag(request.nonmatchingEtagConstraints)));
	}
   OSSUtil::GetResponseHeaderParameters(request.responseHeaders,params);

   return invoke_Async(HttpMethod_GET,request.bucketName,request.key,headers,params,NULL,0,userInfo);

}
bool OSSObjectOperation::GetObjectMetadata_Async(string &bucketName,string &key)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetObjectMetadata"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	userInfo.insert(map<string, string> :: value_type("key",key));
	if(bucketName.empty() || key.empty())
	{
		return false;
	}
	return invoke_Async(HttpMethod_HEAD,bucketName,key,headers,params,NULL,0,userInfo);
}
bool OSSObjectOperation::CopyObject_Async(CopyObjectRequest & request)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","CopyObject"));
	if(request.sourceBucketName.empty() || request.sourceKey.empty() 
		||request.destinationBucketName.empty() ||request.destinationkey.empty())
	{
		return false;
	}
	populateCopyObjectHeaders(request,headers);
	map<string,string>::iterator iter = headers.find("Content-Length");
	if(iter != headers.end())
	{
		headers.erase(iter);
	}
	return invoke_Async(HttpMethod_PUT,request.destinationBucketName,request.destinationkey,headers,params,NULL,0,userInfo);
  
}
bool OSSObjectOperation::DeleteObject_Async(string &bucketName,string &key)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","DeleteObject"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	userInfo.insert(map<string, string> :: value_type("key",key));
	if(bucketName.empty() || key.empty())
	{
		return false;
	}
	return invoke_Async(HttpMethod_DELETE,bucketName,key,headers,params,NULL,0,userInfo);
}
bool OSSObjectOperation::DeleteMultipleObjects_Async(string &bucketName,vector<string> &objNames, bool isQuiet)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","DeleteMultipleObjects"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	if(bucketName.empty() || (objNames.size() ==0))
	{
		return false;
	}
	params.insert(map<string, string> :: value_type("delete",""));
	string strXMLContent = makeDeleteObjectsXMLContent(objNames,isQuiet);
	string utf8XML =HttpUtil::MbcsToUtf8(strXMLContent);
	md5_context content;
	md5_starts(&content);
	md5_update(&content,(unsigned char*)utf8XML.c_str(),utf8XML.size() );
	uint8 digest[16];
    md5_finish( &content, digest );
	string strXMLContentMd5;
	strXMLContentMd5.append((const char *)digest);
	string base64String =base64_encode((const unsigned char*)strXMLContentMd5.c_str(),strXMLContentMd5.size());
	headers.insert(map<string, string> :: value_type("Content-MD5",base64String));
	char * data =(char*) utf8XML.c_str();
	string key="";
	return invoke_Async(HttpMethod_POST,bucketName,key,headers,params,data,utf8XML.size(),userInfo);
}
ResponseMessage OSSObjectOperation::invoke(HttpMethod httpMethod,string &bucketName,string &objectName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo)
{
	return request(httpMethod,bucketName,objectName,headers,params,content,contentLength,userInfo);
}
bool OSSObjectOperation::invoke_Async(HttpMethod httpMethod,string &bucketName,string &objectName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo)
{
	return request_Async(httpMethod,bucketName,objectName,headers,params,content,contentLength,userInfo);
}
void OSSObjectOperation::serviceClientRequestFinished(DefaultServiceClient*defaultServiceClient,ResponseMessage &responseMessage)
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
			if(method.compare("PutObject")==0)
			{
				map<string,string> headers =responseMessage.getHeaders();
				map<string,string>::iterator iter = headers.find("ETag");
				string eTag="";
				if(iter != headers.end())
				{
					eTag = iter->second;
				}
				eTag = StringUtil::trimQuote(eTag);
				PutObjectResult result;
				result.eTag = eTag;
				delegate->OnPutObjectComplete(this,result);
			} 
			//GetObject
			else if(method.compare("GetObject")==0)
			{
				OSSObject object;
				if(responseMessage.getContent()!= NULL)
				{
					object.SetData(responseMessage.getContent(),responseMessage.getContentLength());
				}
				object.bucketName = userInfo["bucketName"];
				object.key = userInfo["key"];
				ObjectMetadata objMetadata;
				OSSUtil::ParserObjectMetadata(responseMessage.getHeaders(),objMetadata);
				object.metadata = objMetadata;
				delegate->OnFetchObjectComplete(this,object);
			} 
			//GetObjectToFile
			else if(method.compare("GetObjectToFile")==0)
			{
				string filePath = userInfo["path"];
				delegate->OnFetchObjectToFileComplete(this,filePath);
			}
			//GetObjectMetadata
			else if(method.compare("GetObjectMetadata")==0)
			{
				ObjectMetadata objectMetadata;
				OSSUtil::ParserObjectMetadata(responseMessage.getHeaders(),objectMetadata);
				delegate->OnGetObjectMetadataComplete(this,objectMetadata);
			}
			//CopyObject
			else if(method.compare("CopyObject")==0)
			{
				string strXML ;
				CopyObjectResult result;
				if(responseMessage.getContent() != NULL)
				{
					strXML.append(responseMessage.getContent());
					result.MakeCopyObjectResult(strXML);
				}
				delegate->OnCopyObjectComplete(this,result);
			}
			//DeleteObject
			else if(method.compare("DeleteObject")==0)
			{
				delegate->OnDeleteObjectComplete(this);
			}
			//DeleteMultipleObjects
			else if(method.compare("DeleteMultipleObjects")==0)
			{
				string strXML ;
				DeleteObjectsResult result;
				if(responseMessage.getContent() != NULL)
				{
					strXML.append(responseMessage.getContent());
					result.MakeDeleteObjectsResult(strXML);
				}
				delegate->OnDeleteMultipleObjectsComplete(this,result);
			}
		}
		else
		{
			OSS_RESULTCODE rCode;
			string strError(responseMessage.getContent());
			OSSError error(strError);
			rCode = OSSUtil::codeFromString(error.code);
			//PutObject
			if(method.compare("PutObject")==0)
			{
				delegate->OnPutObjectFailed(this,rCode);
			} 
			//GetObject
			else if(method.compare("GetObject")==0)
			{
				delegate->OnFetchObjectFailed(this,rCode);
			} 
			//GetObjectToFile
			else if(method.compare("GetObjectToFile")==0)
			{
				delegate->OnFetchObjectToFileFailed(this,rCode);
			}
			//GetObjectMetadata
			else if(method.compare("GetObjectMetadata")==0)
			{
				delegate->OnGetObjectMetadataFailed(this,rCode);
			}
			//CopyObject
			else if(method.compare("CopyObject")==0)
			{
				delegate->OnCopyObjectFailed(this,rCode);
			}
			//DeleteObject
			else if(method.compare("DeleteObject")==0)
			{
				delegate->OnDeleteObjectFailed(this,rCode);
			}
			//DeleteMultipleObjects
			else if(method.compare("DeleteMultipleObjects")==0)
			{
				delegate->OnDeleteMultipleObjectsFailed(this,rCode);
			}
		}
	}
}
void OSSObjectOperation::serviceClientRequestFailed(DefaultServiceClient*defaultServiceClient, ResponseMessage &responseMessage)
{
	OSSError error;
	error.message = "network error";
	if(delegate != NULL)
	{
		delegate->OnNetworkFailed(this,OSS_RESULTCODE_INVALID);
	}
}
string OSSObjectOperation::joinETag(vector<string> &arrayList)
{
	string rtnString = "";
	int i = 1;
	for(int j = 0;j < arrayList.size();j++)
	{
		if(i==0)
		{
			rtnString+=",";
		}
		rtnString+=arrayList[i];
		i=0;
	}
	return rtnString;
}
string OSSObjectOperation::makeDeleteObjectsXMLContent(vector<string> &objectNames,bool isQuiet)
{
    string rtnString="";
	rtnString+="<Delete>";
	rtnString+="<Quiet>";
    if (isQuiet) {
		rtnString+="true";
    }
    else {
		rtnString+="false";
    }
    rtnString+="</Quiet>";
	for(int j=0;j<objectNames.size();j++)
	{
		rtnString+="<Object>";
		rtnString+="<Key>";
		rtnString+=objectNames[j];
		rtnString+="</Key>";
		rtnString+="</Object>";
		
	}
	rtnString+="</Delete>";
	return rtnString;
}
}
