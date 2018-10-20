#include <ac/ac.h>
#include <DebugLog.h>


int main(int argc, char* argv[])
{
    std::vector<std::string> strings;
    strings.emplace_back("hesf");
    strings.emplace_back("abcdef");

    ACMatcher matcher(strings);


    const char* str = "hers";

    Slice* slice = matcher.match_any(str, strlen(str));
    if (slice) {
        LOG_DEBUG("ok", slice->to_string().c_str());
    } else {
        LOG_DEBUG("no ok");
    }
}

