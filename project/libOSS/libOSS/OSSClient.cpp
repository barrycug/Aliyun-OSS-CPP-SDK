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
#include "OSSClient.h"

namespace OSS
{
OSSClient::OSSClient(string &accessID,string &accessKey)
{
	_endPoint = "http://storage.aliyun.com";
	_credentials.accessID = accessID;
	_credentials.accessKey = accessKey;
	init();
}
OSSClient::OSSClient(string &accessID,string &accessKey,ClientConfiguration &config)
{
	_endPoint = "http://storage.aliyun.com";
	_credentials.accessID = accessID;
	_credentials.accessKey = accessKey;
	_clientConfiguration = config;
	init();
}
OSSClient::OSSClient(string &endPoint,string &accessID,string &accessKey)
{
	_endPoint = endPoint;
	_credentials.accessID = accessID;
	_credentials.accessKey = accessKey;
	init();
}
OSSClient::OSSClient(string &endPoint,string &accessID,string &accessKey,ClientConfiguration &config)
{
	_endPoint = endPoint;
	_credentials.accessID = accessID;
	_credentials.accessKey = accessKey;
	_clientConfiguration = config;
	
	init();
}
OSSClient::~OSSClient(void)
{
	if (_pBucketSC != NULL)
	{
		delete _pBucketSC;
		_pBucketSC = NULL;
	}
	if (_pBucketOperation != NULL)
	{
		delete _pBucketOperation;
		_pBucketOperation = NULL;
	}
	if (_pObjectSC != NULL)
	{
		delete _pObjectSC;
		_pObjectSC = NULL;
	}
	if (_pObjectOperation != NULL)
	{
		delete _pObjectOperation;
		_pObjectOperation = NULL;
	}
	if (_pMultiPartSC != NULL)
	{
		delete _pMultiPartSC;
		_pMultiPartSC = NULL;
	}
	if (_pMultipartOperation != NULL)
	{
		delete _pMultipartOperation;
		_pMultipartOperation = NULL;
	}
	if (_pObjectGroupSC != NULL)
	{
		delete _pObjectGroupSC;
		_pObjectGroupSC = NULL;
	}
	if (_pObjectGroupOperation != NULL)
	{
		delete _pObjectGroupOperation;
		_pObjectGroupOperation = NULL;
	}
}
void OSSClient::init()
{
	_pBucketSC = new DefaultServiceClient(_clientConfiguration);	
	_pBucketOperation = new OSSBucketOperation(_endPoint,_credentials,_pBucketSC);
	_pBucketOperation->delegate = this;

	_pObjectSC = new DefaultServiceClient(_clientConfiguration);
	_pObjectOperation = new OSSObjectOperation(_endPoint,_credentials,_pObjectSC);
	_pObjectOperation->delegate = this;

	_pMultiPartSC = new DefaultServiceClient(_clientConfiguration);	
	_pMultipartOperation = new OSSMultipartOperation(_endPoint,_credentials,_pMultiPartSC);
	_pMultipartOperation->delegate = this;

	_pObjectGroupSC = new DefaultServiceClient(_clientConfiguration);
	_pObjectGroupOperation = new OSSObjectGroupOperation(_endPoint,_credentials,_pObjectGroupSC);
	_pObjectGroupOperation->delegate = this;
	delegate = NULL;

}
OSS_RESULTCODE OSSClient::CreateBucket(string &bucketName,Bucket &bucket)
{
	return _pBucketOperation->CreateBucket(bucketName,bucket);
}
OSS_RESULTCODE OSSClient::DeleteBucket(string &bucketName)
{
	return _pBucketOperation->DeleteBucket(bucketName);
}
OSS_RESULTCODE OSSClient::ListBuckets(Buckets &buckets)
{
	return _pBucketOperation->ListBuckets(buckets);
}
OSS_RESULTCODE OSSClient::SetBucketACL(string &bucketName,CannedAccessControlList &aclList)
{
	return _pBucketOperation->SetBucketACL(bucketName,aclList);
}
OSS_RESULTCODE OSSClient::GetBucketACL(string &bucketName,CannedAccessControlList &aclList)
{
	return _pBucketOperation->GetBucketACL( bucketName,aclList);
}
OSS_RESULTCODE OSSClient::IsBucketExist(string &bucketName,bool &isExist)
{
	return _pBucketOperation->IsBucketExist(bucketName,isExist);
}
OSS_RESULTCODE OSSClient:: ListObjects(ListObjectsRequest & reuqest,ObjectListing &objectListing)
{
	return _pBucketOperation->ListObjects(reuqest,objectListing);
}
bool OSSClient::CreateBucket_Async(string &bucketName)
{
	return _pBucketOperation->CreateBucket_Async(bucketName);
}
bool OSSClient::DeleteBucket_Async(string &bucketName)
{
	return _pBucketOperation->DeleteBucket_Async(bucketName);
}
bool OSSClient::ListBuckets_Async()
{
	return _pBucketOperation->ListBuckets_Async();
}
bool OSSClient::SetBucketACL_Async(string &bucketName,CannedAccessControlList &aclList)
{
	return _pBucketOperation->SetBucketACL_Async(bucketName,aclList);
}
bool OSSClient::GetBucketACL_Async(string &bucketName)
{
	return _pBucketOperation->GetBucketACL_Async( bucketName);
}
bool OSSClient::IsBucketExist_Async(string &bucketName)
{
	return _pBucketOperation->IsBucketExist_Async(bucketName);
}
bool OSSClient::ListObjects_Async(ListObjectsRequest & reuqest)
{
	return _pBucketOperation->ListObjects_Async(reuqest);
}
OSS_RESULTCODE OSSClient::PutObject(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata,PutObjectResult &result)
{
	return _pObjectOperation->PutObject(bucketName,key,data,dataLength,objectMetadata,result);
}
OSS_RESULTCODE OSSClient::FetchObject(FetchObjectRequest &request,OSSObject & result)
{
	return _pObjectOperation->FetchObject(request,result);
}
OSS_RESULTCODE OSSClient::FetchObject(string &bucketName,string &key,OSSObject & result)
{
	return _pObjectOperation->FetchObject(bucketName,key,result);
}
OSS_RESULTCODE OSSClient::FetchObject(string &bucketName,string &key,string &filePath)
{
	return _pObjectOperation->FetchObject(bucketName,key,filePath);
}
OSS_RESULTCODE OSSClient::FetchObject(FetchObjectRequest &request,string &filePath)
{
	return _pObjectOperation->FetchObject(request,filePath);
}
OSS_RESULTCODE OSSClient::GetObjectMetadata(string &bucketName,string &key,ObjectMetadata &objectMetadata)
{
	return _pObjectOperation->GetObjectMetadata(bucketName,key,objectMetadata);
}
OSS_RESULTCODE OSSClient::CopyObject(CopyObjectRequest & request,CopyObjectResult &result)
{
	return _pObjectOperation->CopyObject(request,result);
}
OSS_RESULTCODE OSSClient::DeleteObject(string &bucketName,string &key)
{
	return _pObjectOperation->DeleteObject(bucketName,key);

}
OSS_RESULTCODE OSSClient::DeleteMultipleObjects(string &bucketName,vector<string> &objNames, bool isQuiet,DeleteObjectsResult & result)
{
	return _pObjectOperation->DeleteMultipleObjects(bucketName,objNames,isQuiet,result);
}

bool OSSClient::PutObject_Async(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata)
{
	return _pObjectOperation->PutObject_Async(bucketName,key,data,dataLength,objectMetadata);
}
bool OSSClient::FetchObject_Async(string &bucketName,string &key)
{
	return _pObjectOperation->FetchObject_Async(bucketName,key);
}
bool OSSClient::FetchObject_Async(FetchObjectRequest &request)
{
	return _pObjectOperation->FetchObject_Async(request);
}
//大文件请使用该方法
bool OSSClient::FetchObject_Async(string &bucketName,string &key,string &filePath)
{
	return _pObjectOperation->FetchObject_Async(bucketName,key,filePath);
}
bool OSSClient::FetchObject_Async(FetchObjectRequest &request,string &filePath)
{
	return _pObjectOperation->FetchObject_Async(request,filePath);
}
bool OSSClient::GetObjectMetadata_Async(string &bucketName,string &key)
{
	return _pObjectOperation->GetObjectMetadata_Async(bucketName,key);
}
bool OSSClient::CopyObject_Async(CopyObjectRequest & request)
{
	return _pObjectOperation->CopyObject_Async(request);
}
bool OSSClient::DeleteObject_Async(string &bucketName,string &key)
{
	return _pObjectOperation->DeleteObject_Async(bucketName,key);
}
bool OSSClient::DeleteMultipleObjects_Async(string &bucketName,vector<string> &objNames, bool isQuiet)
{
	return _pObjectOperation->DeleteMultipleObjects_Async(bucketName,objNames,isQuiet);
}
OSS_RESULTCODE OSSClient::UploadPart(UploadPartRequest & uploadPartRequest,UploadPartResult & result)
{
	return _pMultipartOperation->UploadPart(uploadPartRequest,result);
}
OSS_RESULTCODE OSSClient::ListParts(ListPartsRequest & listPartsRequest,PartListing &result)
{
	return _pMultipartOperation->ListParts(listPartsRequest,result);
}
OSS_RESULTCODE OSSClient::ListMultipartUploads(ListMultipartUploadsRequest &listMultipartUploadsRequest,MultipartUploadListing &result)
{
	return _pMultipartOperation->ListMultipartUploads(listMultipartUploadsRequest,result);
}
OSS_RESULTCODE OSSClient::InitiateMultipartUpload(InitiateMultipartUploadRequest & initiateMultipartUploadRequest,InitiateMultipartUploadResult &result)
{
	return _pMultipartOperation->InitiateMultipartUpload( initiateMultipartUploadRequest, result);
}
OSS_RESULTCODE OSSClient::CompleteMultipartUpload(CompleteMultipartUploadRequest &completeMultipartUploadRequest,CompleteMultipartUploadResult &result)
{
	return _pMultipartOperation->CompleteMultipartUpload(completeMultipartUploadRequest,result);
}
OSS_RESULTCODE OSSClient::AbortMultipartUpload(AbortMultipartUploadRequest & abortMultipartUploadRequest,string& uploadId)
{
	return _pMultipartOperation->AbortMultipartUpload(abortMultipartUploadRequest,uploadId);
}
//异步调用
bool OSSClient::UploadPart_Async(UploadPartRequest & uploadPartRequest)
{
	return _pMultipartOperation->UploadPart_Async(uploadPartRequest);
}
bool OSSClient::ListParts_Async(ListPartsRequest & listPartsRequest)
{
	return _pMultipartOperation->ListParts_Async(listPartsRequest);
}
bool OSSClient::ListMultipartUploads_Async(ListMultipartUploadsRequest &listMultipartUploadsRequest)
{
	return _pMultipartOperation->ListMultipartUploads_Async(listMultipartUploadsRequest);
}
bool OSSClient::InitiateMultipartUpload_Async(InitiateMultipartUploadRequest & initiateMultipartUploadRequest)
{
	return _pMultipartOperation->InitiateMultipartUpload_Async(initiateMultipartUploadRequest);
}
bool OSSClient::CompleteMultipartUpload_Async(CompleteMultipartUploadRequest &completeMultipartUploadRequest)
{
	return _pMultipartOperation->CompleteMultipartUpload_Async(completeMultipartUploadRequest);
}
bool OSSClient::AbortMultipartUpload_Async(AbortMultipartUploadRequest & abortMultipartUploadRequest)
{
	return _pMultipartOperation->AbortMultipartUpload_Async(abortMultipartUploadRequest);
}

OSS_RESULTCODE OSSClient::PostObjectGroup(PostObjectGroupRequest &postObjectGroupRequest,PostObjectGroupResult & reault)
{
	return _pObjectGroupOperation->PostObjectGroup(postObjectGroupRequest,reault);
}
OSS_RESULTCODE OSSClient::GetObjectGroupIndex(string &bucketName ,string &key,FetchObjectGroupIndexResult &result)
{
	return _pObjectGroupOperation->GetObjectGroupIndex(bucketName,key,result);
}

OSS_RESULTCODE OSSClient::GetObjectGroup(string &bucketName ,string &key)
{
	return _pObjectGroupOperation->GetObjectGroup(bucketName,key);
}
OSS_RESULTCODE OSSClient::DeleteObjectGroup(string &bucketName ,string &key)
{
	return _pObjectGroupOperation->DeleteObjectGroup(bucketName,key);
}
OSS_RESULTCODE OSSClient::GetObjectGroupMetadata(string &bucketName ,string &key,ObjectMetadata &objectMetadata)
{
	return _pObjectGroupOperation->GetObjectGroupMetadata(bucketName,key,objectMetadata);
}
//异步调用
bool OSSClient::PostObjectGroup_Async(PostObjectGroupRequest &postObjectGroupRequest)
{
	return _pObjectGroupOperation->PostObjectGroup_Async(postObjectGroupRequest);
}
bool OSSClient::GetObjectGroupIndex_Async(string &bucketName ,string &key)
{
	return _pObjectGroupOperation->GetObjectGroupIndex_Async(bucketName,key);
}
bool OSSClient::GetObjectGroup_Async(string &bucketName ,string &key)
{
	return _pObjectGroupOperation->GetObjectGroup_Async(bucketName,key);
}
bool OSSClient::DeleteObjectGroup_Async(string &bucketName ,string &key)
{
	return _pObjectGroupOperation->DeleteObjectGroup_Async(bucketName ,key);
}
bool OSSClient::GetObjectGroupMetadata_Async(string &bucketName,string &key)
{
	return _pObjectGroupOperation->GetObjectGroupMetadata_Async(bucketName ,key);
}

//代理相关方法
void OSSClient::OnCreateBucketComplete(OSSBucketOperation * bucketOperation,Bucket &bucket)
{
	if(delegate != NULL)
	{
		delegate->OnCreateBucketComplete(this,bucket);
	}
}
void OSSClient::OnCreateBucketFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnCreateBucketFailed(this,code);
	}
}
void OSSClient::OnDeleteBucketComplete(OSSBucketOperation * bucketOperation,string &bucketName)
{
	if(delegate != NULL)
	{
		delegate->OnDeleteBucketComplete(this,bucketName);
	}
}
void OSSClient::OnDeleteBucketFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnDeleteBucketFailed(this,code);
	}
}
void OSSClient::OnListBucketsComplete(OSSBucketOperation * bucketOperation,Buckets &buckets)
{
	if(delegate != NULL)
	{
		delegate->OnListBucketsComplete(this,buckets);
	}
}
void OSSClient::OnListBucketsFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnListBucketsFailed(this,code);
	}
}
void OSSClient::OnSetBucketACLComplete(OSSBucketOperation * bucketOperation)
{
	if(delegate != NULL)
	{
		delegate->OnSetBucketACLComplete(this);
	}
}
void OSSClient::OnSetBucketACLFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnSetBucketACLFailed(this,code);
	}
}
void OSSClient::OnGetBucketACLComplete(OSSBucketOperation * bucketOperation,CannedAccessControlList &aclList)
{
	if(delegate != NULL)
	{
		delegate->OnGetBucketACLComplete(this,aclList);
	}
}
void OSSClient::OnGetBucketACLFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnGetBucketACLFailed(this,code);
	}
}
void OSSClient::OnIsBucketExistComplete(OSSBucketOperation * bucketOperation,bool &isExist)
{
	if(delegate != NULL)
	{
		delegate->OnIsBucketExistComplete(this,isExist);
	}
}
void OSSClient::OnIsBucketExistFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnIsBucketExistFailed(this,code);
	}
}
void OSSClient::OnListObjectsComplete(OSSBucketOperation * bucketOperation,ObjectListing &objectListing)
{
	if(delegate != NULL)
	{
		delegate->OnListObjectsComplete(this,objectListing);
	}
}
void OSSClient::OnListObjectsFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnListObjectsFailed(this,code);
	}
}
void OSSClient::OnNetworkFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnNetworkFailed(this,code);
	}
}


