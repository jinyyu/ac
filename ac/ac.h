#ifndef AHO_CORASICK_PROJECT_AC_H
#define AHO_CORASICK_PROJECT_AC_H
#include <vector>
#include <string>


class TrieNode;
class ACMatcher
{
public:
    explicit ACMatcher(const std::vector<std::string>& strings);

    ~ACMatcher();

private:
    void build_trie();

    std::vector<std::string> strings_;
    TrieNode* root_;
};

#endif //AHO_CORASICK_PROJECT_AC_H
