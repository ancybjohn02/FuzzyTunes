#include "../include/FuzzyHelper.hpp"
#include <algorithm>
#include <cctype>
#include <limits>

std::string FuzzySearchHelper::normalize(const std::string& input) {
    std::string normalized;
    std::transform(input.begin(), input.end(), std::back_inserter(normalized),
                   [](unsigned char c) { return std::tolower(c); });
    return normalized;
}

int FuzzySearchHelper::levenshtein(const std::string& a, const std::string& b) {
    // Optional: Simple Levenshtein distance
    const size_t m = a.size(), n = b.size();
    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1));

    for (size_t i = 0; i <= m; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= n; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            int cost = (a[i-1] == b[j-1]) ? 0 : 1;
            dp[i][j] = std::min({ 
                dp[i-1][j] + 1, 
                dp[i][j-1] + 1, 
                dp[i-1][j-1] + cost 
            });
        }
    }

    return dp[m][n];
}

std::shared_ptr<Song> FuzzySearchHelper::fuzzy_match(
    const std::string& query,
    const std::unordered_map<std::string, std::shared_ptr<Song>>& title_map
) {
    std::string normalized_query = normalize(query);
    std::shared_ptr<Song> best_match = nullptr;
    int best_score = std::numeric_limits<int>::max();

    for (const auto& [title, song_ptr] : title_map) {
        std::string normalized_title = normalize(title);

        // First try substring match
        if (normalized_title.find(normalized_query) != std::string::npos) {
            return song_ptr;
        }

        // Then try fuzzy match
        int distance = levenshtein(normalized_query, normalized_title);
        if (distance < best_score) {
            best_score = distance;
            best_match = song_ptr;
        }
    }

    return best_match;
}
