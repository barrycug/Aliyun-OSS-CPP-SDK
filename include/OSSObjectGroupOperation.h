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
#include <string>
#include "PostObjectGroupRequest.h"
#include "PostObjectGroupResult.h"
#include "FetchObjectGroupIndexResult.h"
#include "ObjectGroupPartETag.h"
#include "OSSObjectGroupOperationCallback.h"
using namespace std;
namespace OSS
{
/**
@class OSSObjectGroupOperation
@brief ObjectGroup相关操作类
*/
class OSSDLL_API OSSObjectGroupOperation :
	public OSSOperation
{
public:
	OSSObjectGroupOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client);
	~OSSObjectGroupOperation(void);
public:
//同步调用
OSS_RESULTCODE PostObjectGroup(PostObjectGroupRequest &postObjectGroupRequest,PostObjectGroupResult & reault);
OSS_RESULTCODE GetObjectGroupIndex(string &bucketName ,string &key,FetchObjectGroupIndexResult &result);
/**
 GetObjectGroup 没有实现，请使用 GetObject 方法
 @param bucketName string
 @param key string
 */
OSS_RESULTCODE GetObjectGroup(string &bucketName ,string &key);
/**
 DeleteObjectGroup 没有实现，请使用 DeleteObject 方法
 @param bucketName string
 @param key string
 */
OSS_RESULTCODE DeleteObjectGroup(string &bucketName ,string &key);
/**
 GetObjectGroupMetadata没有实现，请使用 GetObjectMetadata 方法
 @param bucketName string
 @param key string
 */
OSS_RESULTCODE GetObjectGroupMetadata(string &bucketName ,string &key,ObjectMetadata &objectMetadata);
//异步调用
bool PostObjectGroup_Async(PostObjectGroupRequest &postObjectGroupRequest);
bool GetObjectGroupIndex_Async(string &bucketName ,string &key);
/**
 GetObjectGroup_Async 没有实现，请使用 GetObject_Async 方法
 @param bucketName string in
 @param key string in 
 */
bool GetObjectGroup_Async(string &bucketName ,string &key);
/**
 DeleteObjectGroup_Async 没有实现，请使用 DeleteObject_Async 方法
 @param bucketName string in
 @param key string in
 */
bool DeleteObjectGroup_Async(string &bucketName ,string &key);

/**
 GetObjectGroupMetadata_Async没有实现，请使用 GetObjectMetadata_Async 方法
 @param bucketName string in
 @param key string in
 */
bool GetObjectGroupMetadata_Async(string &bucketName,string &key);
public:
	OSSObjectGroupOperationCallback *delegate;
private:
	ResponseMessage invoke(HttpMethod httpMethod,string &bucketName,string &objName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo);
	bool invoke_Async(HttpMethod httpMethod,string &bucketName,string &objName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo);

public:
	//
	void serviceClientRequestFinished(DefaultServiceClient*defaultServiceClient,ResponseMessage &responseMessage);
	void serviceClientRequestFailed(DefaultServiceClient*defaultServiceClient, ResponseMessage &responseMessage);
private:
	string MakePostObjectGroupXML(vector<ObjectGroupPartETag> &objectGroupPartETags);
};
}

