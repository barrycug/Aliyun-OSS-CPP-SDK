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
#include "OSSBucketOperation.h"
#include "OSSApi.h"
#include <map>
#include "OSSError.h"
#include "OSSUtil.h"

namespace OSS
{
OSSBucketOperation::OSSBucketOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client):OSSOperation(endpoint,serviceCredentials,client)
{
	delegate = NULL;
}


OSSBucketOperation::~OSSBucketOperation(void)
{
}
bool OSSBucketOperation::CreateBucket_Async(string &bucketName)
{
	
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	if(bucketName.empty())
	{
		return false;
	}
	userInfo.insert(map<string, string> :: value_type("method","CreateBucket"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	return invoke_Async(HttpMethod_PUT,bucketName,headers,params,NULL,0,userInfo);
}

bool OSSBucketOperation::DeleteBucket_Async(string &bucketName)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	if(bucketName.empty())
	{
		return false;
	}
	userInfo.insert(map<string, string> :: value_type("method","DeleteBucket"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	return invoke_Async(HttpMethod_DELETE,bucketName,headers,params,NULL,0,userInfo);

}
bool OSSBucketOperation::ListBuckets_Async()
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	string bucketName;
	userInfo.insert(map<string, string> :: value_type("method","ListBuckets"));
	return invoke_Async(HttpMethod_GET,bucketName,headers,params,NULL,0,userInfo);

}
bool OSSBucketOperation::SetBucketACL_Async(string &bucketName,CannedAccessControlList &aclList)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	if(bucketName.empty())
	{
		return false;
	}
	userInfo.insert(map<string, string> :: value_type("method","SetBucketACL"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	userInfo.insert(map<string, string> :: value_type("acl",aclList.GetCannedAccessControlString()));
	headers.insert(map<string, string> :: value_type("x-oss-acl",aclList.GetCannedAccessControlString()));
	params.insert(map<string, string> :: value_type("acl",""));
	return invoke_Async(HttpMethod_PUT,bucketName,headers,params,NULL,0,userInfo);

}
bool OSSBucketOperation::GetBucketACL_Async(string &bucketName)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	if(bucketName.empty())
	{
		return false;
	}
	userInfo.insert(map<string, string> :: value_type("method","GetBucketACL"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	params.insert(map<string, string> :: value_type("acl",""));
	return invoke_Async(HttpMethod_GET,bucketName,headers,params,NULL,0,userInfo);
}
bool OSSBucketOperation::IsBucketExist_Async(string &bucketName)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","IsBucketExist"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	return invoke_Async(HttpMethod_GET,bucketName,headers,params,NULL,0,userInfo);
}
bool OSSBucketOperation::ListObjects_Async(ListObjectsRequest & reuqest)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	string bucketName;
	if(reuqest.bucketName.empty())
	{
		return false;
	}
	userInfo.insert(map<string, string> :: value_type("method","ListObjects"));
	if(!reuqest.prefix.empty())
	{
		params.insert(map<string, string> :: value_type("prefix",reuqest.prefix));
	}
	if(!reuqest.marker.empty())
	{
		params.insert(map<string, string> :: value_type("marker",reuqest.marker));
	}
	if(!reuqest.delimiter.empty())
	{
		params.insert(map<string, string> :: value_type("delimiter",reuqest.delimiter));
	}
	if(reuqest.maxKeys > 0 )
	{
		char temp[64];
		sprintf_s(temp,"%d",reuqest.maxKeys);
		string str(temp);
		params.insert(map<string, string> :: value_type("max-keys",str));
	}
	return invoke_Async(HttpMethod_GET,reuqest.bucketName,headers,params,NULL,0,userInfo);
}
OSS_RESULTCODE OSSBucketOperation::CreateBucket(string &bucketName,Bucket & bucket)
{
	OSS_RESULTCODE rCode;
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","CreateBucket"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	ResponseMessage rm=invoke(HttpMethod_PUT,bucketName,headers,params,NULL,0,userInfo);
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		bucket.name = bucketName;
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
}
OSS_RESULTCODE OSSBucketOperation::DeleteBucket(string &bucketName)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","DeleteBucket"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	ResponseMessage rm = invoke(HttpMethod_DELETE,bucketName,headers,params,NULL,0,userInfo);
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
OSS_RESULTCODE OSSBucketOperation::ListBuckets(Buckets &buckets)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	string bucketName;
	userInfo.insert(map<string, string> :: value_type("method","ListBuckets"));
	ResponseMessage rm  = invoke(HttpMethod_GET,bucketName,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		strXML.append(rm.getContent());
		buckets.MakeBuckets(strXML);
	}
	else
	{
		rCode = OSS_RESULTCODE_INVALID;
		if(rm.getContent() != NULL)
		{
			string strError(rm.getContent());
			OSSError error(strError);
			rCode = OSSUtil::codeFromString(error.code);
		}
	
	}
	return rCode;
}
OSS_RESULTCODE OSSBucketOperation::SetBucketACL(string &bucketName,CannedAccessControlList &aclList)
{

	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","SetBucketACL"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	userInfo.insert(map<string, string> :: value_type("acl",aclList.GetCannedAccessControlString()));
	headers.insert(map<string, string> :: value_type("x-oss-acl",aclList.GetCannedAccessControlString()));
	params.insert(map<string, string> :: value_type("acl",""));
	ResponseMessage rm =invoke(HttpMethod_PUT,bucketName,headers,params,NULL,0,userInfo);
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
OSS_RESULTCODE OSSBucketOperation::GetBucketACL(string &bucketName,CannedAccessControlList &aclList)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","GetBucketACL"));
	userInfo.insert(map<string, string> :: value_type("bucketName",bucketName));
	params.insert(map<string, string> :: value_type("acl",""));
	ResponseMessage rm  =invoke(HttpMethod_GET,bucketName,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		strXML.append(rm.getContent());
		aclList.MakeCannedAccessControlList(strXML);
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
}
OSS_RESULTCODE OSSBucketOperation::IsBucketExist(string &bucketName,bool &isExist)
{
	OSS_RESULTCODE rCode = OSS_RESULTCODE_INVALID;
	Buckets buckets;
	isExist = false;
	if(!bucketName.empty())
	{
		rCode = ListBuckets(buckets);
		if (rCode == OSS_RESULTCODE_OK)
		{
			for(int i=0;i<buckets.bucketList.size();i++)
			{
				Bucket bucket = buckets.bucketList[i];
				if(bucketName.compare(bucket.name) == 0)
				{
					isExist = true;
					break;
				}
			}
		}
	}
	return rCode;
}
OSS_RESULTCODE OSSBucketOperation::ListObjects(ListObjectsRequest & reuqest,ObjectListing &objectListing)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	string bucketName;
	userInfo.insert(map<string, string> :: value_type("method","ListObjects"));
	if(!reuqest.prefix.empty())
	{
		params.insert(map<string, string> :: value_type("prefix",reuqest.prefix));
	}
	if(!reuqest.marker.empty())
	{
		params.insert(map<string, string> :: value_type("marker",reuqest.marker));
	}
	if(!reuqest.delimiter.empty())
	{
		params.insert(map<string, string> :: value_type("delimiter",reuqest.delimiter));
	}
	if(reuqest.maxKeys > 0 )
	{
		char temp[64];
		sprintf_s(temp,"%d",reuqest.maxKeys);
		string str(temp);
		params.insert(map<string, string> :: value_type("max-keys",str));
	}
	ResponseMessage rm = invoke(HttpMethod_GET,reuqest.bucketName,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		strXML.append(rm.getContent());
		objectListing.MakeObjectListing(strXML);
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
}
ResponseMessage OSSBucketOperation::invoke(HttpMethod httpMethod,string &bucketName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo)
{
	ResponseMessage rm = request(httpMethod,bucketName,"",headers,params,content,contentLength,userInfo);
	return rm;
}
bool OSSBucketOperation::invoke_Async(HttpMethod httpMethod,string &bucketName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo)
{
	return request_Async(httpMethod,bucketName,"",headers,params,content,contentLength,userInfo);
}
void OSSBucketOperation::serviceClientRequestFinished(DefaultServiceClient*defaultServiceClient,ResponseMessage &responseMessage)
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
			//CreateBucket
			if(method.compare("CreateBucket")==0)
			{
				iter = userInfo.find("bucketName");
				string bucketName = "";
				if(iter != userInfo.end())
				{
					bucketName = iter->second;
				}
				Bucket bucket;
				bucket.name = bucketName;
				delegate->OnCreateBucketComplete(this,bucket);
			}
			//DeleteBucket
			else if(method.compare("DeleteBucket")==0)
			{
				iter = userInfo.find("bucketName");
				string bucketName = "";
				if(iter != userInfo.end())
				{
					bucketName = iter->second;
				}
				delegate->OnDeleteBucketComplete(this,bucketName);
			}
			//ListBuckets
			else if(method.compare("ListBuckets")==0)
			{
				string strXML ;
				strXML.append(responseMessage.getContent());
				Buckets buckets;
				buckets.MakeBuckets(strXML);
				delegate->OnListBucketsComplete(this,buckets);
			}
			//SetBucketACL
			else if(method.compare("SetBucketACL")==0)
			{
				delegate->OnSetBucketACLComplete(this);
			}
			//GetBucketACL
			else if(method.compare("GetBucketACL")==0)
			{
				string strXML ;
				strXML.append(responseMessage.getContent());
				CannedAccessControlList aclList;
				aclList.MakeCannedAccessControlList(strXML);
				delegate->OnGetBucketACLComplete(this,aclList);
			}
			//IsBucketExist
			else if(method.compare("IsBucketExist")==0)
			{
				iter = userInfo.find("bucketName");
				string bucketName = "";
				if(iter != userInfo.end())
				{
					bucketName = iter->second;
				}
				bool isExist = false;
				if(bucketName.empty())
				{
					isExist = false;
				}
				else
				{
					string strXML ;
					strXML.append(responseMessage.getContent());
					Buckets buckets;
					buckets.MakeBuckets(strXML);
					for(int j =0; j<buckets.bucketList.size();j++)
					{
						if(bucketName.compare(buckets.bucketList[j].name) == 0)
						{
							isExist = true;
							break;
						}
					}
				}
				delegate->OnIsBucketExistComplete(this,isExist);
			}
			//ListObjects
			else if(method.compare("ListObjects")==0)
			{
				string strXML ;
				strXML.append(responseMessage.getContent());
				ObjectListing objectListing;
				objectListing.MakeObjectListing(strXML);
				delegate->OnListObjectsComplete(this,objectListing);
			}
		}
		else
		{

			OSS_RESULTCODE rCode;
			string strError(responseMessage.getContent());
			OSSError error(strError);
			rCode = OSSUtil::codeFromString(error.code);
			if(method.compare("CreateBucket")==0)
			{
				delegate->OnCreateBucketFailed(this,rCode);
			} 
			else if(method.compare("DeleteBucket")==0)
			{
				delegate->OnDeleteBucketFailed(this,rCode);
			}
			//ListBuckets
			else if(method.compare("ListBuckets")==0)
			{
				delegate->OnListBucketsFailed(this,rCode);
			}
			//SetBucketACL
			else if(method.compare("SetBucketACL")==0)
			{
				delegate->OnSetBucketACLFailed(this,rCode);
			}
			//GetBucketACL
			else if(method.compare("GetBucketACL")==0)
			{
				delegate->OnGetBucketACLFailed(this,rCode);
			}
			//IsBucketExist
			else if(method.compare("IsBucketExist")==0)
			{
				delegate->OnIsBucketExistFailed(this,rCode);
			}
			//ListObjects
			else if(method.compare("ListObjects")==0)
			{
				delegate->OnListObjectsFailed(this,rCode);
			}

		}
	}
	
}
void OSSBucketOperation::serviceClientRequestFailed(DefaultServiceClient*defaultServiceClient, ResponseMessage &responseMessage)
{
	OSSError error;
	error.message = "network error";
	
	if(delegate != NULL)
	{
		delegate->OnNetworkFailed(this,OSS_RESULTCODE_INVALID);
	}
}
}