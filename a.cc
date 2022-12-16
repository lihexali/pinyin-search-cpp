// string::size
#include <iostream>
#include <string>
#include "StringUtil.h"
int main()
{
    bool ret = Utils::String::containsIgnoreCasePinyin("a炉石传说", "lszs");	
    return ret? 0 : 1;
}

