//////////////////////////////////////////////////////////////////////////
//
//  Cpp Enumeration Utility
//
//////////////////////////////////////////////////////////////////////////
//
// 	Author  : Denis Brachet
//  Date    : 03/11/2014
//  License : WTFPL � (http://www.wtfpl.net/)
//
//////////////////////////////////////////////////////////////////////////
// This is an utility to transform enums to and from strings.
// Here's a quick example on how to use the utility:
//
// Declare an enum (in .h):
//   enum class MyEnum { a, b, c };
// 
// Make the enum visible to the utility (in .h):
//    DECLARE_ENUM_ENTRY(MyEnum);
//
// Give the utility the texts for the enum value (in .cpp):
//    
//    DEFINE_ENUM_ENTRY_BEGIN(MyEnum)
//    DEFINE_ENUM_ENTRY(MyEnum::a, "A_Value")
//    DEFINE_ENUM_ENTRY(MyEnum::b, "B_Value")
//    DEFINE_ENUM_ENTRY(MyEnum::c, "C_Value")
//    DEFINE_ENUM_ENTRY_END()
//
// From now it will be possible to convert the enum values to and from 
// std::string using stream operators (<<, >>).
// You could use it to serialize enum in json or xml or whatever you want!
//
//////////////////////////////////////////////////////////////////////////

#ifndef __ENUM_UTILITY_H__
#define __ENUM_UTILITY_H__

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//////////////////////////////////////////////////////////////////////////
//! Maps a value to a text
struct EnumEntry {
    EnumEntry() : m_Value(0) {}
    EnumEntry(int value, std::string text) : m_Value(value), m_Text(text) {}
    int				m_Value;
    std::string		m_Text;
    };

typedef std::vector<EnumEntry> EnumEntries;

//////////////////////////////////////////////////////////////////////////
//! Base struct for type->map mapping. 
//! Specialize using REGISTER_ENUM_MAP_ENTRY in header files
template<typename T> struct EnumTypeToMap { static EnumEntries * GetMapEntry() { return nullptr; } };

//////////////////////////////////////////////////////////////////////////
//! Helper macros for registering enum texts and stream opertators
#define MAKE_MAP_NAME(__type)				__type ## _Map

#define DECLARE_ENUM_ENTRY(__type)			extern EnumEntries MAKE_MAP_NAME(__type); \
											template<> struct EnumTypeToMap< __type > { static EnumEntries * GetMapEntry() { return & MAKE_MAP_NAME(__type); }; };

#define DECLARE_STREAM_OPERATORS(__type)	std::ostream & operator << (std::ostream & ss, const __type & v); \
											std::istream & operator >> (std::istream & ss, __type & v);

#define DECLARE_ENUM(__type)				DECLARE_ENUM_ENTRY(__type) \
											DECLARE_STREAM_OPERATORS(__type)

#define DEFINE_STREAM_OPERATORS(__type)		std::ostream & operator << (std::ostream & ss, const __type & v) { ss << EnumMapper::GetText(v); return ss;} \
											std::istream & operator >> (std::istream & ss, __type & v) { std::string vv; ss >> vv; EnumMapper::GetEnumValue< __type >(vv, v); return ss; }

#define DECLARE_ENUM_ENTRY_MAP(__type)		EnumEntries MAKE_MAP_NAME(__type) {


#define DEFINE_ENUM_ENTRY_BEGIN(__type)		DEFINE_STREAM_OPERATORS(__type) \
											DECLARE_ENUM_ENTRY_MAP(__type)


#define DEFINE_ENUM_ENTRY(__value, __text)	EnumEntry((int)__value, __text),

#define DEFINE_ENUM_ENTRY2(__enum, __value)	EnumEntry((int)__enum::__value, #__value),

#define DEFINE_ENUM_ENTRY_END()				};


//////////////////////////////////////////////////////////////////////////
//! Utility class used to serialize and deserialize enum values to and from string
struct EnumMapper {
    //! Converts the given text into corresponding enum value and saves the result into result_value
    template<typename T>
    static bool GetEnumValue(std::string text, T & result_value) {
        EnumEntries & entries = *EnumTypeToMap<T>::GetMapEntry();
        EnumEntries::iterator it = std::find_if(entries.begin(), entries.end(), [&](EnumEntry & v) { return v.m_Text == text; });
        if (it != entries.end()) {
            result_value = static_cast<T>((*it).m_Value);
            return true;
            }
        return false;
        }
    //! Converts the given enum value into corresponding text saves the result into result_value
    template<typename T>
    static bool GetEnumText(T value, std::string & result_value) {
        EnumEntries & entries = *EnumTypeToMap<T>::GetMapEntry();
        EnumEntries::iterator it = std::find_if(entries.begin(), entries.end(), [&](EnumEntry & v) { return v.m_Value == static_cast<int>(value); });
        if (it != entries.end()) {
            result_value = (*it).m_Text;
            return true;
            }
        return false;
        }
    //! Quick conversion from value to text
    template<typename T>
    static std::string GetText(T value, std::string default_value = "") {
        EnumEntries & entries = *EnumTypeToMap<T>::GetMapEntry();
        EnumEntries::iterator it = std::find_if(entries.begin(), entries.end(), [&](EnumEntry & v) { return v.m_Value == static_cast<int>(value); });
        if (it != entries.end())
            default_value = (*it).m_Text;
        return default_value;
        }
    //! Quick conversion from value to text
    template<typename T>
    static T GetValue(std::string value, T default_value = (T)0) {
        T ret(default_value);
        EnumEntries & entries = *EnumTypeToMap<T>::GetMapEntry();
        EnumEntries::iterator it = std::find_if(entries.begin(), entries.end(), [&](EnumEntry & v) { return v.m_Text == value; });
        if (it != entries.end())
            ret = static_cast<T>((*it).m_Value);
        return ret;
        }

    //! Quick conversion from value to text
    static std::string GetText(int value, EnumEntries * entries, std::string default_value = "") {
        EnumEntries::iterator it = std::find_if(entries->begin(), entries->end(), [&](EnumEntry & v) { return v.m_Value == value; });
        if (it != entries->end())
            default_value = (*it).m_Text;
        return default_value;
        }
    //! Quick conversion from value to text
    static int GetValue(std::string value, EnumEntries * entries, int default_value = 0) {
        int ret(default_value);
        EnumEntries::iterator it = std::find_if(entries->begin(), entries->end(), [&](EnumEntry & v) { return v.m_Text == value; });
        if (it != entries->end())
            ret = ((*it).m_Value);
        return ret;
        }

    };


#endif // __ENUM_UTILITY_H__
