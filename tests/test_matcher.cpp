#include <ac/ac.h>


int main(int argc, char* argv[])
{
    std::vector<std::string> strings;
    strings.emplace_back("he");
    strings.emplace_back("she");
    strings.emplace_back("her");

    ACMatcher matcher(strings);
}

