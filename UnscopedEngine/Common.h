#pragma once

//types
#include<cstdint>
#include<string>
#include<unordered_map>
#include<map>
#include<list>
#include<tuple>

//streams
#include<iostream>
#include<fstream>
#include<sstream>

//Utilities
#include<chrono>
#include<functional>
#include<locale>
#include<codecvt>
#include<cmath>

#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<DirectXMath.h>

#define API_FAILED(returnValue) returnValue == FALSE


//(const char*,const char*,const char*,int,HRESULT)
#define _LOGMSG(message,file,function,line,hresult) \
{\
	throw std::exception(message);\
}

#define LOGMSG(message,hresult) _LOGMSG(message,__FILE__, __FUNCTION__, __LINE__,hresult)

inline std::string ToString(const std::wstring& str)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
}