//Object Op
void OSSClient::OnPutObjectComplete(OSSObjectOperation * objectOperation,PutObjectResult &result)
{
	if(delegate != NULL)
	{
		delegate->OnPutObjectComplete(this,result);
	}
}
void OSSClient::OnPutObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnPutObjectFailed(this,code);
	}
}
void OSSClient::OnFetchObjectComplete(OSSObjectOperation * objectOperation,OSSObject &object)
{
	if(delegate != NULL)
	{
		delegate->OnFetchObjectComplete(this,object);
	}
}
void OSSClient::OnFetchObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnFetchObjectFailed(this,code);
	}
}
void OSSClient::OnFetchObjectToFileComplete(OSSObjectOperation * objectOperation,string &fileName)
{
	if(delegate != NULL)
	{
		delegate->OnFetchObjectToFileComplete(this,fileName);
	}
}
void OSSClient::OnFetchObjectToFileFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnFetchObjectToFileFailed(this,code);
	}
}
void OSSClient::OnGetObjectMetadataComplete(OSSObjectOperation * objectOperation,ObjectMetadata &objectMetadata)
{
	if(delegate != NULL)
	{
		delegate->OnGetObjectMetadataComplete(this,objectMetadata);
	}
}
void OSSClient::OnGetObjectMetadataFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnGetObjectMetadataFailed(this,code);
	}
}
void OSSClient::OnCopyObjectComplete(OSSObjectOperation * objectOperation,CopyObjectResult &result)
{
	if(delegate != NULL)
	{
		delegate->OnCopyObjectComplete(this,result);
	}
}
void OSSClient::OnCopyObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnCopyObjectFailed(this,code);
	}
}
void OSSClient::OnDeleteObjectComplete(OSSObjectOperation * objectOperation)
{
	if(delegate != NULL)
	{
		delegate->OnDeleteObjectComplete(this);
	}
}
void OSSClient::OnDeleteObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnDeleteObjectFailed(this,code);
	}
}
void OSSClient::OnDeleteMultipleObjectsComplete(OSSObjectOperation * objectOperation,DeleteObjectsResult &result)
{
	if(delegate != NULL)
	{
		delegate->OnDeleteMultipleObjectsComplete(this,result);
	}
}
void OSSClient::OnDeleteMultipleObjectsFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnDeleteMultipleObjectsFailed(this,code);
	}
}	
void OSSClient::OnNetworkFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnNetworkFailed(this,code);
	}
}


