#include <ahocorasick/ahocorasick.h>
#include <DebugLog.h>


int main(int argc, char* argv[])
{
    std::vector<std::string> strings;
    strings.emplace_back("aldkjaflksjalfk");
    strings.emplace_back("asdeflksadf");
    strings.emplace_back("his");
    strings.emplace_back("hers");

    AcAutomata matcher(strings);


    const char* str = "hehers";

    Slice* slice = matcher.search(str, strlen(str));
    if (slice) {
        LOG_DEBUG("ok ---------- %s", slice->to_string().c_str());
    } else {
        LOG_DEBUG("no ok");
    }
}

