#include "stdafx.h"
#include "string_utility.h"
#include <sstream>
#include <iomanip>
#include <stdarg.h>
#include <wchar.h>
#include <algorithm>

extern const std::string EmptyString;

//////////////////////////////////////////////////////////////////////////
StringVector split(std::string src, std::string::size_type limit)
	{
	StringVector v;

	std::string::iterator i = src.begin(), last = i;
	for (; i != src.end(); i++)
		{
		if (*i == ' ' || *i == '\n' || *i == '\t' || *i == '\r')
			{
			if (i + 1 != src.end() && (i[1] == ' ' || i[1] == '\n' || i[1] == '\t' || i[1] == '\r'))
				continue;
			v.push_back(std::string(last, i));
			last = i + 1;
			if (v.size() >= limit - 1)
				{
				v.push_back(std::string(last, src.end()));
				return v;
				}
			}
		}

	if (last != i)
		v.push_back(std::string(last, i));

	return v;
	};

//////////////////////////////////////////////////////////////////////////
StringVector split(std::string src, std::string::value_type separator, std::string::size_type limit)
	{
	StringVector v;

	std::string::iterator i = src.begin(), last = i;
	for (; i != src.end(); i++)
		{
		if (*i == separator)
			{
			v.push_back(std::string(last, i));
			last = i + 1;
			if (v.size() >= limit - 1)
				{
				v.push_back(std::string(last, src.end()));
				return v;
				}
			}
		}

	if (last != i)
		v.push_back(std::string(last, i));

	return v;
	};

//////////////////////////////////////////////////////////////////////////
StringVector split(std::string src, std::string separator, std::string::size_type limit)
	{
	StringVector v;

	std::string::iterator i = src.begin(), last = i;
	for (; i != src.end(); i++)
		{
		if (std::string(i, i + separator.length()) == separator)
			{
			v.push_back(std::string(last, i));
			last = i + separator.length();

			if (v.size() >= limit - 1)
				{
				v.push_back(std::string(last, src.end()));
				return v;
				}
			}
		}

	if (last != i)
		v.push_back(std::string(last, i));

	return v;
	};

//////////////////////////////////////////////////////////////////////////
StringVector chunk_split(std::string src, std::string::size_type chunklen)
	{
	StringVector retval;
	retval.reserve(src.size() / chunklen + 1);

	std::string::size_type count = 0;
	std::string::iterator i = src.begin(), last = i;
	for (; i != src.end(); i++, count++)
		{
		if (count == chunklen)
			{
			count = 0;
			retval.push_back(std::string(last, i));
			last = i;
			}
		}

	if (last != i)
		retval.push_back(std::string(last, i));

	return retval;
	};

//////////////////////////////////////////////////////////////////////////
template <class InputIterator>
std::string join(const std::string &glue, InputIterator first, InputIterator last)
	{
	std::string retval;

	for (; first != last; first++)
		{
		retval.append(*first);
		retval.append(glue);
		}
	retval.erase(retval.length() - glue.length());

	return retval;
	};

//////////////////////////////////////////////////////////////////////////
template <class InputIterator>
std::string join(std::string::value_type glue, InputIterator first, InputIterator last)
	{
	std::string retval;

	for (; first != last; first++)
		{
		retval.append(*first);
		retval.append(1, glue);
		}
	retval.erase(retval.length() - 1);

	return retval;
	};

//////////////////////////////////////////////////////////////////////////
std::string replace(std::string src, std::string &needle, std::string &s)
	{
	std::string::size_type
		lastpos = 0,
		thispos;

	while ((thispos = src.find(needle, lastpos)) != std::string::npos)
		{
		src.replace(thispos, needle.length(), s);
		lastpos = thispos + 1;
		}
	return src;
	};

//////////////////////////////////////////////////////////////////////////
std::string replace(std::string src, std::string::value_type needle, std::string::value_type c)
	{
	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		if (*i == needle)
			*i = c;

	return src;
	};

/*
//////////////////////////////////////////////////////////////////////////
std::string tolower(std::string src)
	{
	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		if (*i >= 'A' && *i <= 'Z')
			*i = (*i) + ('a' - 'A');
	return src;
	};
*/

/*
//////////////////////////////////////////////////////////////////////////
std::string toupper(std::string src)
	{
	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		if (*i >= 'a' && *i <= 'z')
			*i = (*i) - ('a' - 'A');
	return src;
	};
*/

