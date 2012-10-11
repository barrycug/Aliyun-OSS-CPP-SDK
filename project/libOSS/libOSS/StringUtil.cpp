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
#include "StringUtil.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <clocale>
#include <Windows.h>
namespace OSS
{
StringUtil::StringUtil(void)
{
}


StringUtil::~StringUtil(void)
{
}
string StringUtil::trimQuote(string& s)
{
	 string drop = "\"";
    // trim right
    s.erase(s.find_last_not_of(drop)+1);
    // trim left
	return  s.erase(0,s.find_first_not_of(drop));

}
string StringUtil:: trim(string& s)
{
    string drop = " ";
    // trim right
    s.erase(s.find_last_not_of(drop)+1);
    // trim left
    s.erase(0,s.find_first_not_of(drop));
	drop = "\n";
    // trim right
    s.erase(s.find_last_not_of(drop)+1);
    // trim left
    s.erase(0,s.find_first_not_of(drop));
	drop = "\r";
    // trim right
    s.erase(s.find_last_not_of(drop)+1);
    // trim left
  return  s.erase(0,s.find_first_not_of(drop));

}
vector<string> StringUtil::split(string &s, char delim, vector<string> &elems){
    stringstream ss(s);
    string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
vector<string> StringUtil::splitHeader(string &s, char delim, vector<string> &elems)
{
	int pos =  s.find_first_of(delim);
	if(pos > 0)
	{
		elems.push_back(s.substr(0,pos));
		elems.push_back(s.substr(pos+1,s.size()-pos-1));
	}
	return elems;
}

}
