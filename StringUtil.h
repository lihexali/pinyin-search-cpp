#include <string>
#include <cstring>
#include <vector>

namespace Utils
{
	namespace String
	{
		unsigned int chars2Unicode      (const std::string& _string, size_t& _cursor);
		bool        containsIgnoreCasePinyin(const std::string & _string, const std::string & _what);
		

	}
}
