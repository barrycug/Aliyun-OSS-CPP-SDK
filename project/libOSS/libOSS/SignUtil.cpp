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
#include "SignUtil.h"
#include "OSSUtil.h"
namespace OSS
{
string SignUtil::s_signedParamters[12] = {"group","delete","acl","uploadId","partNumber","uploads", "response-cache-control","response-content-disposition","response-content-encoding", "response-content-language","response-content-type","response-expires" };
SignUtil::SignUtil(void)
{
}


SignUtil::~SignUtil(void)
{
}

string SignUtil::buildCanonicalString(HttpMethod httpMethod,string &resourcepath,RequestMessage &rm)
{
	string rtnString = "";
	string strMethod = OSSUtil::HttpMethod2String(httpMethod);
	rtnString+=strMethod;
	rtnString+="\n";
	map<string,string> passHeaders;
	map<string,string>::iterator iter;
	map<string,string> headers = rm.getHeaders();
	string str="";
	if(headers.size() > 0)
	{
		for(iter = headers.begin();iter != headers.end();iter++)
		{
			string strKey =iter->first;
			int j = strKey.find_first_of("x-oss-");
			if(strKey.compare("Content-Type") == 0 ||
				strKey.compare("Content-MD5") == 0 ||
				strKey.compare("Date") == 0 ||
				j == 0)
			{
				passHeaders.insert(map<string, string> :: value_type(iter->first,iter->second));
				
			}
		}
		iter = passHeaders.find("Content-Type");
		if(iter == passHeaders.end())
		{
			passHeaders.insert(map<string, string> :: value_type("Content-Type",""));
		}
		iter = passHeaders.find("Content-MD5");
		if(iter == passHeaders.end())
		{
			passHeaders.insert(map<string, string> :: value_type("Content-MD5",""));
		}
		if(rm.parameters.size() >0)
		{
			for(iter = rm.parameters.begin();iter != rm.parameters.end();iter++)
			{
				string strKey =iter->first;
				int j = strKey.find_first_of("x-oss-");
				if(j == 0)
				{
					passHeaders.insert(map<string, string> :: value_type(iter->first,iter->second));				
				}
			}
		}
		for(iter = passHeaders.begin();iter != passHeaders.end();iter++)
		{
			string strKey =iter->first;
			int j = strKey.find_first_of("x-oss-");
			if(j == 0)
			{
				rtnString += strKey	;	
				rtnString += ":";
				rtnString += iter->second;
			}
			else
			{
				rtnString += iter->second;
			}
			rtnString += "\n";
		}
		rtnString += SignUtil::buildCanonicalizeResourcePath(resourcepath,rm.parameters);
	}
	return rtnString;
}
string SignUtil::buildCanonicalizeResourcePath(string resourcepath,map<string,string>params)
{
	string rtnString = "";
	rtnString+=resourcepath;
	if(params.size() >0)
	{
		string c="?";
		map<string,string>::iterator iter;
		for(iter = params.begin();iter != params.end();iter++)
		{
			if(!SignUtil::isStringInArray(iter->first))
			{
				continue;
			}
			rtnString+=c;
			rtnString+=iter->first;
			string strValue = iter->second;
			if(!strValue.empty())
			{
				rtnString+="=";
				rtnString+=strValue;
			}
			c = "&";
		}
	}
	return rtnString;
}
bool SignUtil::isStringInArray(string str)
{
	bool rtnBool = false;
	for(int i =0;i<12;i++)
	{
		if(str.compare(s_signedParamters[i]) == 0)
		{
			return true;
		}
	}
	return false;

}
}
