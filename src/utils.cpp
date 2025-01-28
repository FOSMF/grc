#include "utils.hpp"

namespace GRC {

    int Utils::is_similar(const std::string &w1, const std::string &w2) {
        int len1 = w1.size();
        int len2 = w2.size();

        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

        for (int i = 0; i <= len1; i++) dp[i][0] = i;
        for (int j = 0; j <= len2; j++) dp[0][j] = j;

        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                int cost = (w1[i - 1] == w2[j - 1]) ? 0 : 1;

                dp[i][j] = std::min({
                    dp[i - 1][j] + 1,
                    dp[i][j - 1] + 1,
                    dp[i - 1][j - 1] + cost
                });

                if (i > 1 && j > 1 && w1[i - 1] == w2[j - 2] && w1[i - 2] == w2[j - 1]) {
                    dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + cost);
                }
            }
        }

        int bonus = 0;
        for (int i = 0; i < std::min(len1, len2); i++) {
            if (w1[i] == w2[i]) {
                bonus -= 2;
            }
        }

        return dp[len1][len2] + bonus;
    }

    std::string Utils::find_closest_word(const std::vector<std::string> &words, const std::string &word) {
        int minDistance = std::numeric_limits<int>::max();
        std::string closest_word;

        for (const std::string &key : words) {
            int distance = is_similar(word, key);
            if (distance < minDistance) {
                minDistance = distance;
                if (distance <= 2) closest_word = key;
            }
        }

        return closest_word;
    }

}