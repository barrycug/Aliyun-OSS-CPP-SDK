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
#include "OSSUtil.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "HttpUtil.h"
#include "StringUtil.h"
namespace OSS
{
OSSUtil::OSSUtil(void)
{
}

OSSUtil::~OSSUtil(void)
{
}
string OSSUtil::HttpMethod2String(HttpMethod httpMethod)
{
	string str="";
	switch (httpMethod)
	{
	case HttpMethod_GET:
		str="GET";
		break;
	case HttpMethod_POST:
		str="POST";
		break;
	case HttpMethod_HEAD:
		str="HEAD";
		break;
	case HttpMethod_PUT:
		str="PUT";
		break;
	case HttpMethod_DELETE:
		str="DELETE";
		break;
	default:
		break;
	}
	return str;
}

string OSSUtil::urlEncodeKey(string &s)
{
	string rtnString = "";
	if(!s.empty())
	{
		vector<string> strArray;
		StringUtil::split(s,'/',strArray);
		if(strArray.size() > 0)
		{
			string str = strArray[0];
			//×ª³Éutf8
			string strUtf8 = HttpUtil::MbcsToUtf8(str);
			rtnString+=HttpUtil::UrlEncode(strUtf8);
			
			for(int j=1; j <strArray.size() ;j++)
			{
				string str1 = strArray[j];
				string strUtf81 = HttpUtil::MbcsToUtf8(str1);
				rtnString+="/";
				rtnString+=HttpUtil::UrlEncode(strUtf81);
			
			}

		}
	}
	return rtnString;
}
string OSSUtil::makeResourcePath(string &bucketName, string &objname)
{
	string rtnString;
	if(!bucketName.empty())
	{
		rtnString+=bucketName;
		if(!objname.empty())
		{
			rtnString+="/";
			rtnString+=OSSUtil::urlEncodeKey(objname);
		}
	}
	return rtnString;
}
void OSSUtil::populateRequestMetadata(map<string,string> &header,ObjectMetadata &objectMetadata)
{
	bool isHaveContentType = false;
	map<string,string> metadata = objectMetadata.GetMetadata();
	map<string,string> userMetadata = objectMetadata.GetUserMetadata();
	map<string,string>::iterator iter;
	if(metadata.size() > 0)
	{
		for(iter = metadata.begin();iter != metadata.end();iter++)
		{
			string strKey = iter->first;
			if(strKey.compare("Content-Type") ==0)
			{
				isHaveContentType = true;
			}
			header.insert(map<string, string> :: value_type(iter->first,iter->second));
		}		
	}
	if(!isHaveContentType)
	{
		header.insert(map<string, string> :: value_type("Content-Type","application/octect-stream"));
	}
	if(userMetadata.size() > 0)
	{
		for(iter = userMetadata.begin();iter != userMetadata.end();iter++)
		{
			string strKey = iter->first;
			string strValue = iter->second;
			strValue = "x-oss-meta-"+strValue;
			header.insert(map<string, string> :: value_type(iter->first,strValue));
		}
	}
}
OSS_RESULTCODE OSSUtil:: codeFromString(string &strErrorCodeType)
{
	OSS_RESULTCODE rCode = OSS_RESULTCODE_INVALID;
	if (strErrorCodeType.compare("AccessDenied")==0) {
        rCode = OSS_RESULTCODE_ACCESS_DENIED;
    }else if (strErrorCodeType.compare("BucketAlreadyExists")==0) {
        rCode = OSS_RESULTCODE_BUCKES_ALREADY_EXISTS;
    }else if (strErrorCodeType.compare("BucketNotEmpty")==0) {
        rCode = OSS_RESULTCODE_BUCKETS_NOT_EMPTY;
    }else if (strErrorCodeType.compare("FileGroupTooLarge")==0) {
        rCode = OSS_RESULTCODE_FILE_GROUP_TOO_LARGE;
    }else if (strErrorCodeType.compare("FilePartStale")==0) {
        rCode = OSS_RESULTCODE_FILE_PART_STALE;
    }else if (strErrorCodeType.compare("InvalidArgument")==0) {
        rCode = OSS_RESULTCODE_INVALID_ARGUMENT;
    }else if (strErrorCodeType.compare("InvalidAccessKeyId")==0) {
        rCode = OSS_RESULTCODE_INVALID_ACCESS_KEY_ID;
    }else if (strErrorCodeType.compare("InvalidBucketName")==0) {
        rCode = OSS_RESULTCODE_INVALID_BUCKET_NAME;
    }else if (strErrorCodeType.compare("InvalidObjectName")==0) {
        rCode = OSS_RESULTCODE_INVALID_OBJECT_NAME;
    }else if (strErrorCodeType.compare("InvalidPart")==0) {
        rCode = OSS_RESULTCODE_INVALID_PART;
    }else if (strErrorCodeType.compare("InvalidPartOrder")==0) {
        rCode = OSS_RESULTCODE_INVALID_PART_ORDER;
    }else if (strErrorCodeType.compare("InternalError")==0) {
        rCode = OSS_RESULTCODE_INTERNAL_ERROR;
    }else if (strErrorCodeType.compare("MissingContentLength")==0) {
        rCode = OSS_RESULTCODE_MISSING_CONTENT_LENGTH;
    }else if (strErrorCodeType.compare("NoSuchBucket")==0) {
        rCode = OSS_RESULTCODE_NO_SUCH_BUCKET;
    }else if (strErrorCodeType.compare("NoSuchKey")==0) {
        rCode = OSS_RESULTCODE_NO_SUCH_KEY;
    }else if (strErrorCodeType.compare("NotImplemented")==0) {
        rCode = OSS_RESULTCODE_NOT_IMPLEMENTED;
    }else if (strErrorCodeType.compare("PreconditionFailed")==0) {
        rCode = OSS_RESULTCODE_PRECONDITION_FAILED;
    }else if (strErrorCodeType.compare("RequestTimeTooSkewed")==0) {
        rCode = OSS_RESULTCODE_REQUEST_TIME_TOO_SKEWED;
    }else if (strErrorCodeType.compare("RequestTimeout")==0) {
        rCode = OSS_RESULTCODE_REQUEST_TIMEOUT;
    }else if (strErrorCodeType.compare("SignatureDoesNotMatch")==0) {
        rCode = OSS_RESULTCODE_SIGNATURE_DOES_NOT_MATCH;
    }else if (strErrorCodeType.compare("TooManyBuckets")==0) {
        rCode = OSS_RESULTCODE_TOO_MANY_BUCKETS;
    }
    return rCode;
}
void OSSUtil::GetResponseHeaderParameters(ResponseHeaderOverrides &responseHeaderOverrides,map<string,string> &headers)
{
	if(!responseHeaderOverrides.cacheControl.empty())
	{
		headers.insert(map<string,string>::value_type("response-cache-control",responseHeaderOverrides.cacheControl));
	}
	if(!responseHeaderOverrides.contentDisposition.empty())
	{
		headers.insert(map<string,string>::value_type("response-content-disposition",responseHeaderOverrides.contentDisposition));
	}
	if(!responseHeaderOverrides.contentEncoding.empty())
	{
		headers.insert(map<string,string>::value_type("response-content-encoding",responseHeaderOverrides.contentEncoding));
	}
	if(!responseHeaderOverrides.contentLangauge.empty())
	{
		headers.insert(map<string,string>::value_type("response-content-language",responseHeaderOverrides.contentLangauge));
	}
	if(!responseHeaderOverrides.contentType.empty())
	{
		headers.insert(map<string,string>::value_type("response-content-type",responseHeaderOverrides.contentType));
	}
	if(!responseHeaderOverrides.expires.empty())
	{
		headers.insert(map<string,string>::value_type("response-expires",responseHeaderOverrides.expires));
	}
}
void OSSUtil::ParserObjectMetadata(map<string,string> &header,ObjectMetadata &objectMetadata)
{
	map<string,string>::iterator iter;
	for(iter = header.begin();iter != header.end();iter++)
	{
		string strKey = iter->first;
        string str;
		string strValue = iter->second;
		int pos = strKey.find("x-oss-meta-");
		if(pos >=0)
		{
			str = strKey.substr(pos+11,strKey.size()-11);
			objectMetadata.AddUserMetadata(str,strValue);
		}else if(strKey.compare("ETag")==0)
		{
			objectMetadata.AddHeader(strKey,StringUtil::trimQuote(strValue));
		}else
		{
			objectMetadata.AddHeader(strKey,strValue);
		}

	}

}
void OSSUtil::AddListHeader(map<string,string> &header,string key,vector<string> list)
{
	if (list.size() > 0 )
    {
        string str = ""; 

        int i = 1;
		for(int j = 0; j < list.size();j++)
		{
			if (i== 0) {
				str+=", ";
			}
			str+=list[j];
			i=0;
		}     
        header.insert(map<string, string> :: value_type(key,str));
 
    }

}
}
