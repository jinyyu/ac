#include <ahocorasick/ahocorasick.h>
#include <DebugLog.h>


int main(int argc, char* argv[])
{
    std::vector<std::string> strings;
    strings.emplace_back("he");
    strings.emplace_back("she");
    strings.emplace_back("his");
    strings.emplace_back("hers");

    ACMatcher matcher(strings);


    const char* str = "hehers";

    Slice* slice = matcher.match_any(str, strlen(str));
    if (slice) {
        LOG_DEBUG("ok", slice->to_string().c_str());
    } else {
        LOG_DEBUG("no ok");
    }
}

