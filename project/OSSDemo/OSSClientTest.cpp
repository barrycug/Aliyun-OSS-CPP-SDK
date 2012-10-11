#include "stdafx.h"
#include "OSSClientTest.h"
OSSClientTest::OSSClientTest(void)
{
}


OSSClientTest::~OSSClientTest(void)
{
}
void OSSClientTest::OnCreateBucketComplete(OSSClient *client,Bucket &bucket)
{
}
void OSSClientTest::OnCreateBucketFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnDeleteBucketComplete(OSSClient *client,string &bucketName)
{
}
void OSSClientTest::OnDeleteBucketFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnListBucketsComplete(OSSClient *client,Buckets &buckets)
{
}
void OSSClientTest::OnListBucketsFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnSetBucketACLComplete(OSSClient *client)
{
}
void OSSClientTest::OnSetBucketACLFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnGetBucketACLComplete(OSSClient *client,CannedAccessControlList &aclList)
{
}
void OSSClientTest::OnGetBucketACLFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnIsBucketExistComplete(OSSClient *client,bool &isExist)
{
}
void OSSClientTest::OnIsBucketExistFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnListObjectsComplete(OSSClient *client,ObjectListing &objectListing)
{
}
void OSSClientTest::OnListObjectsFailed(OSSClient *client,OSS_RESULTCODE code)
{
}
//Object Op
void OSSClientTest::OnPutObjectComplete(OSSClient *client,PutObjectResult &result)
{
}
void OSSClientTest::OnPutObjectFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnFetchObjectComplete(OSSClient *client,OSSObject &object)
{
}
void OSSClientTest::OnFetchObjectFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnFetchObjectToFileComplete(OSSClient *client,string &fileName)
{
}
void OSSClientTest::OnFetchObjectToFileFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnGetObjectMetadataComplete(OSSClient *client,ObjectMetadata &objectMetadata)
{
}
void OSSClientTest::OnGetObjectMetadataFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnCopyObjectComplete(OSSClient *client,CopyObjectResult &result)
{
}
void OSSClientTest::OnCopyObjectFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnDeleteObjectComplete(OSSClient *client)
{
}
void OSSClientTest::OnDeleteObjectFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnDeleteMultipleObjectsComplete(OSSClient *client,DeleteObjectsResult &result)
{
}
void OSSClientTest::OnDeleteMultipleObjectsFailed(OSSClient *client,OSS_RESULTCODE code)
{
}
void OSSClientTest::OnPostObjectGroupComplete(OSSClient *client,PostObjectGroupResult &result)
{
}
void OSSClientTest::OnPostObjectGroupFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnGetObjectGroupIndexComplete(OSSClient *client,FetchObjectGroupIndexResult &result)
{
}
void OSSClientTest::OnGetObjectGroupIndexFailed(OSSClient *client,OSS_RESULTCODE code)
{
}
//multipart Op
void OSSClientTest::OnUploadPartComplete(OSSClient *client,UploadPartResult &result)
{
}
void OSSClientTest::OnUploadPartFailed(OSSClient *client,OSS_RESULTCODE code)
{
}
	
void OSSClientTest::OnListPartsComplete(OSSClient *client,PartListing &result)
{
}
void OSSClientTest::OnListPartsFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnListMultipartUploadsComplete(OSSClient *client,MultipartUploadListing &result)
{
}
void OSSClientTest::OnListMultipartUploadsFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnInitiateMultipartUploadComplete(OSSClient *client,InitiateMultipartUploadResult &result)
{
}
void OSSClientTest::OnInitiateMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnCompleteMultipartUploadComplete(OSSClient *client,CompleteMultipartUploadResult &result)
{
}
void OSSClientTest::OnCompleteMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

void OSSClientTest::OnAbortMultipartUploadComplete(OSSClient *client,string &puloadId)
{
}
void OSSClientTest::OnAbortMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code)
{
}
void OSSClientTest::OnNetworkFailed(OSSClient *client,OSS_RESULTCODE code)
{
}

