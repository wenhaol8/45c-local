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
    std::istream_iterator<std::string> it(stopwords), end;
    std::transform(it, end, std::inserter(stopwords_set, stopwords_set.end()), to_lowercase);
    return stopwords_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::istream_iterator<std::string> it(document), end;
    std::for_each(it, end, [&word_counts, &stopwords](const std::string& word) {
        std::string lower_word = to_lowercase(word);
        if (!stopwords.contains(lower_word)) {
            ++word_counts[lower_word];
        }
    });
    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    std::for_each(word_counts.begin(), word_counts.end(), [&output](const auto& pair) {
        output << pair.first << " " << pair.second << "\n";
    });
}