//////////////////////////////////////////////////////////////////////////
std::string::size_type count(std::string src, std::string &str)
	{
	std::string::size_type count = 0, last = 0, cur = 0;

	while ((cur = src.find(str, last + 1)) != std::string::npos)
		{
		count++;
		last = cur;
		}

	return count;
	};

//////////////////////////////////////////////////////////////////////////
bool is_alnum(std::string src)
	{
	if (src.length() == 0)
		return false;

	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		{
		if (*i < 'A' || *i > 'Z')
			if (*i < '0' || *i > '9')
				if (*i < 'a' || *i > 'z')
					return false;
		}

	return true;
	};

//////////////////////////////////////////////////////////////////////////
bool is_alpha(std::string src)
	{
	if (src.length() == 0)
		return false;

	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		if (*i < 'A' || (*i > 'Z' && (*i < 'a' || *i > 'z')))
			return false;

	return true;
	};

//////////////////////////////////////////////////////////////////////////
bool is_numeric(std::string src)
	{
	if (src.length() == 0)
		return false;

	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		if (*i < '0' || *i > '9')
			return false;

	return true;
	};

//////////////////////////////////////////////////////////////////////////
bool is_lower(std::string src)
	{
	if (src.length() == 0)
		return false;

	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		if (*i < 'a' || *i < 'z')
			return false;

	return true;
	};

//////////////////////////////////////////////////////////////////////////
bool is_upper(std::string src)
	{
	if (src.length() == 0)
		return false;

	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		if (*i < 'A' || *i > 'Z')
			return false;

	return true;
	};

//////////////////////////////////////////////////////////////////////////
std::string swapcase(std::string src)
	{
	for (std::string::iterator i = src.begin(); i != src.end(); i++)
		if (*i >= 'A' && *i <= 'Z')
			*i += ('a' - 'A');
		else if (*i >= 'a' && *i <= 'z')
			*i -= ('a' - 'A');

	return src;
	};

//////////////////////////////////////////////////////////////////////////
void trim(std::string& str, const std::string & ChrsToTrim, TrimDirection TrimDir)
	{
	size_t startIndex = str.find_first_not_of(ChrsToTrim);
	if (startIndex == std::string::npos)
		{ 
		str.erase(); 
		return;
		}

	if ((TrimDir == TrimDirection::Right) || (TrimDir == TrimDirection::Both))
		str = str.substr(startIndex, str.size() - startIndex);

	if ((TrimDir == TrimDirection::Left) || (TrimDir == TrimDirection::Both))
		str = str.substr(0, str.find_last_not_of(ChrsToTrim) + 1);
	}

//////////////////////////////////////////////////////////////////////////
inline void trim_right(std::string& str, const std::string & ChrsToTrim)
	{
	trim(str, ChrsToTrim, TrimDirection::Right);
	}

//////////////////////////////////////////////////////////////////////////
inline void trim_left(std::string& str, const std::string & ChrsToTrim)
	{
	trim(str, ChrsToTrim, TrimDirection::Left);
	}

//////////////////////////////////////////////////////////////////////////
bool get_line(char * pBuffer, char * end_of_buffer, char** curPos, std::string &curLine)
	{
	curLine.clear();

	if ((*curPos) >= end_of_buffer)
		return false;

	while ((*curPos)<end_of_buffer)
		{
		if (**curPos == '\n')
			{
			(*curPos)++;
			break;
			}
		curLine += (**curPos);
		(*curPos)++;
		}
	return ((*curPos)<end_of_buffer);
	}

//////////////////////////////////////////////////////////////////////////
bool case_ins_char_compare(char a, char b)
	{
	return(::toupper(a) == ::toupper(b));
	}

//////////////////////////////////////////////////////////////////////////
bool case_ins_compare(const std::string& s1, const std::string& s2)
	{
	bool rt = ((s1.size() == s2.size()) && std::equal(s1.begin(), s1.end(), s2.begin(), case_ins_char_compare));
	return rt;
	}

//////////////////////////////////////////////////////////////////////////
std::wstring string_to_wstring(const std::string & src)
	{
	std::wstring res;
	res.assign(src.begin(), src.end());
	return res;
	}

//////////////////////////////////////////////////////////////////////////
std::wstring string_to_wstring(const char * src)
	{
	if (src == nullptr)
		src = "";

	std::string s = src;
	return string_to_wstring(s);
	}

