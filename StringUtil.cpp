#include "StringUtil.h"
#include <algorithm>
#include <stdarg.h>
#include <cstring>
#include "han.h"
#include <iostream>

namespace Utils
{
	namespace String
	{

		unsigned int chars2Unicode(const std::string& _string, size_t& _cursor)
		{
			const char&  c      = _string[_cursor];
			unsigned int result = '?';

			if((c & 0x80) == 0) // 0xxxxxxx, one byte character
			{
				// 0xxxxxxx
				result = ((_string[_cursor++]       )      );
			}
			else if((c & 0xE0) == 0xC0) // 110xxxxx, two byte character
			{
				// 0001xxxx


				// 110xxxxx 10xxxxxx
				result = ((_string[_cursor++] & 0x1F) <<  6) |
					((_string[_cursor++] & 0x3F)      );
			}
			else if((c & 0xF0) == 0xE0) // 1110xxxx, three byte character
			{
				// 1110xxxx 10xxxxxx 10xxxxxx
				result = ((_string[_cursor++] & 0x0F) << 12) |
					((_string[_cursor++] & 0x3F) <<  6) |
					((_string[_cursor++] & 0x3F)      );
			}
			else if((c & 0xF8) == 0xF0) // 11110xxx, four byte character
			{
				// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
				result = ((_string[_cursor++] & 0x07) << 18) |
					((_string[_cursor++] & 0x3F) << 12) |
					((_string[_cursor++] & 0x3F) <<  6) |
					((_string[_cursor++] & 0x3F)      );
			}
			else
			{
				// error, invalid unicode
				++_cursor;
			}

			return result;

		} // chars2Unicode
		bool containsIgnoreCasePinyin(const std::string & _string, const std::string & _what)
		{
			std::vector<const char*> vpinyin;
			size_t len = _string.size();
			size_t idx = 0;
			bool ret = false;

			vpinyin.reserve(len);
			while(idx < len) {
				int code = chars2Unicode(_string, idx);
				if (code < 0x80) {
					char tmp[2] = { _string[idx-1], 0};
					std::cout << "dfsdf:" << (tmp) << std::endl;
					std::cout << "aaa:" << s_tblpinyin[_string[idx-1]] << std::endl;
					vpinyin.push_back( s_tblpinyin[_string[idx-1]] );
				} else {
					ret = true;
					auto it = s_mapPinyin.find(code);
					if (it != s_mapPinyin.end()) {
						vpinyin.push_back(it->second);
					} else {
						vpinyin.push_back(NULL);
					}
				}
			}
			if (!ret) return false; // all chars < 0x80

			auto it = std::search(
					vpinyin.begin(), vpinyin.end(),
					_what.begin(), _what.end(),
					[](const char *ptr, char ch2) {
					if (!ptr) return false;
					for(;;) {
					char ch1 = *ptr++;
					if (!ch1) return false;
					if (toupper(ch1) == toupper(ch2)) return true;
					}
					}
					);
			return (it != vpinyin.end());
		}
	}
}
