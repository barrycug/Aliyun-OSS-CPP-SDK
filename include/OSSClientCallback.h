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
class OSSClient;
class Bucket;
class Buckets;
class CannedAccessControlList;
class ObjectListing;

class ObjectMetadata;
class PutObjectResult;
class OSSObject;
class CopyObjectResult;
class DeleteObjectsResult;

class PostObjectGroupResult;
class FetchObjectGroupIndexResult;

class UploadPartResult;
class PartListing;
class MultipartUploadListing;
class InitiateMultipartUploadResult;
class CompleteMultipartUploadResult;

/**
@class OSSClientCallback
@brief 抽象基类，OSSClient对象操作相关回调函数定义
*/
class OSSDLL_API OSSClientCallback
{
	//bucket op
public:
	virtual  void OnCreateBucketComplete(OSSClient *client,Bucket &bucket) = 0;
	virtual  void OnCreateBucketFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnDeleteBucketComplete(OSSClient *client,string &bucketName) = 0;
	virtual  void OnDeleteBucketFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnListBucketsComplete(OSSClient *client,Buckets &buckets) = 0;
	virtual  void OnListBucketsFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnSetBucketACLComplete(OSSClient *client) = 0;
	virtual  void OnSetBucketACLFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnGetBucketACLComplete(OSSClient *client,CannedAccessControlList &aclList) = 0;
	virtual  void OnGetBucketACLFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnIsBucketExistComplete(OSSClient *client,bool &isExist) = 0;
	virtual  void OnIsBucketExistFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnListObjectsComplete(OSSClient *client,ObjectListing &objectListing) = 0;
	virtual  void OnListObjectsFailed(OSSClient *client,OSS_RESULTCODE code) = 0;
	//Object Op
	virtual  void OnPutObjectComplete(OSSClient *client,PutObjectResult &result) = 0;
	virtual  void OnPutObjectFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnFetchObjectComplete(OSSClient *client,OSSObject &object) = 0;
	virtual  void OnFetchObjectFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnFetchObjectToFileComplete(OSSClient *client,string &fileName) = 0;
	virtual  void OnFetchObjectToFileFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnGetObjectMetadataComplete(OSSClient *client,ObjectMetadata &objectMetadata) = 0;
	virtual  void OnGetObjectMetadataFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnCopyObjectComplete(OSSClient *client,CopyObjectResult &result) = 0;
	virtual  void OnCopyObjectFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnDeleteObjectComplete(OSSClient *client) = 0;
	virtual  void OnDeleteObjectFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnDeleteMultipleObjectsComplete(OSSClient *client,DeleteObjectsResult &result) = 0;
	virtual  void OnDeleteMultipleObjectsFailed(OSSClient *client,OSS_RESULTCODE code) = 0;
	virtual  void OnPostObjectGroupComplete(OSSClient *client,PostObjectGroupResult &result) = 0;
	virtual  void OnPostObjectGroupFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnGetObjectGroupIndexComplete(OSSClient *client,FetchObjectGroupIndexResult &result) = 0;
	virtual  void OnGetObjectGroupIndexFailed(OSSClient *client,OSS_RESULTCODE code) = 0;
	//multipart Op
	virtual  void OnUploadPartComplete(OSSClient *client,UploadPartResult &result) = 0;
	virtual  void OnUploadPartFailed(OSSClient *client,OSS_RESULTCODE code) = 0;
	
	virtual  void OnListPartsComplete(OSSClient *client,PartListing &result) = 0;
	virtual  void OnListPartsFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnListMultipartUploadsComplete(OSSClient *client,MultipartUploadListing &result) = 0;
	virtual  void OnListMultipartUploadsFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnInitiateMultipartUploadComplete(OSSClient *client,InitiateMultipartUploadResult &result) = 0;
	virtual  void OnInitiateMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnCompleteMultipartUploadComplete(OSSClient *client,CompleteMultipartUploadResult &result) = 0;
	virtual  void OnCompleteMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code) = 0;

	virtual  void OnAbortMultipartUploadComplete(OSSClient *client,string &puloadId) = 0;
	virtual  void OnAbortMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code) = 0;
	virtual  void OnNetworkFailed(OSSClient *client,OSS_RESULTCODE code) = 0;
};
}