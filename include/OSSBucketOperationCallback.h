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

#include <string>
#include "OSSApi.h"
using namespace std;
namespace OSS
{
class OSSBucketOperation;
class Bucket;
class Buckets;
class CannedAccessControlList;
class ObjectListing;
/**
@class OSSBucketOperationCallback
@brief 抽象基类，Bucket对象操作相关回调函数定义
*/
class OSSDLL_API OSSBucketOperationCallback
{

public:

	virtual  void OnCreateBucketComplete(OSSBucketOperation * bucketOperation,Bucket &bucket) = 0;
	virtual  void OnCreateBucketFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnDeleteBucketComplete(OSSBucketOperation * bucketOperation,string &bucketName) = 0;
	virtual  void OnDeleteBucketFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnListBucketsComplete(OSSBucketOperation * bucketOperation,Buckets &buckets) = 0;
	virtual  void OnListBucketsFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnSetBucketACLComplete(OSSBucketOperation * bucketOperation) = 0;
	virtual  void OnSetBucketACLFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnGetBucketACLComplete(OSSBucketOperation * bucketOperation,CannedAccessControlList &aclList) = 0;
	virtual  void OnGetBucketACLFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnIsBucketExistComplete(OSSBucketOperation * bucketOperation,bool &isExist) = 0;
	virtual  void OnIsBucketExistFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnListObjectsComplete(OSSBucketOperation * bucketOperation,ObjectListing &objectListing) = 0;
	virtual  void OnListObjectsFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnNetworkFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code) = 0;
};
}