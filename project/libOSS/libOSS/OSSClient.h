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
/*! \mainpage OSS library
 * \section intro_sec Introduction
 *
 *
OSS SDK for C++ 使用说明 \n
1 简介 \n
Aliyun OSS C++ SDK使用c++实现了Aliyun OSS提供的功能，主要包括Bucket的创建、删除、浏览。Object的创建、删除浏览以及多点上传等功能，关于OSS提供的服务请参考OSS API说明文档。\n
2 主要内容\n
Aliyun OSS C++ SDK主要包括源代码（BSD协议开源）、说明文档、示例工程、帮助文档等。\n
该SDK开发环境为vs2012，提供了vs2012的工程文件，目前只支持windows平台，暂不支持跨平台使用。\n
该SDK提供头文件和动态库和lib文件用于开发。\n
3 第三方库\n
本SDK使用到的第三方类库包括以下部分：\n
Libcurl\n
Xmlparser\n
4 使用步骤\n
4.1 新建vs2012 工程，将vc include目录设为SDK目录下的include目录，Library目录设为SDK目录下的bin目录。\n
4.2 工程Output目录设为SDK目录下的bin目录。\n
4.3 在Linker属性下Input中添加libcurl.lib和libOSS.lib\n
4.4 在代码中包含头文件OSSClient.h\n
#include "OSSClient.h"\n
4.5 定义OSSClient对象，并使用accessID和accessKey初始化。\n
OSS::OSSClient *_ptClient = new  OSSClient(aID,akey,config);\n
4.6 使用OSSClient对OSS对象操作，OSS对象提供了四类对象的操作函数，包括Bucket，Object，MultiPart和ObjectGroup。OSSClient 还分别提供了同步和异步的方式进行调用。\n
4.6.1 同步方式调用\n
直接使用OSSClient对象调用即可。\n
_ptClient->ListBuckets(buckets);\n
4.6.2 异步方式调用\n
异步方式是web请求的主流请求方式，当请求返回的时候响应相关消息。\n
1）使用异步方式首先要实现代理类，该代理类必须继承OSS::OSSClientCallback 这个抽象基类，并实现抽象基类中定义的回调方法。\n
class OSSClientTest: OSS::OSSClientCallback\n
{\n
public:\n
	OSSClientTest(void);\n
	~OSSClientTest(void);\n
public:\n
	////Bucket Op\n
	virtual  void OnCreateBucketComplete(OSSClient *client,Bucket &bucket);\n
	virtual  void OnCreateBucketFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnDeleteBucketComplete(OSSClient *client,string &bucketName);\n
	virtual  void OnDeleteBucketFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnListBucketsComplete(OSSClient *client,Buckets &buckets);\n
	virtual  void OnListBucketsFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnSetBucketACLComplete(OSSClient *client);\n
	virtual  void OnSetBucketACLFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnGetBucketACLComplete(OSSClient *client,CannedAccessControlList &aclList);\n
	virtual  void OnGetBucketACLFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnIsBucketExistComplete(OSSClient *client,bool &isExist);\n
	virtual  void OnIsBucketExistFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnListObjectsComplete(OSSClient *client,ObjectListing &objectListing);\n
	virtual  void OnListObjectsFailed(OSSClient *client,OSS_RESULTCODE code);\n
	////Object Op\n
	virtual  void OnPutObjectComplete(OSSClient *client,PutObjectResult &result);\n
	virtual  void OnPutObjectFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnFetchObjectComplete(OSSClient *client,OSSObject &object);\n
	virtual  void OnFetchObjectFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnFetchObjectToFileComplete(OSSClient *client,string &fileName);\n
	virtual  void OnFetchObjectToFileFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnGetObjectMetadataComplete(OSSClient *client,ObjectMetadata &objectMetadata);\n
	virtual  void OnGetObjectMetadataFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnCopyObjectComplete(OSSClient *client,CopyObjectResult &result);\n
	virtual  void OnCopyObjectFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnDeleteObjectComplete(OSSClient *client);\n
	virtual  void OnDeleteObjectFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnDeleteMultipleObjectsComplete(OSSClient *client,DeleteObjectsResult &result);\n
	virtual  void OnDeleteMultipleObjectsFailed(OSSClient *client,OSS_RESULTCODE code);\n
	////ObjectGroup Op\n
	virtual  void OnPostObjectGroupComplete(OSSClient *client,PostObjectGroupResult &result);\n
	virtual  void OnPostObjectGroupFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnGetObjectGroupIndexComplete(OSSClient *client,FetchObjectGroupIndexResult &result);\n
	virtual  void OnGetObjectGroupIndexFailed(OSSClient *client,OSS_RESULTCODE code);\n
	////multipart Op\n
	virtual  void OnUploadPartComplete(OSSClient *client,UploadPartResult &result);\n
	virtual  void OnUploadPartFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnListPartsComplete(OSSClient *client,PartListing &result);\n
	virtual  void OnListPartsFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnListMultipartUploadsComplete(OSSClient *client,MultipartUploadListing &result);\n
	virtual  void OnListMultipartUploadsFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnInitiateMultipartUploadComplete(OSSClient *client,InitiateMultipartUploadResult &result);\n
	virtual  void OnInitiateMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnCompleteMultipartUploadComplete(OSSClient *client,CompleteMultipartUploadResult &result);\n
	virtual  void OnCompleteMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnAbortMultipartUploadComplete(OSSClient *client,string &puloadId);\n
	virtual  void OnAbortMultipartUploadFailed(OSSClient *client,OSS_RESULTCODE code);\n
	virtual  void OnNetworkFailed(OSSClient *client,OSS_RESULTCODE code);\n
};\n
2） 定义回调代理类\n
OSSClientTest *ptOSSClientTest = new OSSClientTest();\n
3）将代理类的指针赋给OSSClient 的delegate对象\n
 _ptClient->delegate =(OSSClientCallback *)ptOSSClientTest;\n
4） 调用以_Async结尾的相关方法对OSS对象操作\n
_ptClient->ListBuckets_Async();\n
\n
 *
 * @version     V1.0
 * @author      baocai zhang
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
#include "ClientConfiguration.h"
#include "ServiceCredentials.h"
#include "DefaultServiceClient.h"
#include "OSSBucketOperation.h"
#include "OSSMultipartOperation.h"
#include "OSSObjectGroupOperation.h"
#include "OSSObjectOperation.h"
#include "OSSClientCallback.h"

#include<string>
using namespace std;
namespace OSS
{
/**
@class OSSClient
@brief OSS 类库主要操作类，提供了同步和异步的方式对OSS对象进行操作
* 同步的方式会直接返回结果
* 异步的方式需要使用者继承并实现OSSClientCallback类中的相关回调方法，并讲delegate设置为该类的指针。异步的方式不会阻塞进程。
*/
class OSSDLL_API OSSClient: public OSSBucketOperationCallback,
	public OSSObjectOperationCallback,public OSSMultipartOperationCallback,public OSSObjectGroupOperationCallback
{
public:
	/**
	 @brief 构造函数，使用accessID 和accessKey 进行初始化
	 @param[in] accessID string
	 @param[in] accessKey string
	 */
	OSSClient(string &accessID,string &accessKey);
	/**
	 @brief 构造函数，使用accessID 、accessKey和客户端配置参数进行初始化
	 @param[in] accessID string
	 @param[in] accessKey string
	 @param[in] config ClientConfiguration
	 */
	OSSClient(string &accessID,string &accessKey,ClientConfiguration &config);
	/**
	 @brief 构造函数，使用endPoint，accessID 和accessKey进行初始化，endPoint 默认为"http://storage.aliyun.com"
	 @param[in] endPoint string
	 @param[in] accessID string
	 @param[in] accessKey string
	 */
	OSSClient(string &endPoint,string &accessID,string &accessKey);
	/**
	 @brief 构造函数，使用endPoint，accessID 、accessKey和客户端配置参数进进行初始化，endPoint 默认为"http://storage.aliyun.com"
	 @param[in] endPoint string
	 @param[in] accessID string
	 @param[in] accessKey string
	 @param[in] config ClientConfiguration
	 */
	OSSClient(string &endPoint,string &accessID,string &accessKey,ClientConfiguration &config);
	/**
	 @brief 析构函数
	 */
	~OSSClient(void);
private:
	string _endPoint;
	ClientConfiguration _clientConfiguration;
	ServiceCredentials _credentials;
	DefaultServiceClient *_pBucketSC;
	DefaultServiceClient *_pObjectSC;
	DefaultServiceClient *_pMultiPartSC;
	DefaultServiceClient *_pObjectGroupSC;
	OSSBucketOperation   *_pBucketOperation;
	OSSObjectOperation   *_pObjectOperation;
	OSSMultipartOperation *_pMultipartOperation;
	OSSObjectGroupOperation * _pObjectGroupOperation;
private:
	void init();
public:
	//同步
	/**
	 @brief 同步方法，创建bucket
	 @param[in] bucketName string
	 @param[out] bucket string
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE CreateBucket(string &bucketName,Bucket & bucket);
	/**
	 @brief 同步方法，删除bucket
	 @param[in] bucketName string
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE DeleteBucket(string &bucketName);
	/**
	 @brief 同步方法，罗列所有的bucket
	 @param[out] buckets Buckets
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE ListBuckets(Buckets &buckets);
	/**
	 @brief 同步方法，设置Bucket的访问控制权限
	 @param[in] bucketName string
	 @param[in] aclList CannedAccessControlList
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE SetBucketACL(string &bucketName,CannedAccessControlList &aclList);
	/**
	 @brief 同步方法，获得Bucket的访问控制权限
	 @param[in] bucketName string
	 @param[out] aclList CannedAccessControlList
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE GetBucketACL(string &bucketName,CannedAccessControlList &aclList);
	/**
	 @brief 同步方法，判断指定的bucket是否存在
	 @param[in] bucketName string
	 @param[out] isExist bool
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE IsBucketExist(string &bucketName,bool &isExist);
	/**
	 @brief 同步方法，罗列Bucket中的Object
	 @param[in] reuqest ListObjectsRequest
	 @param[out] objectListing ObjectListing
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE ListObjects(ListObjectsRequest & reuqest,ObjectListing &objectListing);
	//异步
	/**
	 @brief 同步方法，创建bucket
	 @param[in] bucketName string
	 @return bool类型值，用来判断函数是否成功
	 */
	bool CreateBucket_Async(string &bucketName);
	/**
	 @brief 异步方法，删除bucket
	 @param[in] bucketName string
	 @return bool类型值，用来判断函数是否成功
	 */
	bool DeleteBucket_Async(string &bucketName);
	/**
	 @brief 异步方法，罗列所有的bucket
	 @return bool类型值，用来判断函数是否成功
	 */
	bool ListBuckets_Async();
	/**
	 @brief 异步方法，设置Bucket的访问控制权限
	 @param[in] bucketName string
	 @param[in] aclList CannedAccessControlList
	 @return bool类型值，用来判断函数是否成功
	 */
	bool SetBucketACL_Async(string &bucketName,CannedAccessControlList &aclList);
	/**
	 @brief 异步方法，获得Bucket的访问控制权限
	 @param[in] bucketName string
	 @return bool类型值，用来判断函数是否成功
	 */
	bool GetBucketACL_Async(string &bucketName);
	/**
	 @brief 异步方法，判断指定的bucket是否存在
	 @param[in] bucketName string
	 @return bool类型值，用来判断函数是否成功
	 */
	bool IsBucketExist_Async(string &bucketName);
	/**
	 @brief 异步方法，罗列Bucket中的Object
	 @param[in] reuqest ListObjectsRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool ListObjects_Async(ListObjectsRequest & reuqest);
	
public:
	//同步
	/**
	 @brief 同步方法，上传Object，适合小文件上传，大文件上传请使用MultiPart相关接口
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @param[in] data char * 数据块指针
	 @param[in] dataLength long 数据块长度
	 @param[in] objectMetadata ObjectMetadata Object元数据
	 @param[out] result PutObjectResult
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE PutObject(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata,PutObjectResult &result);
	/**
	 @brief 同步方法，获取Object，适合小文件下载，大文件下载请使用FetchObject(string &bucketName,string &key,string & filePath)方法
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @param[out] object OSSObject
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE FetchObject(string &bucketName,string &key,OSSObject & object);
	/**
	 @brief 同步方法，获取Object，适合小文件下载，大文件下载请使用FetchObject(string &bucketName,string &key,string & filePath)方法
	 @param[in] request FetchObjectRequest
	 @param[out] object OSSObject
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE FetchObject(FetchObjectRequest &request,OSSObject & object);
	//大文件使用该方法，会分块写入，不会造成内存溢出
	/**
	 @brief 同步方法，获取Object并直接写到指定文件中，适合大文件下载，会分块写入，不会造成内存溢出
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @param[in] filePath string 写入的文件名称（需要全路径）
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE FetchObject(string &bucketName,string &key,string & filePath);
	//大文件使用该方法，会分块写入，不会造成内存溢出
	/**
	 @brief 同步方法，获取Object并直接写到指定文件中，适合大文件下载，会分块写入，不会造成内存溢出
	 @param[in] request FetchObjectRequest
	 @param[in] filePath string 写入的文件名称（需要全路径）
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE FetchObject(FetchObjectRequest &request,string & filePath);
	/**
	 @brief 同步方法，获取Object元数据
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @param[out] objectMetadata ObjectMetadata 
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE GetObjectMetadata(string &bucketName,string &key,ObjectMetadata &objectMetadata);
	/**
	 @brief 同步方法，拷贝Object
	 @param[in] request CopyObjectRequest
	 @param[out] result CopyObjectResult 
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE CopyObject(CopyObjectRequest & request,CopyObjectResult &result);
	/**
	 @brief 同步方法，删除Object
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE DeleteObject(string &bucketName,string &key);
	/**
	 @brief 同步方法，删除多个Object
	 @param[in] bucketName string
	 @param[in] objNames vector<string> Object名称数组
	 @param[in] isQuiet bool 是否静默删除，静默删除不返回任何相关信息，result为空
	 @param[out] result DeleteObjectsResult
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE DeleteMultipleObjects(string &bucketName,vector<string> &objNames, bool isQuiet,DeleteObjectsResult & result);
	//异步
	/**
	 @brief 异步方法，上传Object，适合小文件上传，大文件上传请使用MultiPart相关接口
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @param[in] data char * 数据块指针
	 @param[in] dataLength long 数据块长度
	 @param[in] objectMetadata ObjectMetadata Object元数据
	 @return bool类型值，用来判断函数是否成功
	 */
	bool PutObject_Async(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata);
	/**
	 @brief 异步方法，获取Object，适合小文件下载，大文件下载请使用FetchObject(string &bucketName,string &key,string & filePath)方法
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @return bool类型值，用来判断函数是否成功
	 */
	bool FetchObject_Async(string &bucketName,string &key);
	/**
	 @brief 异步方法，获取Object，适合小文件下载，大文件下载请使用FetchObject(string &bucketName,string &key,string & filePath)方法
	 @param[in] request FetchObjectRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool FetchObject_Async(FetchObjectRequest &request);
	//大文件使用该方法，会分块写入，不会造成内存溢出
	/**
	 @brief 异步方法，获取Object并直接写到指定文件中，适合大文件下载，会分块写入，不会造成内存溢出
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @param[in] filePath string 写入的文件名称（需要全路径）
	 @return bool类型值，用来判断函数是否成功
	 */
	bool FetchObject_Async(string &bucketName,string &key,string & filePath);	
	//大文件使用该方法，会分块写入，不会造成内存溢出
	/**
	 @brief 异步方法，获取Object并直接写到指定文件中，适合大文件下载，会分块写入，不会造成内存溢出,如果filePath错误，则不会发送请求
	 @param[in] request FetchObjectRequest
	 @param[in] filePath string 写入的文件名称（需要全路径）
	 @return bool类型值，用来判断函数是否成功
	 */
	bool FetchObject_Async(FetchObjectRequest &request,string & filePath);
	/**
	 @brief 异步方法，获取Object元数据
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @return bool类型值，用来判断函数是否成功
	 */
	bool GetObjectMetadata_Async(string &bucketName,string &key);
	/**
	 @brief 异步方法，拷贝Object
	 @param[in] request CopyObjectRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool CopyObject_Async(CopyObjectRequest & request);
	/**
	 @brief 异步方法，删除Object
	 @param[in] bucketName string
	 @param[in] key string Object名称
	 @return bool类型值，用来判断函数是否成功
	 */
	bool DeleteObject_Async(string &bucketName,string &key);
	/**
	 @brief 异步方法，删除多个Object
	 @param[in] bucketName string
	 @param[in] objNames vector<string> Object名称数组
	 @param[in] isQuiet bool 是否静默删除，静默删除不返回任何相关信息，result为空
	 @return bool类型值，用来判断函数是否成功
	 */
	bool DeleteMultipleObjects_Async(string &bucketName,vector<string> &objNames, bool isQuiet);
public:
	//同步调用
	/**
	 @brief 同步方法，多点上传之上传一部分
	 @param[in] uploadPartRequest UploadPartRequest
	 @param[out] result UploadPartResult
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE UploadPart(UploadPartRequest & uploadPartRequest,UploadPartResult & result);
	/**
	 @brief 同步方法，罗列上传的部分
	 @param[in] listPartsRequest ListPartsRequest
	 @param[out] result PartListing
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE ListParts(ListPartsRequest & listPartsRequest,PartListing &result);
	/**
	 @brief 同步方法，罗列已经初始化的上传请求
	 @param[in] listMultipartUploadsRequest ListMultipartUploadsRequest
	 @param[out] result MultipartUploadListing
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE ListMultipartUploads(ListMultipartUploadsRequest &listMultipartUploadsRequest,MultipartUploadListing &result);
	/**
	 @brief 同步方法，初始化上传请求
	 @param[in] initiateMultipartUploadRequest InitiateMultipartUploadRequest
	 @param[out] result InitiateMultipartUploadResult
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE InitiateMultipartUpload(InitiateMultipartUploadRequest & initiateMultipartUploadRequest,InitiateMultipartUploadResult &result);
	/**
	 @brief 同步方法，完成上传请求
	 @param[in] completeMultipartUploadRequest CompleteMultipartUpload
	 @param[out] result CompleteMultipartUploadResult
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE CompleteMultipartUpload(CompleteMultipartUploadRequest &completeMultipartUploadRequest,CompleteMultipartUploadResult &result);
	/**
	 @brief 同步方法，中断并清除上传请求
	 @param[in] abortMultipartUploadRequest AbortMultipartUploadRequest
	 @param[out] uploadId string 中断的请求ID
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE AbortMultipartUpload(AbortMultipartUploadRequest & abortMultipartUploadRequest,string& uploadId);
	//异步调用
	/**
	 @brief 异步方法，多点上传之上传一部分
	 @param[in] uploadPartRequest UploadPartRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool UploadPart_Async(UploadPartRequest & uploadPartRequest);
	/**
	 @brief 异步方法，罗列上传的部分
	 @param[in] listPartsRequest ListPartsRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool ListParts_Async(ListPartsRequest & listPartsRequest);
	/**
	 @brief 异步方法，罗列已经初始化的上传请求
	 @param[in] listMultipartUploadsRequest ListMultipartUploadsRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool ListMultipartUploads_Async(ListMultipartUploadsRequest &listMultipartUploadsRequest);
	/**
	 @brief 异步方法，初始化上传请求
	 @param[in] initiateMultipartUploadRequest InitiateMultipartUploadRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool InitiateMultipartUpload_Async(InitiateMultipartUploadRequest & initiateMultipartUploadRequest);
	/**
	 @brief 异步方法，完成上传请求
	 @param[in] completeMultipartUploadRequest CompleteMultipartUpload
	 @return bool类型值，用来判断函数是否成功
	 */
	bool CompleteMultipartUpload_Async(CompleteMultipartUploadRequest &completeMultipartUploadRequest);
	/**
	 @brief 异步方法，中断并清除上传请求
	 @param[in] abortMultipartUploadRequest AbortMultipartUploadRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool AbortMultipartUpload_Async(AbortMultipartUploadRequest & abortMultipartUploadRequest);
public:
	/**
	 @brief 同步方法，构造ObjectGroup
	 @param[in] postObjectGroupRequest PostObjectGroupRequest
	 @param[out] result PostObjectGroupResult 
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE PostObjectGroup(PostObjectGroupRequest &postObjectGroupRequest,PostObjectGroupResult & result);
	/**
	 @brief 同步方法，获取ObjectGroup的索引信息
	 @param[in] bucketName string
	 @param[in] key string
	 @param[out] result FetchObjectGroupIndexResult 
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE GetObjectGroupIndex(string &bucketName ,string &key,FetchObjectGroupIndexResult &result);
	/**
	 @brief 同步方法，GetObjectGroup 没有实现，请使用 GetObject 方法
	 @param[in] bucketName string
	 @param[in] key string
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE GetObjectGroup(string &bucketName ,string &key);
	/**
	 @brief 同步方法，DeleteObjectGroup 没有实现，请使用 DeleteObject 方法
	 @param[in] bucketName string
	 @param[in] key string
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE DeleteObjectGroup(string &bucketName ,string &key);
	/**
	 @brief 同步方法，GetObjectGroupMetadata没有实现，请使用 GetObjectMetadata 方法
	 @param[in] bucketName string
	 @param[in] key string
	 @return OSS_RESULTCODE类型值，用来判断函数是否成功以及返回错误码
	 */
	OSS_RESULTCODE GetObjectGroupMetadata(string &bucketName ,string &key,ObjectMetadata &objectMetadata);
	//异步调用
	/**
	 @brief 异步方法，构造ObjectGroup
	 @param[in] postObjectGroupRequest PostObjectGroupRequest
	 @return bool类型值，用来判断函数是否成功
	 */
	bool PostObjectGroup_Async(PostObjectGroupRequest &postObjectGroupRequest);
	/**
	 @brief 异步方法，获取ObjectGroup的索引信息
	 @param[in] bucketName string
	 @param[in] key string 
	 @return bool类型值，用来判断函数是否成功
	 */
	bool GetObjectGroupIndex_Async(string &bucketName ,string &key);
	/**
	 @brief 异步方法， GetObjectGroup_Async 没有实现，请使用 GetObject_Async 方法
	 @param[in] bucketName string 
	 @param[in] key string  
	 @return bool类型值，用来判断函数是否成功
	 */
	bool GetObjectGroup_Async(string &bucketName ,string &key);
	/**
	 @brief 异步方法，DeleteObjectGroup_Async 没有实现，请使用 DeleteObject_Async 方法
	 @param[in] bucketName string
	 @param[in] key string 
	  @return bool类型值，用来判断函数是否成功
	 */
	bool DeleteObjectGroup_Async(string &bucketName ,string &key);

	/**
	 @brief 异步方法，GetObjectGroupMetadata_Async没有实现，请使用 GetObjectMetadata_Async 方法
	 @param[in] bucketName string
	 @param[in] key string 
	  @return bool类型值，用来判断函数是否成功
	 */
	bool GetObjectGroupMetadata_Async(string &bucketName,string &key);
public:
	OSSClientCallback *delegate;
private:
	//Bucket Op
	virtual void OnCreateBucketComplete(OSSBucketOperation * bucketOperation,Bucket &bucket);
	virtual void OnCreateBucketFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code);
	virtual void OnDeleteBucketComplete(OSSBucketOperation * bucketOperation,string &bucketName);
	virtual void OnDeleteBucketFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code);
	virtual void OnListBucketsComplete(OSSBucketOperation * bucketOperation,Buckets &buckets);
	virtual void OnListBucketsFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code);
	virtual void OnSetBucketACLComplete(OSSBucketOperation * bucketOperation);
	virtual void OnSetBucketACLFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code);
	virtual void OnGetBucketACLComplete(OSSBucketOperation * bucketOperation,CannedAccessControlList &aclList);
	virtual void OnGetBucketACLFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code);
	virtual void OnIsBucketExistComplete(OSSBucketOperation * bucketOperation,bool &isExist);
	virtual void OnIsBucketExistFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code);
	virtual void OnListObjectsComplete(OSSBucketOperation * bucketOperation,ObjectListing &objectListing);
	virtual void OnListObjectsFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code);
	virtual void OnNetworkFailed(OSSBucketOperation * bucketOperation,OSS_RESULTCODE code);

