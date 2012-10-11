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
#include "HTTPRequest.h"
#include <process.h>
#include "StringUtil.h"
namespace OSS
{
#define  RESULTDATA_INCREASE_LEN		(10*1024)       ///<  保存http请求结果分配的每个数据块的大小
#define  MAX_RECVDATA_LEN				102400000     ///<  保存每次http请求结果分配的最大内存

#define _DEBUG 1
HTTP_RESULTCODE GetErrorCode( CURLcode eUrlError )
{
	HTTP_RESULTCODE eErrorCode;
	switch(eUrlError)
	{
	case CURLE_OK:
		eErrorCode = HTTPRESULT_OK;
		break;
	case CURLE_COULDNT_CONNECT:
		eErrorCode = HTTPRESULT_CANTCONNECT;
		break;
	case CURLE_OPERATION_TIMEDOUT:
		eErrorCode = HTTPRESULT_TIMEOUT;
		break;
	case CURLE_HTTP_RETURNED_ERROR:
		eErrorCode = HTTPRESULT_ERROR;
		break;
	case CURLE_COULDNT_RESOLVE_HOST:
		eErrorCode = HTTPRESULT_CANTRESOLVE;
		break;
	default :
		eErrorCode = HTTPRESULT_FAIL;
		break;
	}

	return eErrorCode;
}
/********************************************************************
 *       异步线程处理函数  http put             *
 ********************************************************************/
unsigned __stdcall  thread_http_put(LPVOID lpParam)
{
	HTTPRequest * pHttp= (HTTPRequest *) lpParam;
	CURLcode rCode = pHttp->DoHttpPut();
	pHttp->isRunning = false;
     HTTP_RESULTCODE eHttpError = GetErrorCode(rCode);	
	 //分发消息
	if (pHttp->delegate != NULL)
	{
		if (rCode == HTTPRESULT_OK)
		{

			pHttp->delegate->OnHttpComplete(pHttp);
		}
		else
		{
			pHttp->delegate->OnHttpFailed(pHttp,eHttpError);
		}
		
	}

	
	return 0;
}
unsigned __stdcall  thread_http_get(LPVOID lpParam)
{
	HTTPRequest * pHttp= (HTTPRequest *) lpParam;
	CURLcode rCode = pHttp->DoHttpGet();
	pHttp->isRunning = false;
     HTTP_RESULTCODE eHttpError = GetErrorCode(rCode);	
	 //分发消息
	if (pHttp->delegate != NULL)
	{
		if (rCode == HTTPRESULT_OK)
		{

			pHttp->delegate->OnHttpComplete(pHttp);
		}
		else
		{
			pHttp->delegate->OnHttpFailed(pHttp,eHttpError);
		}
		
	}

	
	return 0;
}
unsigned __stdcall  thread_http_post(LPVOID lpParam)
{
	HTTPRequest * pHttp= (HTTPRequest *) lpParam;
	CURLcode rCode = pHttp->DoHttpPost();
	pHttp->isRunning = false;
     HTTP_RESULTCODE eHttpError = GetErrorCode(rCode);	
	 //分发消息
	if (pHttp->delegate != NULL)
	{
		if (rCode == HTTPRESULT_OK)
		{

			pHttp->delegate->OnHttpComplete(pHttp);
		}
		else
		{
			pHttp->delegate->OnHttpFailed(pHttp,eHttpError);
		}
		
	}

	
	return 0;
}
unsigned __stdcall  thread_http_head(LPVOID lpParam)
{
	HTTPRequest * pHttp= (HTTPRequest *) lpParam;
	CURLcode rCode = pHttp->DoHttpHead();
	pHttp->isRunning = false;
     HTTP_RESULTCODE eHttpError = GetErrorCode(rCode);	
	 //分发消息
	if (pHttp->delegate != NULL)
	{
		if (rCode == HTTPRESULT_OK)
		{

			pHttp->delegate->OnHttpComplete(pHttp);
		}
		else
		{
			pHttp->delegate->OnHttpFailed(pHttp,eHttpError);
		}
		
	}

	
	return 0;
}
unsigned __stdcall  thread_http_delete(LPVOID lpParam)
{
	HTTPRequest * pHttp= (HTTPRequest *) lpParam;
	CURLcode rCode = pHttp->DoHttpDelete();
	pHttp->isRunning = false;
     HTTP_RESULTCODE eHttpError = GetErrorCode(rCode);	
	 //分发消息
	if (pHttp->delegate != NULL)
	{
		if (rCode == HTTPRESULT_OK)
		{

			pHttp->delegate->OnHttpComplete(pHttp);
		}
		else
		{
			pHttp->delegate->OnHttpFailed(pHttp,eHttpError);
		}
		
	}

	
	return 0;
}
bool HTTPRequest::SetReciveFile(string & filePath)
{
	fopen_s(&_pf,filePath.c_str(),"w+");
	if(_pf != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
HTTPRequest::HTTPRequest(string url_ )
{
//	curl_global_init(CURL_GLOBAL_ALL); 
	url = url_;
	isRunning = false;
	_data = NULL;
	_dataLength = 0;
	_dataStart = NULL;
	userAgent = "";
	proxyHost = "";
	proxyPort = 0;
	timeOutSeconds = 100;
	proxyUserName= "";
	proxyPassword= "";
	proxyDomain= "";
	requestMethod = HttpMethod_GET;
	delegate = NULL;
	_uWritePos = 0;
	_pf = NULL;
	_pchResultData = NULL;
	
}

HTTPRequest::~HTTPRequest(void)
{
	if(_dataStart != NULL)
	{
		delete [] _dataStart;
		_data = NULL;
		_dataStart = NULL;
		_dataLength = 0;
	}
	if(_pchResultData != NULL)
	{
		delete []_pchResultData;
		_pchResultData = NULL;
		_uWritePos = 0;
		_uLength = 0;
	}
	if(_pf != NULL)
	{
		fclose(_pf);
		_pf = NULL;
	}

//	curl_global_cleanup(); 
}
void HTTPRequest:: addPostData(char * data,long length)
{
	if(length >=0)
	{
		if(_dataStart != NULL)
		{
			delete [] _dataStart;
			_data = NULL;
			_dataStart = NULL;
			_dataLength = 0;
		}
		_data = new char [length];
		memcpy(_data,data,length);
		_dataLength = length;
		_dataStart = _data;
	}
}
void HTTPRequest:: addRequestHeader(string key,string value)
{
	_headers.insert(map<string, string> :: value_type(key,value));	
}

void HTTPRequest::reset()
{	
	isRunning = false;
	_data = NULL;
	_dataStart = NULL;
	_dataLength = 0;
	userAgent = "";
	proxyHost = "";
	proxyPort = 0;
	timeOutSeconds = 100;
	proxyUserName= "";
	proxyPassword= "";
	proxyDomain= "";
	requestMethod = HttpMethod_GET;
	if(_pchResultData != NULL)
	{
		delete []_pchResultData;
		_pchResultData = NULL;
		_uWritePos = 0;
		_uLength = 0;
	}
	_headers.clear();
	if(_dataStart != NULL)
	{
		delete [] _dataStart;
		_data = NULL;
		_dataStart = NULL;
		_dataLength = 0;
	}
}
map<string,string> HTTPRequest:: getResponseHeaders()
{
	return _responseHeaders;
}
HTTP_RESULTCODE HTTPRequest::startSynchronous()
{
	HTTP_RESULTCODE rCode = HTTPRESULT_FAIL;
	if (url.empty())
	{
		return rCode;
	}

	if( isRunning )
	{
		return rCode;
	}

	isRunning	= true;
	CURLcode code;
	switch (requestMethod)
	{
	case HttpMethod_GET:
		code = DoHttpGet();
		break;
	case HttpMethod_POST:
		code = DoHttpPost();
		break;
	case HttpMethod_HEAD:
		code = DoHttpHead();
		break;
	case HttpMethod_PUT:
		code = DoHttpPut();
		break;
	case HttpMethod_DELETE:
		code = DoHttpDelete();
		break;
	default:
		break;
	}
	isRunning = false;
	rCode = GetErrorCode(code);
	
	printf("%s",_pchResultData);
	/*
	//分发消息
	if (delegate != NULL)
	{
		if (rCode == HTTPRESULT_OK)
		{

			delegate->OnHttpComplete(this);
		}
		else
		{
			delegate->OnHttpFailed(this,rCode);
		}
		
	}
	*/
	return rCode;
}
char * HTTPRequest::resposeData()
{
	return _pchResultData;
}
long   HTTPRequest::resposeDataLength()
{
	return _uWritePos;
}
void HTTPRequest::SetBaseParam(CURL *curl)
{
	switch (requestMethod)
		{
		case HttpMethod_GET:
			curl_easy_setopt( curl, CURLOPT_HTTPGET, 1 );
			break;
		case HttpMethod_POST:
			curl_easy_setopt( curl, CURLOPT_POST, 1 );
			break;
		case HttpMethod_HEAD:
			curl_easy_setopt(curl,CURLOPT_NOBODY ,1L );
			break;
		case HttpMethod_PUT:
			 curl_easy_setopt(curl, CURLOPT_PUT, 1L);
			break;
		case HttpMethod_DELETE:
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE"); 
			break;
		default:
			break;
		}
		
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	if(!userAgent.empty())
	{
		curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent.c_str()); 
	}
	if(timeOutSeconds > 0)
	{
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeOutSeconds); 
	}
	if (!proxyHost.empty())
	{
		string strPort;
		string str;
		if (proxyPort >0)
		{
		//	curl_easy_setopt(curl, CURLOPT_PROXYPORT, proxyPort); 
			char temp[64];
			sprintf_s(temp,":%d",proxyPort);
			strPort.append(temp);
		}
		str = proxyHost+strPort;
	//	curl_easy_setopt(curl,CURLOPT_HTTPPROXYTUNNEL,0);
		curl_easy_setopt(curl, CURLOPT_PROXY, str.c_str()); 
	}
		
	if (!proxyUserName.empty())
	{
		string str="";
		if(!proxyDomain.empty())
		{
			str += proxyDomain;
			str += "\\";
		}
		str +=proxyUserName;
		str +=":";
		str +=proxyPassword;
		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, str.c_str());  
	}	
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); 
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""); 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPRequest::ProcessResult);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
	curl_easy_setopt(curl,CURLOPT_HEADERFUNCTION, HTTPRequest::ProcessHeaders);
	
	
	/**
	*debug
	*/
	if(_DEBUG)
	{
			struct data config;
		config.trace_ascii = 1;
		curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, HTTPRequest::my_trace);
		curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	}            
}
curl_slist * HTTPRequest::MakeHeaders(CURL *curl)
{
	struct curl_slist *headers=NULL;
	map < string, string >::iterator iter=_headers.begin();
	iter = _headers.find("Content-Length");

	if(iter == _headers.end())
	{
		char temp[64];
		string str;  
		sprintf_s(temp, "%d", _dataLength);
		string s(temp);
		_headers.insert(map<string, string> :: value_type("Content-Length",s));	
	}

	iter = _headers.find("Accept-Encoding");
	if(iter == _headers.end())
	{
		_headers.insert(map<string, string> :: value_type("Accept-Encoding","gzip"));	
	}
	iter = _headers.find("Connection");
	if(iter == _headers.end())
	{
		_headers.insert(map<string, string> :: value_type("Connection","close"));	
	}
	for (iter = _headers.begin(); iter != _headers.end(); iter++ ) 
	{ 
		string headerStr = "";
		headerStr+=iter->first;
		headerStr+=":";
		headerStr+=iter->second;
		headers = curl_slist_append(headers, headerStr.c_str()); 
	} 
	
	
	
 	return headers;

}
CURLcode HTTPRequest::DoHttpGet()
{
	CURL *curl;
	curl = curl_easy_init();	

	curl_version_info_data * vinfo = curl_version_info( CURLVERSION_NOW ); 
	CURLcode eErrorCode;
	if(curl != NULL)
	{
		struct curl_slist *headers=NULL; 
		SetBaseParam(curl);
		headers = MakeHeaders(curl);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
		eErrorCode = curl_easy_perform(curl);
		long http_code = 0;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		statusCode = http_code;
		curl_slist_free_all(headers);
		//如果写文件，则关闭文件
		if(_pf != NULL)
		{
			fclose(_pf);
			_pf = NULL;
		}
	}
	curl_easy_cleanup(curl);	

	return eErrorCode;	
}
CURLcode HTTPRequest::DoHttpPost()
{
	CURL *curl;
	curl = curl_easy_init();	

	curl_version_info_data * vinfo = curl_version_info( CURLVERSION_NOW ); 
	CURLcode eErrorCode;
	if(curl != NULL)
	{
		struct curl_slist *headers=NULL; 
		SetBaseParam(curl);
		headers = MakeHeaders(curl);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
		if(_dataStart != NULL && _dataLength > 0)
		{
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, _data);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, _dataLength);
		}
		eErrorCode = curl_easy_perform(curl);
		long http_code = 0;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		statusCode = http_code;
		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);	

	return eErrorCode;	
}
CURLcode HTTPRequest:: DoHttpHead()
{
	CURL *curl;
	curl = curl_easy_init();	

	curl_version_info_data * vinfo = curl_version_info( CURLVERSION_NOW ); 
	CURLcode eErrorCode;
	if(curl != NULL)
	{
		struct curl_slist *headers=NULL; 
		SetBaseParam(curl);
		headers = MakeHeaders(curl);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
		eErrorCode = curl_easy_perform(curl);
		long http_code = 0;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		statusCode = http_code;
		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);	

	return eErrorCode;	
}
CURLcode HTTPRequest:: DoHttpDelete()
{
	CURLcode eErrorCode =CURLE_REMOTE_FILE_NOT_FOUND ;
	CURL *curl;
	curl = curl_easy_init();	
	curl_version_info_data * vinfo = curl_version_info( CURLVERSION_NOW ); 

	if(curl != NULL)
	{
		struct curl_slist *headers=NULL; 
		SetBaseParam(curl);
		headers = MakeHeaders(curl);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
		eErrorCode = curl_easy_perform(curl);
		long http_code = 0;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		statusCode = http_code;
		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);	
	return eErrorCode;
}
CURLcode HTTPRequest:: DoHttpPut()
{
	CURLcode eErrorCode =CURLE_REMOTE_FILE_NOT_FOUND ;
	CURL *curl;
	curl = curl_easy_init();	
	curl_version_info_data * vinfo = curl_version_info( CURLVERSION_NOW ); 

	if(curl != NULL)
	{
		struct curl_slist *headers=NULL; 
		SetBaseParam(curl);
		headers = MakeHeaders(curl);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
		
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L); //PUT
		if(_dataLength >0)
		{
			curl_easy_setopt(curl, CURLOPT_READDATA, this);
			curl_easy_setopt(curl, CURLOPT_INFILESIZE, _dataLength);
			curl_easy_setopt(curl, CURLOPT_READFUNCTION, HTTPRequest::Reader);
		}
		else
		{
			curl_easy_setopt(curl, CURLOPT_INFILESIZE, 0L);
		}
		/*
		if(_data != NULL && _dataLength > 0)
		{
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, _data);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, _dataLength);
		}	
		*/
	//	_responseHeaders.clear();
		eErrorCode = curl_easy_perform(curl);
		long http_code = 0;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		statusCode = http_code;
		
		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);	
	return eErrorCode;
}
size_t	HTTPRequest::Reader( void* data, size_t size, size_t nmemb, void *pHttp )
{
	HTTPRequest * oHttpRequest = (HTTPRequest *)pHttp;
	return oHttpRequest->ReadData((char*)data,  size,  nmemb);	
}
size_t HTTPRequest::ReadData(char* pchData, size_t size, size_t nmemb)
{
	size_t curl_size = nmemb * size;
	size_t to_copy = (_dataLength < curl_size) ? _dataLength : curl_size;
	memcpy(pchData, _data, to_copy);
	_dataLength -= to_copy;
	_data += to_copy;
	return to_copy;

}
size_t HTTPRequest::ProcessHeaders(void *ptr, size_t size, size_t nmemb,void *pHttp) 
{
	HTTPRequest * oHttpRequest = (HTTPRequest *)pHttp;
	return oHttpRequest->GetHeaders(ptr,  size,nmemb );
}
size_t HTTPRequest::GetHeaders(void *ptr, size_t size, size_t nmemb) 
{
       long len = 0;
	   string header;
	   if(ptr != NULL)
	   {
			  header.append((char*)ptr);
			  vector<string> headerArray;
			  StringUtil::splitHeader(header,':',headerArray);
			  if(headerArray.size() ==2)
			  {
				  string strKey = StringUtil::trim(headerArray[0]);
				  string strValue = StringUtil::trim(headerArray[1]);
				  _responseHeaders.insert(map<string, string> :: value_type(strKey,strValue));
			  }
	   }
       return size * nmemb;
}
void HTTPRequest::dump(const char *text,
          FILE *stream, unsigned char *ptr, size_t size,
          char nohex)
{
  size_t i;
  size_t c;
 
  unsigned int width=0x10;
 
  if(nohex)
    /* without the hex output, we can fit more on screen */ 
    width = 0x40;
 
  fprintf(stream, "%s, %10.10ld bytes (0x%8.8lx)\n",
          text, (long)size, (long)size);
 
  for(i=0; i<size; i+= width) {
 
    fprintf(stream, "%4.4lx: ", (long)i);
 
    if(!nohex) {
      /* hex not disabled, show it */ 
      for(c = 0; c < width; c++)
        if(i+c < size)
          fprintf(stream, "%02x ", ptr[i+c]);
        else
          fputs("   ", stream);
    }
 
    for(c = 0; (c < width) && (i+c < size); c++) {
      /* check for 0D0A; if found, skip past and start a new line of output */ 
      if (nohex && (i+c+1 < size) && ptr[i+c]==0x0D && ptr[i+c+1]==0x0A) {
        i+=(c+2-width);
        break;
      }
      fprintf(stream, "%c",
              (ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:'.');
      /* check again for 0D0A, to avoid an extra \n if it's at width */ 
      if (nohex && (i+c+2 < size) && ptr[i+c+1]==0x0D && ptr[i+c+2]==0x0A) {
        i+=(c+3-width);
        break;
      }
    }
    fputc('\n', stream); /* newline */ 
  }
  fflush(stream);
}
int HTTPRequest::my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
  struct data *config = (struct data *)userp;
  const char *text;
  (void)handle; /* prevent compiler warning */ 
 
  switch (type) {
  case CURLINFO_TEXT:
    fprintf(stderr, "== Info: %s", data);
  default: /* in case a new one is introduced to shock us */ 
    return 0;
 
  case CURLINFO_HEADER_OUT:
    text = "=> Send header";
	 dump(text, stderr, (unsigned char *)data, size, config->trace_ascii);
    break;
  case CURLINFO_DATA_OUT:
    text = "=> Send data";
    break;
  case CURLINFO_SSL_DATA_OUT:
    text = "=> Send SSL data";
    break;
  case CURLINFO_HEADER_IN:
    text = "<= Recv header";
	 dump(text, stderr, (unsigned char *)data, size, config->trace_ascii);
    break;
  case CURLINFO_DATA_IN:
    text = "<= Recv data";
	 dump(text, stderr, (unsigned char *)data, size, config->trace_ascii);
    break;
  case CURLINFO_SSL_DATA_IN:
    text = "<= Recv SSL data";
    break;
  }
  //
 // dump(text, stderr, (unsigned char *)data, size, config->trace_ascii);
 
  return 0;
}

