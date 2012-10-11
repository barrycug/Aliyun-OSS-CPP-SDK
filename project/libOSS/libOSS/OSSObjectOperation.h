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
#include "ObjectMetadata.h"
#include "CopyObjectRequest.h"
#include "PutObjectResult.h"
#include "OSSObject.h"
#include "CopyObjectResult.h"
#include "DeleteObjectsResult.h"
#include "FetchObjectRequest.h"
#include "OSSObjectOperationCallback.h"
#include<vector>
using namespace std;
namespace OSS
{
/**
@class OSSObjectOperation
@brief Object相关操作
*/
class OSSDLL_API OSSObjectOperation :
	public OSSOperation
{
public:
	OSSObjectOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client);
	~OSSObjectOperation(void);
public:
	//同步
	OSS_RESULTCODE PutObject(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata,PutObjectResult &result);
	OSS_RESULTCODE FetchObject(string &bucketName,string &key,OSSObject & object);
	OSS_RESULTCODE FetchObject(FetchObjectRequest &request,OSSObject & object);
	//大文件请使用该方法
	OSS_RESULTCODE FetchObject(string &bucketName,string &key,string &filePath);
	OSS_RESULTCODE FetchObject(FetchObjectRequest &request,string &filePath);
	OSS_RESULTCODE GetObjectMetadata(string &bucketName,string &key,ObjectMetadata &objectMetadata);
	OSS_RESULTCODE CopyObject(CopyObjectRequest & request,CopyObjectResult &result);
	OSS_RESULTCODE DeleteObject(string &bucketName,string &key);
	OSS_RESULTCODE DeleteMultipleObjects(string &bucketName,vector<string> &objNames, bool isQuiet,DeleteObjectsResult & result);
	//异步
	bool PutObject_Async(string &bucketName,string &key,char * data,long dataLength,ObjectMetadata &objectMetadata);
	bool FetchObject_Async(string &bucketName,string &key);
	bool FetchObject_Async(FetchObjectRequest &request);
	//大文件请使用该方法
	bool FetchObject_Async(string &bucketName,string &key,string &filePath);
	bool FetchObject_Async(FetchObjectRequest &request,string &filePath);
	bool GetObjectMetadata_Async(string &bucketName,string &key);
	bool CopyObject_Async(CopyObjectRequest & request);
	bool DeleteObject_Async(string &bucketName,string &key);
	bool DeleteMultipleObjects_Async(string &bucketName,vector<string> &objNames, bool isQuiet);
private:
	ResponseMessage invoke(HttpMethod httpMethod,string &bucketName,string &objectName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo);
	bool invoke_Async(HttpMethod httpMethod,string &bucketName,string &objectName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo);
public:
	OSSObjectOperationCallback * delegate;
public:
	void serviceClientRequestFinished(DefaultServiceClient*defaultServiceClient,ResponseMessage &responseMessage);
	void serviceClientRequestFailed(DefaultServiceClient*defaultServiceClient, ResponseMessage &responseMessage);
private:
	string joinETag(vector<string> &arrayList);
	void populateCopyObjectHeaders(CopyObjectRequest&copyObjectRequest ,map<string,string>&headers);
	string makeDeleteObjectsXMLContent(vector<string> &objectNames,bool isQuiet);
};
}
