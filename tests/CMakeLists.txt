set(LIBS ${LIBS} ahocorasick)

add_executable(test_debug test_debug.cpp)
target_link_libraries(test_debug ${LIBS})


add_executable(test_trie test_trie.cpp)
target_link_libraries(test_trie ${LIBS})


add_executable(test_matcher test_matcher.cpp)
target_link_libraries(test_matcher ${LIBS})