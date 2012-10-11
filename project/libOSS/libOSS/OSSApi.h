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
#pragma once
#include <string>

enum  HttpMethod
{
	HttpMethod_GET,
	HttpMethod_POST,
	HttpMethod_HEAD,
	HttpMethod_PUT,
	HttpMethod_DELETE
};
enum  Chartset
{
	Chartset_ASCII,
	Chartset_UTF8,
	Chartset_ISO_8859_1
};
enum  CannedAclType
{
	CannedAclType_Private,
	CannedAclType_PublicRead,
	CannedAclType_PublicReadWrite
};

enum HTTP_RESULTCODE
{
	HTTPRESULT_OK   = 0,		///<  成功	
	HTTPRESULT_TIMEOUT,         ///<  请求超时
	HTTPRESULT_CANTRESOLVE,     ///<  不能解析地址
	HTTPRESULT_CANTCONNECT,     ///<  不能连接
	HTTPRESULT_ERROR,           ///<  HTTP请求的数据错误 
	HTTPRESULT_TOOLAGRE,        ///<  返回的数据量太大
	HTTPRESULT_FAIL,		    ///<  失败
	HTTPRESULT_OPITON_ERR		///类型错误，无法生成有效url
};
enum OSS_RESULTCODE
{
    OSS_RESULTCODE_OK = 0,
	OSS_RESULTCODE_INVALID=4999,
    OSS_RESULTCODE_ACCESS_DENIED = 5000,
    OSS_RESULTCODE_BUCKES_ALREADY_EXISTS=5001,
    OSS_RESULTCODE_BUCKETS_NOT_EMPTY  =   5002,
    OSS_RESULTCODE_FILE_GROUP_TOO_LARGE =5003,
    OSS_RESULTCODE_FILE_PART_STALE =5004,
    OSS_RESULTCODE_INVALID_ARGUMENT= 5005,
    OSS_RESULTCODE_INVALID_ACCESS_KEY_ID= 5006,
    OSS_RESULTCODE_INVALID_BUCKET_NAME =5007,
    OSS_RESULTCODE_INVALID_OBJECT_NAME =5008,
    OSS_RESULTCODE_INVALID_PART = 5009,
    OSS_RESULTCODE_INVALID_PART_ORDER = 5010,
    OSS_RESULTCODE_INTERNAL_ERROR = 50011,
    OSS_RESULTCODE_MISSING_CONTENT_LENGTH = 5012,
    OSS_RESULTCODE_NO_SUCH_BUCKET = 5013,
    OSS_RESULTCODE_NO_SUCH_KEY = 5014,
    OSS_RESULTCODE_NOT_IMPLEMENTED = 5015,
    OSS_RESULTCODE_PRECONDITION_FAILED = 5016,
    OSS_RESULTCODE_REQUEST_TIME_TOO_SKEWED = 5017,
    OSS_RESULTCODE_REQUEST_TIMEOUT = 5018,
    OSS_RESULTCODE_SIGNATURE_DOES_NOT_MATCH = 5019,
    OSS_RESULTCODE_TOO_MANY_BUCKETS=5020
};

