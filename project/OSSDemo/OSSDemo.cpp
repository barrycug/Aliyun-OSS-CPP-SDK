// OSSDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <curl/curl.h>
#include <string.h>
#include "HTTPRequest.h"
#include "HttpCallback.h"
#include "OSSClient.h"
#include "ClientConfiguration.h"
#include "CannedAccessControlList.h"
#include "Buckets.h"
#include "ObjectListing.h"
#include "PutObjectResult.h"
#include "md5.h"
#include "HttpUtil.h"
#include "OSSClientTest.h"
using  namespace OSS;

int _tmain(int argc, _TCHAR* argv[])
{

	string aID = "9e0g1wvcoc9889d4c685iyq3";
	string akey ="MzxWwbrsHrFxnQCgY3ET8suIqck=";
	ClientConfiguration config;
	OSS::OSSClient *_ptClient = new  OSSClient(aID,akey,config);
	string bName = "barrycug11";
	Bucket bucket;
   
	
	//同步请求
	/*
//	_ptClient->DeleteBucket(bName);
	Buckets buckets;
	//_ptClient->ListBuckets(buckets);
	//_ptClient->CreateBucket(bName,bucket);
	CannedAccessControlList acl;
	//acl.cannedAclType = CannedAclType_PublicRead;
	//_ptClient->SetBucketACL(bName,acl);
//	_ptClient->GetBucketACL(bName,acl);
	ListObjectsRequest request(bName);
	ObjectListing objectListing;
//	_ptClient->ListObjects(request,objectListing);
	string key="testObj";
	char data[100]="1234中国";
	ObjectMetadata objMetadata;
	PutObjectResult result;
	//_ptClient->PutObject(bName,key,data,sizeof(data),objMetadata,result);
	string fileName = "c:\\111.txt";
	OSSObject obj;
//	_ptClient->GetObjectMetadata(bName,key,objMetadata);
	CopyObjectRequest cpRequest;
	cpRequest.sourceBucketName = bName;
	cpRequest.sourceKey = "宝才/test1.txt";
	cpRequest.destinationBucketName = bName;
	cpRequest.destinationkey = "宝才/22";
	CopyObjectResult cpResult;
//	_ptClient->CopyObject(cpRequest,cpResult);
//	_ptClient->DeleteObject(bName,key);
	vector<string> keys;
	keys.push_back("test333");
	keys.push_back("test222");
	
	DeleteObjectsResult dResult;
//	_ptClient->DeleteMultipleObjects(bName,keys,true,dResult);
	PostObjectGroupRequest poRequest;
	poRequest.bucketName = bName;
	poRequest.objectGroupName = "宝才/group2";
	vector<ObjectGroupPartETag> objectGroupPartETags;
	ObjectGroupPartETag part1 ;
	part1.partName="宝才/p1.txt";
	part1.partNumber = 1;
	part1.eTag = "CB605CF60A69B730F407D1635DFF6CF4";
	objectGroupPartETags.push_back(part1);
	ObjectGroupPartETag part2 ;
	part2.partName="宝才/test1.txt";
	part2.partNumber = 2;
	part2.eTag = "C13DCEABCB143ACD6C9298265D618A9F";
	objectGroupPartETags.push_back(part2);
	poRequest.objectGroupPartETags = objectGroupPartETags;
	PostObjectGroupResult pogResult;
//	_ptClient->PostObjectGroup(poRequest,pogResult);
	string keyGroup = "宝才/group";
	FetchObjectGroupIndexResult fogiResult;
//	_ptClient->GetObjectGroupIndex(bName,keyGroup,fogiResult);
	InitiateMultipartUploadRequest imRequest;
	imRequest.bucketName = bName;
	imRequest.key = "testMP14";
	InitiateMultipartUploadResult imResult;
	_ptClient->InitiateMultipartUpload(imRequest,imResult);
	*/
	/*
	AbortMultipartUploadRequest amRequest ;
	amRequest.bucketName = bName;
	amRequest.key = "testMP";
	amRequest.uploadId = imResult.uploadId;
	string uploadID;
	_ptClient->AbortMultipartUpload(amRequest,uploadID);
	*/
	/*
	UploadPartRequest upRequest;
	UploadPartResult upResult;
	upRequest.bucketName = bName;
	upRequest.key = "testMP14";
	upRequest.partNumber = 1;
	upRequest.uploadId = imResult.uploadId;
	FILE * pf = fopen("D:\\goagent.zip","rb");
	fseek(pf,0,SEEK_END);
	long long sz = ftell(pf);
	fseek(pf,0,SEEK_SET);
	void * fileData = malloc(sz);
	fread(fileData,1,sz,pf);
	upRequest.partSize = sz;
	upRequest.data = (char*)fileData;
	md5_context content;
	md5_starts(&content);
	md5_update(&content,(unsigned char*)fileData,sz);
	uint8 digest[16];
    md5_finish( &content, digest );
	string md5digest;
	md5digest.append((char*)digest);
	upRequest.md5Digest =md5digest;
	_ptClient->UploadPart(upRequest,upResult);
	PartETag etag1 ;
	etag1.eTag = upResult.eTag;
	etag1.partNumber = 1;
	free(fileData);
	fileData = NULL;
	sz;
	fclose(pf);
	pf = NULL;

	upRequest.bucketName = bName;
	upRequest.key = "testMP14";
	upRequest.partNumber = 2;
	upRequest.uploadId = imResult.uploadId;
	pf = fopen("D:\\111.dat","rb");
	fseek(pf,0,SEEK_END);
	sz = ftell(pf);
	fseek(pf,0,SEEK_SET);
	fileData = malloc(sz);
	fread(fileData,1,sz,pf);
	upRequest.partSize = sz;
	upRequest.data = (char*)fileData;
	md5_starts(&content);
	md5_update(&content,(unsigned char*)fileData,sz);
	uint8 digest2[16];
    md5_finish( &content, digest2 );
	string md5digest2;
	md5digest2.append((char*)digest2);
	upRequest.md5Digest =md5digest2;
	_ptClient->UploadPart(upRequest,upResult);
	PartETag etag2 ;
	etag2.eTag = upResult.eTag;
	etag2.partNumber = 2;
	free(fileData);
	fileData = NULL;
	sz;
	fclose(pf);
	pf = NULL;
	
	CompleteMultipartUploadRequest cmuRequest ;
	cmuRequest.bucketName = bName;
	cmuRequest.key = "testMP14";
	cmuRequest.uploadId = imResult.uploadId;
	cmuRequest.partETags.push_back(etag1);
	cmuRequest.partETags.push_back(etag2);
	CompleteMultipartUploadResult cmpResult;
	_ptClient->CompleteMultipartUpload(cmuRequest,cmpResult);
	*/
	/*
	string uploadId = "0004CA96EBFB8539EC9737518BEF24EA";
	ListPartsRequest lpRequest;
	lpRequest.bucketName = bName;
	lpRequest.key = "testMP12";
	lpRequest.uploadId = uploadId;
	lpRequest.maxParts =2;
	lpRequest.partNumberMarker = 1;
	PartListing plResult;
	_ptClient->ListParts(lpRequest,plResult);
	*/
	
	/*

	ListMultipartUploadsRequest lmuRequest ;
	lmuRequest.bucketName = bName;
	MultipartUploadListing mulResult;
	_ptClient->ListMultipartUploads(lmuRequest,mulResult);
	*/

	///////////////////
	//异步请求
	 OSSClientTest *ptOSSClientTest = new OSSClientTest();
	 _ptClient->delegate =(OSSClientCallback *)ptOSSClientTest;

	// _ptClient->ListBuckets_Async();
	 bName = "barryc115";
	// _ptClient->DeleteBucket_Async(bName);
	 bName = "barryc116";
//	 _ptClient->CreateBucket_Async(bName);
	  bName = "barrycug11";
	  ListObjectsRequest loRequest(bName);

//	 _ptClient->ListObjects_Async(loRequest);
	 CannedAccessControlList acl;
	acl.cannedAclType = CannedAclType_PublicRead;
	//_ptClient->SetBucketACL_Async(bName,acl);
//	_ptClient->GetBucketACL_Async(bName);

	string key="testObj2";
	char data[20]="1234中国";
	ObjectMetadata objMetadata;
	PutObjectResult result;
//	_ptClient->PutObject_Async(bName,key,data,sizeof(data),objMetadata);

//	_ptClient->GetObjectMetadata_Async(bName,key);

	CopyObjectRequest cpRequest;
	cpRequest.sourceBucketName = bName;
	cpRequest.sourceKey = "宝才/test1.txt";
	cpRequest.destinationBucketName = bName;
	cpRequest.destinationkey = "宝才/2222";
	CopyObjectResult cpResult;
//	_ptClient->CopyObject_Async(cpRequest);

//	_ptClient->DeleteObject_Async(bName,key);

	vector<string> keys;
	keys.push_back("test333");
	keys.push_back("test222");
	
	DeleteObjectsResult dResult;
	_ptClient->DeleteMultipleObjects_Async(bName,keys,true);


	PostObjectGroupRequest poRequest;
	poRequest.bucketName = bName;
	poRequest.objectGroupName = "宝才/group2";
	vector<ObjectGroupPartETag> objectGroupPartETags;
	ObjectGroupPartETag part1 ;
	part1.partName="宝才/p1.txt";
	part1.partNumber = 1;
	part1.eTag = "CB605CF60A69B730F407D1635DFF6CF4";
	objectGroupPartETags.push_back(part1);
	ObjectGroupPartETag part2 ;
	part2.partName="宝才/test1.txt";
	part2.partNumber = 2;
	part2.eTag = "C13DCEABCB143ACD6C9298265D618A9F";
	objectGroupPartETags.push_back(part2);
	poRequest.objectGroupPartETags = objectGroupPartETags;
	PostObjectGroupResult pogResult;
//	_ptClient->PostObjectGroup_Async(poRequest);
	string keyGroup = "宝才/group";
	FetchObjectGroupIndexResult fogiResult;
//	_ptClient->GetObjectGroupIndex_Async(bName,keyGroup);
	

	 delete _ptClient;
	 _ptClient = NULL;
}
