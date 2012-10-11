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
OSS SDK for C++ ʹ��˵�� \n
1 ��� \n
Aliyun OSS C++ SDKʹ��c++ʵ����Aliyun OSS�ṩ�Ĺ��ܣ���Ҫ����Bucket�Ĵ�����ɾ���������Object�Ĵ�����ɾ������Լ�����ϴ��ȹ��ܣ�����OSS�ṩ�ķ�����ο�OSS API˵���ĵ���\n
2 ��Ҫ����\n
Aliyun OSS C++ SDK��Ҫ����Դ���루BSDЭ�鿪Դ����˵���ĵ���ʾ�����̡������ĵ��ȡ�\n
��SDK��������Ϊvs2012���ṩ��vs2012�Ĺ����ļ���Ŀǰֻ֧��windowsƽ̨���ݲ�֧�ֿ�ƽ̨ʹ�á�\n
��SDK�ṩͷ�ļ��Ͷ�̬���lib�ļ����ڿ�����\n
3 ��������\n
��SDKʹ�õ��ĵ��������������²��֣�\n
Libcurl\n
Xmlparser\n
4 ʹ�ò���\n
4.1 �½�vs2012 ���̣���vc includeĿ¼��ΪSDKĿ¼�µ�includeĿ¼��LibraryĿ¼��ΪSDKĿ¼�µ�binĿ¼��\n
4.2 ����OutputĿ¼��ΪSDKĿ¼�µ�binĿ¼��\n
4.3 ��Linker������Input�����libcurl.lib��libOSS.lib\n
4.4 �ڴ����а���ͷ�ļ�OSSClient.h\n
#include "OSSClient.h"\n
4.5 ����OSSClient���󣬲�ʹ��accessID��accessKey��ʼ����\n
OSS::OSSClient *_ptClient = new  OSSClient(aID,akey,config);\n
4.6 ʹ��OSSClient��OSS���������OSS�����ṩ���������Ĳ�������������Bucket��Object��MultiPart��ObjectGroup��OSSClient ���ֱ��ṩ��ͬ�����첽�ķ�ʽ���е��á�\n
4.6.1 ͬ����ʽ����\n
ֱ��ʹ��OSSClient������ü��ɡ�\n
_ptClient->ListBuckets(buckets);\n
4.6.2 �첽��ʽ����\n
�첽��ʽ��web�������������ʽ�������󷵻ص�ʱ����Ӧ�����Ϣ��\n
1��ʹ���첽��ʽ����Ҫʵ�ִ����࣬�ô��������̳�OSS::OSSClientCallback ���������࣬��ʵ�ֳ�������ж���Ļص�������\n
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
2�� ����ص�������\n
OSSClientTest *ptOSSClientTest = new OSSClientTest();\n
3�����������ָ�븳��OSSClient ��delegate����\n
 _ptClient->delegate =(OSSClientCallback *)ptOSSClientTest;\n
