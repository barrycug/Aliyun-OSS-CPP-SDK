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
#include "OSSMultipartOperation.h"
#include "OSSApi.h"
#include <map>
#include "OSSError.h"
#include "OSSUtil.h"
#include "StringUtil.h"
#include "HttpUtil.h"
namespace OSS
{
OSSMultipartOperation::OSSMultipartOperation(string &endpoint,ServiceCredentials &serviceCredentials ,DefaultServiceClient *client):OSSOperation(endpoint,serviceCredentials,client)
{
	delegate = NULL;
}


OSSMultipartOperation::~OSSMultipartOperation(void)
{
}
	//同步调用
OSS_RESULTCODE OSSMultipartOperation::UploadPart(UploadPartRequest & uploadPartRequest,UploadPartResult & result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","UploadPart"));
	if(uploadPartRequest.bucketName.empty() || uploadPartRequest.key.empty()
		||uploadPartRequest.uploadId.empty() )
	{
		return OSS_RESULTCODE_INVALID;
	}
	 int l = uploadPartRequest.partSize;
    int i = uploadPartRequest.partNumber;
	if((l < 0) || (l > 5368709120) ||((i < 0) || (i > 10000)))
	{
		return OSS_RESULTCODE_INVALID;
	}
	char temp[64];
	sprintf(temp,"%ld",l);
	string strLength(temp);
	headers.insert(map<string, string> :: value_type("Content-Length",strLength));
	headers.insert(map<string, string> :: value_type("Content-MD5",uploadPartRequest.md5Digest));
	char temp1[64];
	sprintf(temp1,"%d",uploadPartRequest.partNumber);
	string strPartNumber(temp1);
	params.insert(map<string, string> :: value_type("partNumber",strPartNumber));
	params.insert(map<string, string> :: value_type("uploadId",uploadPartRequest.uploadId));

	ResponseMessage rm ;
	rm =  invoke(HttpMethod_PUT,uploadPartRequest.bucketName,uploadPartRequest.key,headers,params,uploadPartRequest.data,l,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		map<string,string> headers =rm.getHeaders();
		map<string,string>::iterator iter = headers.find("ETag");
		string eTag="";
		if(iter != headers.end())
		{
			eTag = iter->second;
		}
		eTag = StringUtil::trimQuote(eTag);
		result.partNumber = i;
		result.eTag = eTag;
		
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
	
}
OSS_RESULTCODE OSSMultipartOperation::ListParts(ListPartsRequest & listPartsRequest,PartListing &result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","ListParts"));
	if(listPartsRequest.bucketName.empty() || listPartsRequest.key.empty() ||listPartsRequest.uploadId.empty() )
	{
		return OSS_RESULTCODE_INVALID;
	}
	if(!(listPartsRequest.maxParts >0 && listPartsRequest.maxParts <1000) 
		||!(listPartsRequest.partNumberMarker >0 && listPartsRequest.partNumberMarker <1000))
	{
		return OSS_RESULTCODE_INVALID;
	}
	params.insert(map<string, string> :: value_type("uploadId",listPartsRequest.uploadId));
	char temp[64];
	sprintf(temp,"%ld",listPartsRequest.maxParts);
	string strMaxParts(temp);
	params.insert(map<string, string> :: value_type("max-parts",strMaxParts));
	char temp1[64];
	sprintf(temp1,"%ld",listPartsRequest.partNumberMarker);
	string strPartNumberMarker(temp1);
	params.insert(map<string, string> :: value_type("part-number-marker",strPartNumberMarker));

	ResponseMessage rm ;
	rm =  invoke(HttpMethod_GET,listPartsRequest.bucketName,listPartsRequest.key,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		if(rm.getContent() != NULL)
		{
			strXML.append(rm.getContent());
			result.MakePartListing(strXML);
		}
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;	

}
OSS_RESULTCODE OSSMultipartOperation::ListMultipartUploads(ListMultipartUploadsRequest &listMultipartUploadsRequest,MultipartUploadListing &result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","ListMultipartUploads"));
	if(listMultipartUploadsRequest.bucketName.empty()  )
	{
		return OSS_RESULTCODE_INVALID;
	}
	params.insert(map<string, string> :: value_type("uploads",""));
	if (!listMultipartUploadsRequest.delimiter.empty()) 
	{
		params.insert(map<string, string> :: value_type("delimiter",listMultipartUploadsRequest.delimiter));
    }
	if (!listMultipartUploadsRequest.keyMarker.empty()) 
	{
		params.insert(map<string, string> :: value_type("key-marker",listMultipartUploadsRequest.keyMarker));
    }
	if (listMultipartUploadsRequest.maxUploads > 0) 
	{
		char temp[64];
		sprintf(temp,"%ld",listMultipartUploadsRequest.maxUploads);
		string strMaxUploads(temp);
		params.insert(map<string, string> :: value_type("max-uploads",strMaxUploads));
    }
	if (!listMultipartUploadsRequest.prefix.empty()) 
	{
		params.insert(map<string, string> :: value_type("prefix",listMultipartUploadsRequest.prefix));
    }
	if (!listMultipartUploadsRequest.uploadIdMarker.empty()) 
	{
		params.insert(map<string, string> :: value_type("upload-id-marker",listMultipartUploadsRequest.uploadIdMarker));
    }
	
	ResponseMessage rm ;
	string key ="";
	rm =  invoke(HttpMethod_GET,listMultipartUploadsRequest.bucketName,key,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		if(rm.getContent() != NULL)
		{
			strXML.append(rm.getContent());
			result.MakeMultipartUploadListing(strXML);
		}
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
	/*

    [params setObject:@""  forKey:@"uploads"];

   
    if (listMultipartUploadsRequest.prefix != nil) {
        [params setObject:listMultipartUploadsRequest.prefix  forKey:@"prefix"];
    }
    if (listMultipartUploadsRequest.uploadIdMarker != nil) {
        [params setObject:listMultipartUploadsRequest.uploadIdMarker  forKey:@"upload-id-marker"];
    }
    NSArray *keys = [NSArray arrayWithObjects:@"method",nil];
    NSArray *objs = [NSArray arrayWithObjects:@"listMultipartUploads", nil];
    NSDictionary *userInfo = [NSDictionary dictionaryWithObjects:objs forKeys:keys];
    
    [self invoke:HttpMethod_GET buckName:listMultipartUploadsRequest.bucketName objectName:nil headers:nil params:params content:nil contentLength:0 userInfo:userInfo];
    [params release];
	*/
}
OSS_RESULTCODE OSSMultipartOperation::InitiateMultipartUpload(InitiateMultipartUploadRequest & initiateMultipartUploadRequest,InitiateMultipartUploadResult &result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","InitiateMultipartUpload"));
	if(initiateMultipartUploadRequest.bucketName.empty() || initiateMultipartUploadRequest.key.empty() )
	{
		return OSS_RESULTCODE_INVALID;
	}
	if(initiateMultipartUploadRequest.pObjectMetadata != NULL)
	{
		OSSUtil::populateRequestMetadata(headers,*initiateMultipartUploadRequest.pObjectMetadata);
	}
	map<string,string>::iterator iter = headers.find("Content-Length");
	if(iter != headers.end())
	{
		headers.erase(iter);
	}
	params.insert(map<string, string> :: value_type("uploads",""));
	string dataString = "data";
	string utf8Data = HttpUtil::MbcsToUtf8(dataString);
	char *data =(char *)utf8Data.c_str();
	ResponseMessage rm ;
	rm =  invoke(HttpMethod_POST,initiateMultipartUploadRequest.bucketName,initiateMultipartUploadRequest.key,headers,params,data,utf8Data.size(),userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		if(rm.getContent() != NULL)
		{
			strXML.append(rm.getContent());
			result.MakeInitiateMultipartUploadResult(strXML);
		}
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;	
}
OSS_RESULTCODE OSSMultipartOperation::CompleteMultipartUpload(CompleteMultipartUploadRequest &completeMultipartUploadRequest,CompleteMultipartUploadResult &result)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","CompleteMultipartUpload"));
	if(completeMultipartUploadRequest.bucketName.empty() || completeMultipartUploadRequest.key.empty()
		||completeMultipartUploadRequest.uploadId.empty() ||completeMultipartUploadRequest.partETags.size()==0)
	{
		return OSS_RESULTCODE_INVALID;
	}
	
	headers.insert(map<string, string> :: value_type("Content-Type","text/plain"));
	params.insert(map<string, string> :: value_type("uploadId",completeMultipartUploadRequest.uploadId));
	string strContent = buildMultipartRequestXml(completeMultipartUploadRequest.partETags);
	string utf8Data = HttpUtil::MbcsToUtf8(strContent);
	char *data =(char *)utf8Data.c_str();
	ResponseMessage rm ;
	rm =  invoke(HttpMethod_POST,completeMultipartUploadRequest.bucketName,completeMultipartUploadRequest.key,headers,params,data,utf8Data.size(),userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		string strXML ;
		if(rm.getContent() != NULL)
		{
			strXML.append(rm.getContent());
			result.MakeCompleteMultipartUploadResult(strXML);
		}
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;
}
OSS_RESULTCODE OSSMultipartOperation::AbortMultipartUpload(AbortMultipartUploadRequest & abortMultipartUploadRequest,string& uploadId)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","AbortMultipartUpload"));
	userInfo.insert(map<string, string> :: value_type("uploadId",abortMultipartUploadRequest.uploadId));
	if(abortMultipartUploadRequest.bucketName.empty() || abortMultipartUploadRequest.key.empty()||abortMultipartUploadRequest.uploadId.empty() )
	{
		return OSS_RESULTCODE_INVALID;
	}
	params.insert(map<string, string> :: value_type("uploadId",abortMultipartUploadRequest.uploadId));
	ResponseMessage rm ;
	rm =  invoke(HttpMethod_DELETE,abortMultipartUploadRequest.bucketName,abortMultipartUploadRequest.key,headers,params,NULL,0,userInfo);
	OSS_RESULTCODE rCode;
	if(rm.isSuccessful())
	{
		rCode = OSS_RESULTCODE_OK;
		uploadId = abortMultipartUploadRequest.uploadId;
	}
	else
	{
		string strError(rm.getContent());
		OSSError error(strError);
		rCode = OSSUtil::codeFromString(error.code);
	}
	return rCode;

}
	//异步调用
bool OSSMultipartOperation::UploadPart_Async(UploadPartRequest & uploadPartRequest)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","UploadPart"));
	
	if(uploadPartRequest.bucketName.empty() || uploadPartRequest.key.empty()
		||uploadPartRequest.uploadId.empty() )
	{
		return false;
	}
	 int l = uploadPartRequest.partSize;
    int i = uploadPartRequest.partNumber;
	if((l < 0) || (l > 5368709120) ||((i < 0) || (i > 10000)))
	{
		return false;
	}

	char temp[64];
	sprintf(temp,"%ld",l);
	string strLength(temp);
	headers.insert(map<string, string> :: value_type("Content-Length",strLength));
	headers.insert(map<string, string> :: value_type("Content-MD5",uploadPartRequest.md5Digest));
	char temp1[64];
	sprintf(temp1,"%d",uploadPartRequest.partNumber);
	string strPartNumber(temp1);
	params.insert(map<string, string> :: value_type("partNumber",strPartNumber));
	params.insert(map<string, string> :: value_type("uploadId",uploadPartRequest.uploadId));

	userInfo.insert(map<string, string> :: value_type("partNumber",strPartNumber));

	ResponseMessage rm ;
	return invoke_Async(HttpMethod_PUT,uploadPartRequest.bucketName,uploadPartRequest.key,headers,params,uploadPartRequest.data,l,userInfo);
}
bool OSSMultipartOperation::ListParts_Async(ListPartsRequest & listPartsRequest)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","ListParts"));
	if(listPartsRequest.bucketName.empty() || listPartsRequest.key.empty() ||listPartsRequest.uploadId.empty() )
	{
		return false;
	}
	if(!(listPartsRequest.maxParts >0 && listPartsRequest.maxParts <1000) 
		||!(listPartsRequest.partNumberMarker >0 && listPartsRequest.partNumberMarker <1000))
	{
		return false;
	}
	params.insert(map<string, string> :: value_type("uploadId",listPartsRequest.uploadId));
	char temp[64];
	sprintf(temp,"%ld",listPartsRequest.maxParts);
	string strMaxParts(temp);
	params.insert(map<string, string> :: value_type("max-parts",strMaxParts));
	char temp1[64];
	sprintf(temp1,"%ld",listPartsRequest.partNumberMarker);
	string strPartNumberMarker(temp1);
	params.insert(map<string, string> :: value_type("part-number-marker",strPartNumberMarker));

	ResponseMessage rm ;
	return invoke_Async(HttpMethod_GET,listPartsRequest.bucketName,listPartsRequest.key,headers,params,NULL,0,userInfo);
	
}
bool OSSMultipartOperation::ListMultipartUploads_Async(ListMultipartUploadsRequest &listMultipartUploadsRequest)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","ListMultipartUploads"));
	if(listMultipartUploadsRequest.bucketName.empty()  )
	{
		return false;
	}
	params.insert(map<string, string> :: value_type("uploads",""));
	if (!listMultipartUploadsRequest.delimiter.empty()) 
	{
		params.insert(map<string, string> :: value_type("delimiter",listMultipartUploadsRequest.delimiter));
    }
	if (!listMultipartUploadsRequest.keyMarker.empty()) 
	{
		params.insert(map<string, string> :: value_type("key-marker",listMultipartUploadsRequest.keyMarker));
    }
	if (listMultipartUploadsRequest.maxUploads > 0) 
	{
		char temp[64];
		sprintf(temp,"%ld",listMultipartUploadsRequest.maxUploads);
		string strMaxUploads(temp);
		params.insert(map<string, string> :: value_type("max-uploads",strMaxUploads));
    }
	if (!listMultipartUploadsRequest.prefix.empty()) 
	{
		params.insert(map<string, string> :: value_type("prefix",listMultipartUploadsRequest.prefix));
    }
	if (!listMultipartUploadsRequest.uploadIdMarker.empty()) 
	{
		params.insert(map<string, string> :: value_type("upload-id-marker",listMultipartUploadsRequest.uploadIdMarker));
    }
	
	ResponseMessage rm ;
	string key ="";
	return invoke_Async(HttpMethod_GET,listMultipartUploadsRequest.bucketName,key,headers,params,NULL,0,userInfo);
}
bool OSSMultipartOperation::InitiateMultipartUpload_Async(InitiateMultipartUploadRequest & initiateMultipartUploadRequest)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","InitiateMultipartUpload"));
	if(initiateMultipartUploadRequest.bucketName.empty() || initiateMultipartUploadRequest.key.empty() )
	{
		return false;
	}
	if(initiateMultipartUploadRequest.pObjectMetadata != NULL)
	{
		OSSUtil::populateRequestMetadata(headers,*initiateMultipartUploadRequest.pObjectMetadata);
	}
	map<string,string>::iterator iter = headers.find("Content-Length");
	if(iter != headers.end())
	{
		headers.erase(iter);
	}
	params.insert(map<string, string> :: value_type("uploads",""));
	string dataString = "data";
	string utf8Data = HttpUtil::MbcsToUtf8(dataString);
	char *data =(char *)utf8Data.c_str();
	ResponseMessage rm ;
	return invoke_Async(HttpMethod_POST,initiateMultipartUploadRequest.bucketName,initiateMultipartUploadRequest.key,headers,params,data,utf8Data.size(),userInfo);
	
}
bool OSSMultipartOperation::CompleteMultipartUpload_Async(CompleteMultipartUploadRequest &completeMultipartUploadRequest)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","CompleteMultipartUpload"));
	if(completeMultipartUploadRequest.bucketName.empty() || completeMultipartUploadRequest.key.empty()
		||completeMultipartUploadRequest.uploadId.empty() ||completeMultipartUploadRequest.partETags.size()==0)
	{
		return false;
	}
	
	headers.insert(map<string, string> :: value_type("Content-Type","text/plain"));
	params.insert(map<string, string> :: value_type("uploadId",completeMultipartUploadRequest.uploadId));
	string strContent = buildMultipartRequestXml(completeMultipartUploadRequest.partETags);
	string utf8Data = HttpUtil::MbcsToUtf8(strContent);
	char *data =(char *)utf8Data.c_str();
	ResponseMessage rm ;
	return invoke_Async(HttpMethod_POST,completeMultipartUploadRequest.bucketName,completeMultipartUploadRequest.key,headers,params,data,utf8Data.size(),userInfo);
	
}
bool OSSMultipartOperation::AbortMultipartUpload_Async(AbortMultipartUploadRequest & abortMultipartUploadRequest)
{
	map<string,string> headers;
	map<string,string> params;
	map<string,string> userInfo;
	userInfo.insert(map<string, string> :: value_type("method","AbortMultipartUpload"));
	userInfo.insert(map<string, string> :: value_type("uploadId",abortMultipartUploadRequest.uploadId));
	if(abortMultipartUploadRequest.bucketName.empty() || abortMultipartUploadRequest.key.empty()||abortMultipartUploadRequest.uploadId.empty() )
	{
		return false;
	}
	params.insert(map<string, string> :: value_type("uploadId",abortMultipartUploadRequest.uploadId));
	ResponseMessage rm ;
	return invoke_Async(HttpMethod_DELETE,abortMultipartUploadRequest.bucketName,abortMultipartUploadRequest.key,headers,params,NULL,0,userInfo);

}
ResponseMessage OSSMultipartOperation::invoke(HttpMethod httpMethod,string &bucketName,string &objName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo)
{
	ResponseMessage rm = request(httpMethod,bucketName,objName,headers,params,content,contentLength,userInfo);
	return rm;
}
bool OSSMultipartOperation::invoke_Async(HttpMethod httpMethod,string &bucketName,string &objName,map<string,string> &headers,map<string,string> &params,char *content,long contentLength,map<string,string> &userInfo)
{
	return request_Async(httpMethod,bucketName,objName,headers,params,content,contentLength,userInfo);
}
void OSSMultipartOperation::serviceClientRequestFinished(DefaultServiceClient*defaultServiceClient,ResponseMessage &responseMessage)
{
	if(delegate != NULL)
	{
		map<string,string> userInfo = responseMessage.userInfo;
		map<string,string>::iterator iter ;
		iter = userInfo.find("method");
		string method = "";
		if(iter != userInfo.end())
		{
			method = iter->second;
		}
		if (responseMessage.isSuccessful())
		{
			if(method.compare("AbortMultipartUpload")==0)
			{
				string uploadId = userInfo["uploadId"];
				delegate->OnAbortMultipartUploadComplete(this,uploadId);
			} 
			else if(method.compare("InitiateMultipartUpload")==0)
			{
				string strXML="";
				InitiateMultipartUploadResult result;
				if(responseMessage.getContent() != NULL)
				{
					strXML.append(responseMessage.getContent());
					result.MakeInitiateMultipartUploadResult(strXML);
				}
				delegate->OnInitiateMultipartUploadComplete(this,result);
			} 
			else if(method.compare("CompleteMultipartUpload")==0)
			{
				string strXML ;
				CompleteMultipartUploadResult result;
				if(responseMessage.getContent() != NULL)
				{
					strXML.append(responseMessage.getContent());
					result.MakeCompleteMultipartUploadResult(strXML);
				}
				delegate->OnCompleteMultipartUploadComplete(this,result);
			} 
			//ListParts
			else if(method.compare("ListParts")==0)
			{
				string strXML ;
				PartListing result;
				if(responseMessage.getContent() != NULL)
				{
					strXML.append(responseMessage.getContent());
					result.MakePartListing(strXML);
				}
				delegate->OnListPartsComplete(this,result);
			} 
			//ListMultipartUploads
			else if(method.compare("ListMultipartUploads")==0)
			{
				string strXML ;
				MultipartUploadListing result;
				if(responseMessage.getContent() != NULL)
				{
					strXML.append(responseMessage.getContent());
					result.MakeMultipartUploadListing(strXML);
				}
				delegate->OnListMultipartUploadsComplete(this,result);
			} 
			//UploadPart
			else if(method.compare("UploadPart")==0)
			{
				UploadPartResult result;
				map<string,string> headers =responseMessage.getHeaders();
				map<string,string>::iterator iter = headers.find("ETag");
				string eTag="";
				if(iter != headers.end())
				{
					eTag = iter->second;
				}
				eTag = StringUtil::trimQuote(eTag);
				string strPartNumber = userInfo["pPartNumber"];
				int i = 0;
				i = atoi(strPartNumber.c_str());
				result.partNumber = i;
				result.eTag = eTag;
				delegate->OnUploadPartComplete(this,result);
			} 
			
		}
		else
		{
			OSS_RESULTCODE rCode;
			string strError(responseMessage.getContent());
			OSSError error(strError);
			rCode = OSSUtil::codeFromString(error.code);
			//AbortMultipartUpload
			if(method.compare("AbortMultipartUpload")==0)
			{
				delegate->OnAbortMultipartUploadFailed(this,rCode);
			} 
			//InitiateMultipartUpload
			else if(method.compare("InitiateMultipartUpload")==0)
			{
				delegate->OnInitiateMultipartUploadFailed(this,rCode);
			} 
			//CompleteMultipartUpload
			else if(method.compare("CompleteMultipartUpload")==0)
			{
				delegate->OnCompleteMultipartUploadFailed(this,rCode);
			} 
			//ListParts
			else if(method.compare("ListParts")==0)
			{
				delegate->OnListPartsFailed(this,rCode);
			} 
			//ListMultipartUploads
			else if(method.compare("ListMultipartUploads")==0)
			{
				delegate->OnListMultipartUploadsFailed(this,rCode);
			} 
			//UploadPart
			else if(method.compare("UploadPart")==0)
			{
				delegate->OnUploadPartFailed(this,rCode);
			} 
			
		}
	}
}
void OSSMultipartOperation::serviceClientRequestFailed(DefaultServiceClient*defaultServiceClient, ResponseMessage &responseMessage)
{
	OSSError error;
	error.message = "network error";
	if(delegate != NULL)
	{
		delegate->OnNetworkFailed(this,OSS_RESULTCODE_INVALID);
	}
}
string OSSMultipartOperation::buildMultipartRequestXml(vector<PartETag> &partETags)
{
    string rtnString="";
    rtnString+="<CompleteMultipartUpload>";
	for (int i=0;i<partETags.size();i++) {
		PartETag partETag = partETags[i];
        rtnString+="<Part>";
        rtnString+="<PartNumber>";
		char temp[64];
		sprintf(temp,"%d",partETag.partNumber);
        rtnString+=temp;
        rtnString+="</PartNumber>";
        rtnString+="<ETag>";
		rtnString+=partETag.eTag;
        rtnString+="</ETag>";
        rtnString+="</Part>";
    }
    rtnString+="</CompleteMultipartUpload>";
    return rtnString;
}
}