//////////////////////////////////////////////////////////////////////////
std::string wstring_to_string(const std::wstring & src)
	{
	std::string res;
	res.assign(src.begin(), src.end());
	return res;
	}

//////////////////////////////////////////////////////////////////////////
std::string wstring_to_string(const wchar_t * src)
	{
	if (src == nullptr)
		src = L"";

	std::wstring s = src;
	return wstring_to_string(s);
	}

//////////////////////////////////////////////////////////////////////////
std::string string_format(const std::string fmt, ...)
	{
	int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
	std::string str;
	va_list ap;
	while (1) {     // Maximum two passes on a POSIX system...
		str.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf((std::string::value_type *)str.data(), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) {  // Everything worked
			str.resize(n);
			return str;
			}
		if (n > -1)  // Needed size returned
			size = n + 1;   // For null char
		else
			size *= 2;      // Guess at a larger size (OS specific)
		}
	return str;
	}

//////////////////////////////////////////////////////////////////////////
std::wstring wstring_format(const std::wstring fmt, ...)
	{
	int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
	std::wstring str;
	va_list ap;
	while (1) {     // Maximum two passes on a POSIX system...
		str.resize(size);
		va_start(ap, fmt);
#ifdef _WIN32        
		int n = _vsnwprintf_s((std::wstring::value_type *)str.data(), str.size(), size, fmt.c_str(), ap);
#else
		int n = vswprintf((std::wstring::value_type *)str.data(), size, fmt.c_str(), ap);
#endif
		va_end(ap);
		if (n > -1 && n < size) {  // Everything worked
			str.resize(n);
			return str;
			}
		if (n > -1)  // Needed size returned
			size = n + 1;   // For null char
		else
			size *= 2;      // Guess at a larger size (OS specific)
		}
	return str;
	}

//////////////////////////////////////////////////////////////////////////
std::string bytes_to_hex_string(const std::vector<uint8_t> & buffer, int max, bool trailing_dots)
	{
    return bytes_to_hex_string(buffer.data(), buffer.size(), max, trailing_dots);
	}

//////////////////////////////////////////////////////////////////////////
std::string bytes_to_hex_string(const uint8_t * data, size_t len, int max, bool trailing_dots)
    {
    std::ostringstream ss;

    // convert header to a string
    int real_len = len;
    if (max != -1)
        real_len = ((int)len < max) ? (int)len : max;

    for (int a = 0; a < real_len; a++)
        ss << std::hex << std::setw(2) << std::uppercase << std::setfill('0') << (unsigned)data[a];

    if (trailing_dots && (real_len != len))
        ss << "...";

    return ss.str();
    }

//////////////////////////////////////////////////////////////////////////
std::wstring bytes_to_hex_wstring(const std::vector<uint8_t> & buffer, int max, bool trailing_dots)
	{
    return bytes_to_hex_wstring(buffer.data(), buffer.size(), max, trailing_dots);
    }

//////////////////////////////////////////////////////////////////////////
std::wstring bytes_to_hex_wstring(const uint8_t * data, size_t len, int max, bool trailing_dots)
    {
    std::wostringstream ss;

    // convert header to a string
    int real_len = len;
    if (max != -1)
        real_len = ((int)len < max) ? (int)len : max;

    for (int a = 0; a < real_len; a++)
        ss << std::hex << std::setw(2) << std::uppercase << std::setfill(wchar_t(0)) << (unsigned)data[a];

    if (trailing_dots && (real_len != len))
        ss << "...";

    return ss.str();
    }

//////////////////////////////////////////////////////////////////////////
std::size_t hex_string_to_bytes(std::string source, std::vector<uint8_t> & buffer)
	{
	for (std::size_t i = 0; i < source.length(); i += 2)
		{
		std::string byteString = source.substr(i, 2);
		char byte = (char)strtol(byteString.c_str(), NULL, 16);
		buffer.push_back(byte);
		}
	return buffer.size();
	}

//////////////////////////////////////////////////////////////////////////
std::size_t hex_wstring_to_bytes(std::wstring source, std::vector<uint8_t> & buffer)
	{
	for (std::size_t i = 0; i < source.length(); i += 2)
		{
		std::wstring byteString = source.substr(i, 2);
		char byte = (char)wcstol(byteString.c_str(), NULL, 16);
		buffer.push_back(byte);
		}
	return buffer.size();
	}




