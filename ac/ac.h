#ifndef AHO_CORASICK_PROJECT_AC_H
#define AHO_CORASICK_PROJECT_AC_H
#include <vector>
#include <string>
#include <ac/Slice.h>


class TrieNode;
class ACMatcher
{
public:
    explicit ACMatcher(const std::vector<std::string>& strings);

    ~ACMatcher();

    Slice* search(const char* data, int len);

private:
    void build_trie();

    void build_fail();

    std::vector<std::string> strings_;
    TrieNode* root_;
};

#endif //AHO_CORASICK_PROJECT_AC_H
