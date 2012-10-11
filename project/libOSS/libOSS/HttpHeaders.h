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
using namespace std;
namespace OSS
{
/**
@class HttpHeaders
@brief ¶ÔhttpÍ·Ïà¹Ø×Ö·û´®µÄ·â×°
*/
class OSSDLL_API HttpHeaders
{
public:
	HttpHeaders(void);
	~HttpHeaders(void);
public:

/**
  AUTHORIZATION ×Ö·û´®
 */
static const string AUTHORIZATION;
/**
  CACHE_CONTROL ×Ö·û´®
 */
static const string CACHE_CONTROL;
/**
  CONTENT_DISPOSITION ×Ö·û´®
 */
static const string CONTENT_DISPOSITION;
/**
  CONTENT_ENCODING ×Ö·û´®
 */
static const string CONTENT_ENCODING;
/**
  CONTENT_LENGTH ×Ö·û´®
 */
static const string CONTENT_LENGTH;
/**
  CONTENT_MD5 ×Ö·û´®
 */
static const string CONTENT_MD5;
/**
  CONTENT_TYPE ×Ö·û´®
 */
static const string  CONTENT_TYPE;
/**
  DATE ×Ö·û´®
 */
static const string DATE;
/**
  ETAG ×Ö·û´®
 */
static const string ETAG;
/**
  EXPIRES ×Ö·û´®
 */
static const string EXPIRES;
/**
  HOST ×Ö·û´®
 */
static const string HOST;
/**
  LAST_MODIFIED ×Ö·û´®
 */
static const string LAST_MODIFIED;
/**
  RANGE ×Ö·û´®
 */
static const string RANGE;
/**
  LOCATION ×Ö·û´®
 */
static const string LOCATION;
};
}
