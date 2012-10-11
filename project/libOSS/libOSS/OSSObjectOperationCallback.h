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
class OSSObjectOperation;
class ObjectMetadata;
class PutObjectResult;
class OSSObject;
class CopyObjectResult;
class DeleteObjectsResult;
/**
@class OSSObjectOperationCallback
@brief 抽象基类，Object相关操作回调函数定义
*/
class OSSDLL_API OSSObjectOperationCallback
{
public:
	virtual  void OnPutObjectComplete(OSSObjectOperation * objectOperation,PutObjectResult &result) = 0;
	virtual  void OnPutObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnFetchObjectComplete(OSSObjectOperation * objectOperation,OSSObject &object) = 0;
	virtual  void OnFetchObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnFetchObjectToFileComplete(OSSObjectOperation * objectOperation,string &fileName) = 0;
	virtual  void OnFetchObjectToFileFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnGetObjectMetadataComplete(OSSObjectOperation * objectOperation,ObjectMetadata &objectMetadata) = 0;
	virtual  void OnGetObjectMetadataFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnCopyObjectComplete(OSSObjectOperation * objectOperation,CopyObjectResult &result) = 0;
	virtual  void OnCopyObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnDeleteObjectComplete(OSSObjectOperation * objectOperation) = 0;
	virtual  void OnDeleteObjectFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code) = 0;

	virtual  void OnDeleteMultipleObjectsComplete(OSSObjectOperation * objectOperation,DeleteObjectsResult &result) = 0;
	virtual  void OnDeleteMultipleObjectsFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code) = 0;
	
	virtual  void OnNetworkFailed(OSSObjectOperation * objectOperation,OSS_RESULTCODE code) = 0;
};
}