#ifndef AHO_CORASICK_PROJECT_AC_H
#define AHO_CORASICK_PROJECT_AC_H
#include <vector>
#include <string>
#include <ahocorasick/Slice.h>


class TrieNode;
class AcAutomata
{
public:
    explicit AcAutomata(const std::vector<std::string>& patterns);

    ~AcAutomata();

    Slice* search(const char* data, int len);

private:
    void build_trie();

    void build_fail();

    std::vector<std::string> patterns_;
    TrieNode* root_;
};

#endif //AHO_CORASICK_PROJECT_AC_H
