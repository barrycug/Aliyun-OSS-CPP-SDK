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
#pragma warning(disable:4251)
#ifdef LIBOSS_EXPORTS
#define OSSDLL_API __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define OSSDLL_API __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif 
#pragma once
#include "ossoperation.h"
#include "CannedAccessControlList.h"
#include "ListObjectsRequest.h"
#include "Bucket.h"
#include "ObjectListing.h"
#include<string>
#include<vector>
#include "Buckets.h"
#include "OSSBucketOperationCallback.h"
using namespace std;
namespace OSS
{
/**
@class OSSBucketOperation
@brief Bucket对象操作类
*/
class OSSDLL_API OSSBucketOperation :
	public OSSOperation
{
public:
	OSSBucketOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client);
	~OSSBucketOperation(void);
public:
	OSS_RESULTCODE CreateBucket(string &bucketName,Bucket &bucket);
	OSS_RESULTCODE DeleteBucket(string &bucketName);
	OSS_RESULTCODE ListBuckets(Buckets &buckets);
	OSS_RESULTCODE SetBucketACL(string &bucketName,CannedAccessControlList &aclList);
	OSS_RESULTCODE GetBucketACL(string &bucketName,CannedAccessControlList &aclList);
	OSS_RESULTCODE IsBucketExist(string &bucketName,bool &isExist);
	OSS_RESULTCODE ListObjects(ListObjectsRequest & reuqest,ObjectListing &objectListing);

	bool CreateBucket_Async(string &bucketName);
	bool DeleteBucket_Async(string &bucketName);
	bool ListBuckets_Async();
	bool SetBucketACL_Async(string &bucketName,CannedAccessControlList &aclList);
	bool GetBucketACL_Async(string &bucketName);
	bool IsBucketExist_Async(string &bucketName);
	bool ListObjects_Async(ListObjectsRequest & reuqest);
private:
	ResponseMessage invoke(HttpMethod httpMethod,string &bucketName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo);
	bool invoke_Async(HttpMethod httpMethod,string &bucketName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo);
public:
	OSSBucketOperationCallback *delegate;
public:
	
	void serviceClientRequestFinished(DefaultServiceClient*defaultServiceClient,ResponseMessage &responseMessage);
	void serviceClientRequestFailed(DefaultServiceClient*defaultServiceClient, ResponseMessage &responseMessage);

};

}

