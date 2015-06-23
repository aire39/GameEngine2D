#pragma once

#include <string>
#include <sstream>
#include <stdio.h>
#ifndef __WIN32__
#include <cstring>
#endif

inline std::string convertDouble(double value) {
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

inline void convert_string_tolower(std::string &str)
{
    for(int i=0; i<(int)str.length(); i++)
        str[i] = tolower(str.c_str()[i]);
}

inline bool is_forard_slash_dir(const std::string & str)
{
    #ifndef MINGW4
        if( strchr(str.c_str(), '/') != NULL )
            return true;
    #else
        if( str.find_first_of('/') != NULL )
            return true;
    #endif

	return false;
}

inline void foward_slash_dir(std::string & str)
{
	for(int i=0; i<(int)str.length(); i++)
		if( str[i] == '\\' )
			str[i] = '/';
}
