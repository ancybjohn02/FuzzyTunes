#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Song.hpp"

class FuzzySearchHelper {
public:
    static std::shared_ptr<Song> fuzzy_match(
        const std::string& query,
        const std::unordered_map<std::string, std::shared_ptr<Song>>& title_map
    );

private:
    static std::string normalize(const std::string& input);
    static int levenshtein(const std::string& a, const std::string& b);
};
