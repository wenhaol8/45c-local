#include "mapset.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <ranges>

std::string to_lowercase(const std::string& str) {
    std::string lowercased;
    std::ranges::transform(str, std::back_inserter(lowercased),
                           [](unsigned char c) { return std::tolower(c); });
    return lowercased;
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> stopwords_set;
    std::string word;
    while (stopwords >> word) {
        stopwords_set.insert(to_lowercase(word));
    }
    return stopwords_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::string word;
    while (document >> word) {
        word = to_lowercase(word);
        if (!stopwords.contains(word)) {
            ++word_counts[word];
        }
    }
    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << "\n";
    }
}