//MutiPart Op
void OSSClient::OnUploadPartComplete(OSSMultipartOperation * multipartOperation,UploadPartResult &result)
{
	if(delegate != NULL)
	{
		delegate->OnUploadPartComplete(this,result);
	}
}
void OSSClient::OnUploadPartFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnUploadPartFailed(this,code);
	}
}	
void OSSClient::OnListPartsComplete(OSSMultipartOperation * multipartOperation,PartListing &result)
{
	if(delegate != NULL)
	{
		delegate->OnListPartsComplete(this,result);
	}
}
void OSSClient::OnListPartsFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnListPartsFailed(this,code);
	}
}
void OSSClient::OnListMultipartUploadsComplete(OSSMultipartOperation * multipartOperation,MultipartUploadListing &result)
{
	if(delegate != NULL)
	{
		delegate->OnListMultipartUploadsComplete(this,result);
	}
}
void OSSClient::OnListMultipartUploadsFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnListMultipartUploadsFailed(this,code);
	}
}
void OSSClient::OnInitiateMultipartUploadComplete(OSSMultipartOperation * multipartOperation,InitiateMultipartUploadResult &result)
{
	if(delegate != NULL)
	{
		delegate->OnInitiateMultipartUploadComplete(this,result);
	}
}
void OSSClient::OnInitiateMultipartUploadFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnInitiateMultipartUploadFailed(this,code);
	}
}
void OSSClient::OnCompleteMultipartUploadComplete(OSSMultipartOperation * multipartOperation,CompleteMultipartUploadResult &result)
{
	if(delegate != NULL)
	{
		delegate->OnCompleteMultipartUploadComplete(this,result);
	}
}
void OSSClient::OnCompleteMultipartUploadFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnCompleteMultipartUploadFailed(this,code);
	}
}
void OSSClient::OnAbortMultipartUploadComplete(OSSMultipartOperation * multipartOperation,string &puloadId)
{
	if(delegate != NULL)
	{
		delegate->OnAbortMultipartUploadComplete(this,puloadId);
	}
}
void OSSClient::OnAbortMultipartUploadFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnAbortMultipartUploadFailed(this,code);
	}
}
void OSSClient::OnNetworkFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnNetworkFailed(this,code);
	}
}
	

//ObjectGroup Op
void OSSClient::OnPostObjectGroupComplete(OSSObjectGroupOperation * objectGroupOperation,PostObjectGroupResult &result)
{
	if(delegate != NULL)
	{
		delegate->OnPostObjectGroupComplete(this,result);
	}
}
void OSSClient::OnPostObjectGroupFailed(OSSObjectGroupOperation * objectGroupOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnPostObjectGroupFailed(this,code);
	}
}
void OSSClient::OnGetObjectGroupIndexComplete(OSSObjectGroupOperation * objectGroupOperation,FetchObjectGroupIndexResult &result)
{
	if(delegate != NULL)
	{
		delegate->OnGetObjectGroupIndexComplete(this,result);
	}
}
void OSSClient::OnGetObjectGroupIndexFailed(OSSObjectGroupOperation * objectGroupOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnGetObjectGroupIndexFailed(this,code);
	}
}
void OSSClient::OnNetworkFailed(OSSObjectGroupOperation * objectGroupOperation,OSS_RESULTCODE code)
{
	if(delegate != NULL)
	{
		delegate->OnNetworkFailed(this,code);
	}
}
}
