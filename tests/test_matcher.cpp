#include <ac/ac.h>
#include <DebugLog.h>


int main(int argc, char* argv[])
{
    std::vector<std::string> strings;
    strings.emplace_back("he");
    strings.emplace_back("she");
    strings.emplace_back("her");
    strings.emplace_back("hers");
    strings.emplace_back("his");

    ACMatcher matcher(strings);


    const char* str = "iiiiiiiiiiiiiiiiiiheo";

    Slice* slice = matcher.search(str, strlen(str));
    if (slice) {
        LOG_DEBUG("ok", slice->to_string().c_str());
    } else {
        LOG_DEBUG("no ok");
    }
}

