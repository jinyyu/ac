#include <ahocorasick/ahocorasick.h>
#include <DebugLog.h>


bool on_match(void* ctx, Slice* slice)
{
    fprintf(stderr, "---on match %s\n", slice->to_string().c_str());
    return false;
}

int main(int argc, char* argv[])
{
    std::vector<std::string> strings;
    strings.emplace_back("aldkjaflksjalfk");
    strings.emplace_back("asdeflksadf");
    strings.emplace_back("his");
    strings.emplace_back("hers");

    AcAutomata matcher(strings);


    const char* str = "asdfsafafasfasfaldkjaflksjalfkhishishersasdeflksadf";

    matcher.search(str, strlen(str),on_match, NULL);

    std::vector<Slice> matches;
    matcher.search_all(str, strlen(str), matches);
    if (matches.empty()) {
        fprintf(stderr, "no match\n");
    } else {
        for (auto it = matches.begin(); it != matches.end(); ++it) {
            fprintf(stderr, "+++match %s\n", it->to_string().c_str());
        }
    }
}

