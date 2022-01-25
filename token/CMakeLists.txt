# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}")

add_library(Token
        unused_rule_token/unused_rule_token.cpp
        unused_rule_token/colon_token.cpp
        unused_rule_token/comma_token.cpp
        unused_rule_token/keyword_token.cpp
        unused_rule_token/unknown_token.cpp
        prefix_symbol_token/boolean_prefix_token.cpp
        prefix_symbol_token/left_brace_token.cpp
        prefix_symbol_token/left_paren_token.cpp
        prefix_symbol_token/literal_prefix_token.cpp
        prefix_symbol_token/null_token.cpp
        prefix_symbol_token/super_token.cpp
        prefix_symbol_token/this_token.cpp)