4�� ������_Async��β����ط�����OSS�������\n
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
@brief OSS �����Ҫ�����࣬�ṩ��ͬ�����첽�ķ�ʽ��OSS������в���
* ͬ���ķ�ʽ��ֱ�ӷ��ؽ��
* �첽�ķ�ʽ��Ҫʹ���߼̳в�ʵ��OSSClientCallback���е���ػص�����������delegate����Ϊ�����ָ�롣�첽�ķ�ʽ�����������̡�
*/
class OSSDLL_API OSSClient: public OSSBucketOperationCallback,
	public OSSObjectOperationCallback,public OSSMultipartOperationCallback,public OSSObjectGroupOperationCallback
{
public:
	/**
	 @brief ���캯����ʹ��accessID ��accessKey ���г�ʼ��
	 @param[in] accessID string
	 @param[in] accessKey string
	 */
	OSSClient(string &accessID,string &accessKey);
	/**
	 @brief ���캯����ʹ��accessID ��accessKey�Ϳͻ������ò������г�ʼ��
	 @param[in] accessID string
	 @param[in] accessKey string
	 @param[in] config ClientConfiguration
	 */
	OSSClient(string &accessID,string &accessKey,ClientConfiguration &config);
	/**
	 @brief ���캯����ʹ��endPoint��accessID ��accessKey���г�ʼ����endPoint Ĭ��Ϊ"http://storage.aliyun.com"
	 @param[in] endPoint string
	 @param[in] accessID string
	 @param[in] accessKey string
	 */
	OSSClient(string &endPoint,string &accessID,string &accessKey);
	/**
	 @brief ���캯����ʹ��endPoint��accessID ��accessKey�Ϳͻ������ò��������г�ʼ����endPoint Ĭ��Ϊ"http://storage.aliyun.com"
	 @param[in] endPoint string
	 @param[in] accessID string
	 @param[in] accessKey string
	 @param[in] config ClientConfiguration
	 */
	OSSClient(string &endPoint,string &accessID,string &accessKey,ClientConfiguration &config);
	/**
	 @brief ��������
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
	//ͬ��
	/**
	 @brief ͬ������������bucket
	 @param[in] bucketName string
	 @param[out] bucket string
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE CreateBucket(string &bucketName,Bucket & bucket);
	/**
	 @brief ͬ��������ɾ��bucket
	 @param[in] bucketName string
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE DeleteBucket(string &bucketName);
	/**
	 @brief ͬ���������������е�bucket
	 @param[out] buckets Buckets
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE ListBuckets(Buckets &buckets);
	/**
	 @brief ͬ������������Bucket�ķ��ʿ���Ȩ��
	 @param[in] bucketName string
	 @param[in] aclList CannedAccessControlList
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE SetBucketACL(string &bucketName,CannedAccessControlList &aclList);
	/**
	 @brief ͬ�����������Bucket�ķ��ʿ���Ȩ��
	 @param[in] bucketName string
	 @param[out] aclList CannedAccessControlList
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE GetBucketACL(string &bucketName,CannedAccessControlList &aclList);
	/**
	 @brief ͬ���������ж�ָ����bucket�Ƿ����
	 @param[in] bucketName string
	 @param[out] isExist bool
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE IsBucketExist(string &bucketName,bool &isExist);
	/**
	 @brief ͬ������������Bucket�е�Object
	 @param[in] reuqest ListObjectsRequest
	 @param[out] objectListing ObjectListing
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE ListObjects(ListObjectsRequest & reuqest,ObjectListing &objectListing);
	//�첽
	/**
	 @brief ͬ������������bucket
	 @param[in] bucketName string
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool CreateBucket_Async(string &bucketName);
	/**
	 @brief �첽������ɾ��bucket
	 @param[in] bucketName string
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool DeleteBucket_Async(string &bucketName);
	/**
	 @brief �첽�������������е�bucket
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool ListBuckets_Async();
	/**
	 @brief �첽����������Bucket�ķ��ʿ���Ȩ��
	 @param[in] bucketName string
	 @param[in] aclList CannedAccessControlList
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool SetBucketACL_Async(string &bucketName,CannedAccessControlList &aclList);
	/**
	 @brief �첽���������Bucket�ķ��ʿ���Ȩ��
	 @param[in] bucketName string
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool GetBucketACL_Async(string &bucketName);
	/**
	 @brief �첽�������ж�ָ����bucket�Ƿ����
	 @param[in] bucketName string
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool IsBucketExist_Async(string &bucketName);
	/**
	 @brief �첽����������Bucket�е�Object
	 @param[in] reuqest ListObjectsRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool ListObjects_Async(ListObjectsRequest & reuqest);
	
public:
	//ͬ��
	/**
	 @brief ͬ���������ϴ�Object���ʺ�С�ļ��ϴ������ļ��ϴ���ʹ��MultiPart��ؽӿ�
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @param[in] data char * ���ݿ�ָ��
	 @param[in] dataLength long ���ݿ鳤��
	 @param[in] objectMetadata ObjectMetadata ObjectԪ����
	 @param[out] result PutObjectResult
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE PutObject(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata,PutObjectResult &result);
	/**
	 @brief ͬ����������ȡObject���ʺ�С�ļ����أ����ļ�������ʹ��FetchObject(string &bucketName,string &key,string & filePath)����
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @param[out] object OSSObject
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE FetchObject(string &bucketName,string &key,OSSObject & object);
	/**
	 @brief ͬ����������ȡObject���ʺ�С�ļ����أ����ļ�������ʹ��FetchObject(string &bucketName,string &key,string & filePath)����
	 @param[in] request FetchObjectRequest
	 @param[out] object OSSObject
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE FetchObject(FetchObjectRequest &request,OSSObject & object);
	//���ļ�ʹ�ø÷�������ֿ�д�룬��������ڴ����
	/**
	 @brief ͬ����������ȡObject��ֱ��д��ָ���ļ��У��ʺϴ��ļ����أ���ֿ�д�룬��������ڴ����
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @param[in] filePath string д����ļ����ƣ���Ҫȫ·����
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE FetchObject(string &bucketName,string &key,string & filePath);
	//���ļ�ʹ�ø÷�������ֿ�д�룬��������ڴ����
	/**
	 @brief ͬ����������ȡObject��ֱ��д��ָ���ļ��У��ʺϴ��ļ����أ���ֿ�д�룬��������ڴ����
	 @param[in] request FetchObjectRequest
	 @param[in] filePath string д����ļ����ƣ���Ҫȫ·����
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE FetchObject(FetchObjectRequest &request,string & filePath);
	/**
	 @brief ͬ����������ȡObjectԪ����
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @param[out] objectMetadata ObjectMetadata 
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE GetObjectMetadata(string &bucketName,string &key,ObjectMetadata &objectMetadata);
	/**
	 @brief ͬ������������Object
	 @param[in] request CopyObjectRequest
	 @param[out] result CopyObjectResult 
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE CopyObject(CopyObjectRequest & request,CopyObjectResult &result);
	/**
	 @brief ͬ��������ɾ��Object
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE DeleteObject(string &bucketName,string &key);
	/**
	 @brief ͬ��������ɾ�����Object
	 @param[in] bucketName string
	 @param[in] objNames vector<string> Object��������
	 @param[in] isQuiet bool �Ƿ�Ĭɾ������Ĭɾ���������κ������Ϣ��resultΪ��
	 @param[out] result DeleteObjectsResult
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE DeleteMultipleObjects(string &bucketName,vector<string> &objNames, bool isQuiet,DeleteObjectsResult & result);
	//�첽
	/**
	 @brief �첽�������ϴ�Object���ʺ�С�ļ��ϴ������ļ��ϴ���ʹ��MultiPart��ؽӿ�
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @param[in] data char * ���ݿ�ָ��
	 @param[in] dataLength long ���ݿ鳤��
	 @param[in] objectMetadata ObjectMetadata ObjectԪ����
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool PutObject_Async(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata);
	/**
	 @brief �첽��������ȡObject���ʺ�С�ļ����أ����ļ�������ʹ��FetchObject(string &bucketName,string &key,string & filePath)����
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool FetchObject_Async(string &bucketName,string &key);
	/**
	 @brief �첽��������ȡObject���ʺ�С�ļ����أ����ļ�������ʹ��FetchObject(string &bucketName,string &key,string & filePath)����
	 @param[in] request FetchObjectRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool FetchObject_Async(FetchObjectRequest &request);
	//���ļ�ʹ�ø÷�������ֿ�д�룬��������ڴ����
	/**
	 @brief �첽��������ȡObject��ֱ��д��ָ���ļ��У��ʺϴ��ļ����أ���ֿ�д�룬��������ڴ����
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @param[in] filePath string д����ļ����ƣ���Ҫȫ·����
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool FetchObject_Async(string &bucketName,string &key,string & filePath);	
	//���ļ�ʹ�ø÷�������ֿ�д�룬��������ڴ����
	/**
	 @brief �첽��������ȡObject��ֱ��д��ָ���ļ��У��ʺϴ��ļ����أ���ֿ�д�룬��������ڴ����,���filePath�����򲻻ᷢ������
	 @param[in] request FetchObjectRequest
	 @param[in] filePath string д����ļ����ƣ���Ҫȫ·����
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool FetchObject_Async(FetchObjectRequest &request,string & filePath);
	/**
	 @brief �첽��������ȡObjectԪ����
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool GetObjectMetadata_Async(string &bucketName,string &key);
	/**
	 @brief �첽����������Object
	 @param[in] request CopyObjectRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool CopyObject_Async(CopyObjectRequest & request);
	/**
	 @brief �첽������ɾ��Object
	 @param[in] bucketName string
	 @param[in] key string Object����
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool DeleteObject_Async(string &bucketName,string &key);
	/**
	 @brief �첽������ɾ�����Object
	 @param[in] bucketName string
	 @param[in] objNames vector<string> Object��������
	 @param[in] isQuiet bool �Ƿ�Ĭɾ������Ĭɾ���������κ������Ϣ��resultΪ��
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool DeleteMultipleObjects_Async(string &bucketName,vector<string> &objNames, bool isQuiet);
public:
	//ͬ������
	/**
	 @brief ͬ������������ϴ�֮�ϴ�һ����
	 @param[in] uploadPartRequest UploadPartRequest
	 @param[out] result UploadPartResult
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE UploadPart(UploadPartRequest & uploadPartRequest,UploadPartResult & result);
	/**
	 @brief ͬ�������������ϴ��Ĳ���
	 @param[in] listPartsRequest ListPartsRequest
	 @param[out] result PartListing
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE ListParts(ListPartsRequest & listPartsRequest,PartListing &result);
	/**
	 @brief ͬ�������������Ѿ���ʼ�����ϴ�����
	 @param[in] listMultipartUploadsRequest ListMultipartUploadsRequest
	 @param[out] result MultipartUploadListing
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE ListMultipartUploads(ListMultipartUploadsRequest &listMultipartUploadsRequest,MultipartUploadListing &result);
	/**
	 @brief ͬ����������ʼ���ϴ�����
	 @param[in] initiateMultipartUploadRequest InitiateMultipartUploadRequest
	 @param[out] result InitiateMultipartUploadResult
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE InitiateMultipartUpload(InitiateMultipartUploadRequest & initiateMultipartUploadRequest,InitiateMultipartUploadResult &result);
	/**
	 @brief ͬ������������ϴ�����
	 @param[in] completeMultipartUploadRequest CompleteMultipartUpload
	 @param[out] result CompleteMultipartUploadResult
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE CompleteMultipartUpload(CompleteMultipartUploadRequest &completeMultipartUploadRequest,CompleteMultipartUploadResult &result);
	/**
	 @brief ͬ���������жϲ�����ϴ�����
	 @param[in] abortMultipartUploadRequest AbortMultipartUploadRequest
	 @param[out] uploadId string �жϵ�����ID
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE AbortMultipartUpload(AbortMultipartUploadRequest & abortMultipartUploadRequest,string& uploadId);
	//�첽����
	/**
	 @brief �첽����������ϴ�֮�ϴ�һ����
	 @param[in] uploadPartRequest UploadPartRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool UploadPart_Async(UploadPartRequest & uploadPartRequest);
	/**
	 @brief �첽�����������ϴ��Ĳ���
	 @param[in] listPartsRequest ListPartsRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool ListParts_Async(ListPartsRequest & listPartsRequest);
	/**
	 @brief �첽�����������Ѿ���ʼ�����ϴ�����
	 @param[in] listMultipartUploadsRequest ListMultipartUploadsRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool ListMultipartUploads_Async(ListMultipartUploadsRequest &listMultipartUploadsRequest);
	/**
	 @brief �첽��������ʼ���ϴ�����
	 @param[in] initiateMultipartUploadRequest InitiateMultipartUploadRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool InitiateMultipartUpload_Async(InitiateMultipartUploadRequest & initiateMultipartUploadRequest);
	/**
	 @brief �첽����������ϴ�����
	 @param[in] completeMultipartUploadRequest CompleteMultipartUpload
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool CompleteMultipartUpload_Async(CompleteMultipartUploadRequest &completeMultipartUploadRequest);
	/**
	 @brief �첽�������жϲ�����ϴ�����
	 @param[in] abortMultipartUploadRequest AbortMultipartUploadRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool AbortMultipartUpload_Async(AbortMultipartUploadRequest & abortMultipartUploadRequest);
public:
	/**
	 @brief ͬ������������ObjectGroup
	 @param[in] postObjectGroupRequest PostObjectGroupRequest
	 @param[out] result PostObjectGroupResult 
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE PostObjectGroup(PostObjectGroupRequest &postObjectGroupRequest,PostObjectGroupResult & result);
	/**
	 @brief ͬ����������ȡObjectGroup��������Ϣ
	 @param[in] bucketName string
	 @param[in] key string
	 @param[out] result FetchObjectGroupIndexResult 
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE GetObjectGroupIndex(string &bucketName ,string &key,FetchObjectGroupIndexResult &result);
	/**
	 @brief ͬ��������GetObjectGroup û��ʵ�֣���ʹ�� GetObject ����
	 @param[in] bucketName string
	 @param[in] key string
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE GetObjectGroup(string &bucketName ,string &key);
	/**
	 @brief ͬ��������DeleteObjectGroup û��ʵ�֣���ʹ�� DeleteObject ����
	 @param[in] bucketName string
	 @param[in] key string
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE DeleteObjectGroup(string &bucketName ,string &key);
	/**
	 @brief ͬ��������GetObjectGroupMetadataû��ʵ�֣���ʹ�� GetObjectMetadata ����
	 @param[in] bucketName string
	 @param[in] key string
	 @return OSS_RESULTCODE����ֵ�������жϺ����Ƿ�ɹ��Լ����ش�����
	 */
	OSS_RESULTCODE GetObjectGroupMetadata(string &bucketName ,string &key,ObjectMetadata &objectMetadata);
	//�첽����
	/**
	 @brief �첽����������ObjectGroup
	 @param[in] postObjectGroupRequest PostObjectGroupRequest
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool PostObjectGroup_Async(PostObjectGroupRequest &postObjectGroupRequest);
	/**
	 @brief �첽��������ȡObjectGroup��������Ϣ
	 @param[in] bucketName string
	 @param[in] key string 
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool GetObjectGroupIndex_Async(string &bucketName ,string &key);
	/**
	 @brief �첽������ GetObjectGroup_Async û��ʵ�֣���ʹ�� GetObject_Async ����
	 @param[in] bucketName string 
	 @param[in] key string  
	 @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool GetObjectGroup_Async(string &bucketName ,string &key);
	/**
	 @brief �첽������DeleteObjectGroup_Async û��ʵ�֣���ʹ�� DeleteObject_Async ����
	 @param[in] bucketName string
	 @param[in] key string 
	  @return bool����ֵ�������жϺ����Ƿ�ɹ�
	 */
	bool DeleteObjectGroup_Async(string &bucketName ,string &key);

	/**
	 @brief �첽������GetObjectGroupMetadata_Asyncû��ʵ�֣���ʹ�� GetObjectMetadata_Async ����
	 @param[in] bucketName string
	 @param[in] key string 
	  @return bool����ֵ�������жϺ����Ƿ�ɹ�
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