bool HTTPRequest::WriteResultData(char* pchData, unsigned long  uLength)
{
	if( NULL == pchData || 0 == uLength )
	{
		return false;
	}
	if(_pf == NULL)
	{
		if( NULL == _pchResultData )
		{
			_uLength	 = RESULTDATA_INCREASE_LEN;
			_uWritePos = 0;
			_pchResultData = new char[RESULTDATA_INCREASE_LEN];
			memset(_pchResultData,0,RESULTDATA_INCREASE_LEN);
		}

		/// 不够放，则移动一下，扩大一下接收区
		if( _uWritePos + uLength > _uLength )
		{
			if( _uLength + RESULTDATA_INCREASE_LEN > MAX_RECVDATA_LEN )
			{
				return false;
			}

			char* pTmpData = new char[_uLength+RESULTDATA_INCREASE_LEN];
			memset(pTmpData,0,_uLength+RESULTDATA_INCREASE_LEN);
			if( NULL == pTmpData )
			{
				return false;
			}

			memcpy(pTmpData,_pchResultData,_uLength);
			delete []_pchResultData;
			_pchResultData = pTmpData;
			_uLength = _uLength+RESULTDATA_INCREASE_LEN;
		}

		if( _uWritePos + uLength > _uLength )
		{
			return false;
		}

		/// Copy新的数据
		memcpy( _pchResultData + _uWritePos ,pchData,uLength);
		_uWritePos += uLength;

		return true;
	}
	//直接写入到文件中
	else
	{
		fwrite(pchData,1,uLength,_pf);
		return true;
	}
}


