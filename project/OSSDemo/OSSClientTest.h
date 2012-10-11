#pragma once
#include "stdafx.h"
#include "OSSClient.h"
#include "OSSClientCallback.h"

using namespace OSS;

class OSSClientTest: OSS::OSSClientCallback
{
public:
	OSSClientTest(void);
	~OSSClientTest(void);
public:
	virtual  void OnCreateBucketComplete(OSSClient *client,Bucket &bucket);
	virtual  void OnCreateBucketFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnDeleteBucketComplete(OSSClient *client,string &bucketName);
	virtual  void OnDeleteBucketFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnListBucketsComplete(OSSClient *client,Buckets &buckets);
	virtual  void OnListBucketsFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnSetBucketACLComplete(OSSClient *client);
	virtual  void OnSetBucketACLFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnGetBucketACLComplete(OSSClient *client,CannedAccessControlList &aclList);
	virtual  void OnGetBucketACLFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnIsBucketExistComplete(OSSClient *client,bool &isExist);
	virtual  void OnIsBucketExistFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnListObjectsComplete(OSSClient *client,ObjectListing &objectListing);
	virtual  void OnListObjectsFailed(OSSClient *client,OSS_RESULTCODE code);
	//Object Op
	virtual  void OnPutObjectComplete(OSSClient *client,PutObjectResult &result);
	virtual  void OnPutObjectFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnFetchObjectComplete(OSSClient *client,OSSObject &object);
	virtual  void OnFetchObjectFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnFetchObjectToFileComplete(OSSClient *client,string &fileName);
	virtual  void OnFetchObjectToFileFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnGetObjectMetadataComplete(OSSClient *client,ObjectMetadata &objectMetadata);
	virtual  void OnGetObjectMetadataFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnCopyObjectComplete(OSSClient *client,CopyObjectResult &result);
	virtual  void OnCopyObjectFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnDeleteObjectComplete(OSSClient *client);
	virtual  void OnDeleteObjectFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnDeleteMultipleObjectsComplete(OSSClient *client,DeleteObjectsResult &result);
	virtual  void OnDeleteMultipleObjectsFailed(OSSClient *client,OSS_RESULTCODE code);
	virtual  void OnPostObjectGroupComplete(OSSClient *client,PostObjectGroupResult &result);
	virtual  void OnPostObjectGroupFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnGetObjectGroupIndexComplete(OSSClient *client,FetchObjectGroupIndexResult &result);
	virtual  void OnGetObjectGroupIndexFailed(OSSClient *client,OSS_RESULTCODE code);
	//multipart Op
	virtual  void OnUploadPartComplete(OSSClient *client,UploadPartResult &result);
	virtual  void OnUploadPartFailed(OSSClient *client,OSS_RESULTCODE code);
	
	virtual  void OnListPartsComplete(OSSClient *client,PartListing &result);
	virtual  void OnListPartsFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnListMultipartUploadsComplete(OSSClient *client,MultipartUploadListing &result);
	virtual  void OnListMultipartUploadsFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnInitiateMultipartUploadComplete(OSSClient *client,InitiateMultipartUploadResult &result);
	virtual  void OnInitiateMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnCompleteMultipartUploadComplete(OSSClient *client,CompleteMultipartUploadResult &result);
	virtual  void OnCompleteMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code);

	virtual  void OnAbortMultipartUploadComplete(OSSClient *client,string &puloadId);
	virtual  void OnAbortMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code);
	virtual  void OnNetworkFailed(OSSClient *client,OSS_RESULTCODE code);
};