private:
	//Object Op
	virtual void OnPutObjectComplete(OSSObjectOperation * objectOperation,PutObjectResult &result);
	virtual void OnPutObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code);
	virtual void OnFetchObjectComplete(OSSObjectOperation * objectOperation,OSSObject &object);
	virtual void OnFetchObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code);
	virtual void OnFetchObjectToFileComplete(OSSObjectOperation * objectOperation,string &fileName);
	virtual void OnFetchObjectToFileFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code);
	virtual void OnGetObjectMetadataComplete(OSSObjectOperation * objectOperation,ObjectMetadata &objectMetadata);
	virtual void OnGetObjectMetadataFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code);
	virtual void OnCopyObjectComplete(OSSObjectOperation * objectOperation,CopyObjectResult &result);
	virtual void OnCopyObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code);
	virtual void OnDeleteObjectComplete(OSSObjectOperation * objectOperation);
	virtual void OnDeleteObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code);
	virtual void OnDeleteMultipleObjectsComplete(OSSObjectOperation * objectOperation,DeleteObjectsResult &result);
	virtual void OnDeleteMultipleObjectsFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code);	
	virtual void OnNetworkFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code);

private:
	//MutiPart Op
	virtual void OnUploadPartComplete(OSSMultipartOperation * multipartOperation,UploadPartResult &result);
	virtual void OnUploadPartFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code);	
	virtual void OnListPartsComplete(OSSMultipartOperation * multipartOperation,PartListing &result);
	virtual void OnListPartsFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code);
	virtual void OnListMultipartUploadsComplete(OSSMultipartOperation * multipartOperation,MultipartUploadListing &result);
	virtual void OnListMultipartUploadsFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code);
	virtual void OnInitiateMultipartUploadComplete(OSSMultipartOperation * multipartOperation,InitiateMultipartUploadResult &result);
	virtual void OnInitiateMultipartUploadFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code);
	virtual void OnCompleteMultipartUploadComplete(OSSMultipartOperation * multipartOperation,CompleteMultipartUploadResult &result);
	virtual void OnCompleteMultipartUploadFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code);
	virtual void OnAbortMultipartUploadComplete(OSSMultipartOperation * multipartOperation,string &puloadId);
	virtual void OnAbortMultipartUploadFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code);
	virtual void OnNetworkFailed(OSSMultipartOperation * multipartOperation,OSS_RESULTCODE code);
	
private:
	//ObjectGroup Op
	virtual void OnPostObjectGroupComplete(OSSObjectGroupOperation * objectGroupOperation,PostObjectGroupResult &result);
	virtual void OnPostObjectGroupFailed(OSSObjectGroupOperation * objectGroupOperation,OSS_RESULTCODE code);
	virtual void OnGetObjectGroupIndexComplete(OSSObjectGroupOperation * objectGroupOperation,FetchObjectGroupIndexResult &result);
	virtual void OnGetObjectGroupIndexFailed(OSSObjectGroupOperation * objectGroupOperation,OSS_RESULTCODE code);
	virtual void OnNetworkFailed(OSSObjectGroupOperation * objectGroupOperation,OSS_RESULTCODE code);
};
}