size_t	HTTPRequest::ProcessResult( void* data, size_t size, size_t nmemb, void *pHttpRequest )
{
	if ( pHttpRequest == NULL)
	{
		return 0;
	}

	HTTPRequest * oHttpRequest = (HTTPRequest *)pHttpRequest;
	oHttpRequest->WriteResultData((char*)data,nmemb);	
	return  size * nmemb;
}
bool HTTPRequest::startAsyncSynchronous()
{
	bool code = false;
	if (url.empty())
	{
		return false;
	}

	if( isRunning )
	{
		return false;
	}

	isRunning	= true;
	switch (requestMethod)
	{
	case HttpMethod_GET:
		code = AsyncDoHttpGet();
		break;
	case HttpMethod_POST:
		code = AsyncDoHttpPost();
		break;
	case HttpMethod_HEAD:
		code = AsyncDoHttpHead();
		break;
	case HttpMethod_PUT:
		code = AsyncDoHttpPut();
		break;
	case HttpMethod_DELETE:
		code = AsyncDoHttpDelete();
		break;
	default:
		break;
	}
	return code;

}
bool HTTPRequest::AsyncDoHttpGet()
{
	UINT dwThreadID = 0;
	int nVal = _beginthreadex(NULL, 0, thread_http_get, (void *)this, 0, &dwThreadID);
	if (nVal <= 0)	
	{
		return false;
	}
	 
	WaitForSingleObject ((HANDLE)nVal, INFINITE);
	CloseHandle ((HANDLE)nVal);
	return true;
}
bool HTTPRequest::AsyncDoHttpPost()
{
	UINT dwThreadID = 0;
	int nVal = _beginthreadex(NULL, 0, thread_http_post, (void *)this, 0, &dwThreadID);
	if (nVal <= 0)	
	{
		return false;
	}
	 
	WaitForSingleObject ((HANDLE)nVal, INFINITE);
	CloseHandle ((HANDLE)nVal);
	return true;
}
bool HTTPRequest::AsyncDoHttpHead()
{
	UINT dwThreadID = 0;
	int nVal = _beginthreadex(NULL, 0, thread_http_head, (void *)this, 0, &dwThreadID);
	if (nVal <= 0)	
	{
		return false;
	}
	 
	WaitForSingleObject ((HANDLE)nVal, INFINITE);
	CloseHandle ((HANDLE)nVal);
	return true;
}
bool HTTPRequest::AsyncDoHttpPut()
{
	UINT dwThreadID = 0;
	int nVal = _beginthreadex(NULL, 0, thread_http_put, (void *)this, 0, &dwThreadID);
	if (nVal <= 0)	
	{
		return false;
	}
	 
	WaitForSingleObject ((HANDLE)nVal, INFINITE);
	CloseHandle ((HANDLE)nVal);
	return true;
}
bool HTTPRequest::AsyncDoHttpDelete()
{
	UINT dwThreadID = 0;
	int nVal = _beginthreadex(NULL, 0, thread_http_delete, (void *)this, 0, &dwThreadID);
	if (nVal <= 0)	
	{
		return false;
	}
	 
	WaitForSingleObject ((HANDLE)nVal, INFINITE);
	CloseHandle ((HANDLE)nVal);
	return true;
}
//end namespace OSS
}