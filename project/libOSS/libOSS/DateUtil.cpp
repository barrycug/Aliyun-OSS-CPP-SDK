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
#include "DateUtil.h"
#include <time.h>
#include "strptime.h"
namespace OSS
{
DateUtil::DateUtil(void)
{
//	strftime();
}

DateUtil::~DateUtil(void)
{
}
string DateUtil::formatRfc822Date(tm &time)
{
	string rtnString;
	char tmpbuf[128];
    // Convert to time structure and adjust for PM if necessary. 
	/*
    err = _gmtime64_s( &today, &ltime );
	*/
 	
    strftime( tmpbuf, 128,
         "%a, %d %b %Y %X GMT", &time );
	rtnString+=tmpbuf;
	return rtnString;
}
tm DateUtil::parseRfc822Date(string strDate)
{
	char *format = "EEE, dd MM yyyy HH:mm:ss z";
	tm time;
	strptime(strDate.c_str(),format,&time);
	return time;
}
tm DateUtil::parseIso8601Date(string strDate)
{
	char *format = "yyyy-MM-dd'T'HH:mm:ss'Z'";
	tm time;
	strptime(strDate.c_str(),format,&time);
	return time;
}
}
