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
#include <string>
#include "UploadPartRequest.h"
#include "ListPartsRequest.h"
#include "ListMultipartUploadsRequest.h"
#include "InitiateMultipartUploadRequest.h"
#include "CompleteMultipartUploadRequest.h"
#include "AbortMultipartUploadRequest.h"
#include "UploadPartResult.h"
#include "PartListing.h"
#include "MultipartUploadListing.h"
#include "InitiateMultipartUploadResult.h"
#include "CompleteMultipartUploadResult.h"
#include "OSSMultipartOperationCallback.h"
using namespace std;
namespace OSS
{
/**
@class OSSMultipartOperation
@brief 多点上传相关操作
*/
class OSSDLL_API OSSMultipartOperation :
	public OSSOperation
{
public:
	OSSMultipartOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client);
	~OSSMultipartOperation(void);
public:
	//同步调用
	OSS_RESULTCODE UploadPart(UploadPartRequest & uploadPartRequest,UploadPartResult & result);
	OSS_RESULTCODE ListParts(ListPartsRequest & listPartsRequest,PartListing &result);
	OSS_RESULTCODE ListMultipartUploads(ListMultipartUploadsRequest &listMultipartUploadsRequest,MultipartUploadListing &result);
	OSS_RESULTCODE InitiateMultipartUpload(InitiateMultipartUploadRequest & initiateMultipartUploadRequest,InitiateMultipartUploadResult &result);
	OSS_RESULTCODE CompleteMultipartUpload(CompleteMultipartUploadRequest &completeMultipartUploadRequest,CompleteMultipartUploadResult &result);
	OSS_RESULTCODE AbortMultipartUpload(AbortMultipartUploadRequest & abortMultipartUploadRequest,string& uploadId);
	//异步调用
	bool UploadPart_Async(UploadPartRequest & uploadPartRequest);
	bool ListParts_Async(ListPartsRequest & listPartsRequest);
	bool ListMultipartUploads_Async(ListMultipartUploadsRequest &listMultipartUploadsRequest);
	bool InitiateMultipartUpload_Async(InitiateMultipartUploadRequest & initiateMultipartUploadRequest);
	bool CompleteMultipartUpload_Async(CompleteMultipartUploadRequest &completeMultipartUploadRequest);
	bool AbortMultipartUpload_Async(AbortMultipartUploadRequest & abortMultipartUploadRequest);
public:
	OSSMultipartOperationCallback * delegate;
private:
	ResponseMessage invoke(HttpMethod httpMethod,string &bucketName,string &objName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo);
	bool invoke_Async(HttpMethod httpMethod,string &bucketName,string &objName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo);

public:
	//
	void serviceClientRequestFinished(DefaultServiceClient*defaultServiceClient,ResponseMessage &responseMessage);
	void serviceClientRequestFailed(DefaultServiceClient*defaultServiceClient, ResponseMessage &responseMessage);
private:
	string  buildMultipartRequestXml(vector<PartETag> &partETags);
};
}

