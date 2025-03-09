#include "FileAnalyzer.h"

AnalysisResult FileAnalyzer::analyze(const File &file) {
    AnalysisResult res;

    const std::vector<std::string>& tokens = file.getContent().words;
    if (tokens.empty())
        return res;
    res.totalWords = tokens.size();
    
    auto longestFuture = std::async(std::launch::async, computeLongest, std::cref(tokens));
    auto shortestFuture = std::async(std::launch::async, computeShortest, std::cref(tokens));
    
    res.longestWord = longestFuture.get();
    res.shortestWord = shortestFuture.get();
    
    size_t totalLen = std::accumulate(tokens.begin(), tokens.end(), 0UL,
        [](size_t sum, const std::string &w) { return sum + w.size(); });
        
    res.averageWordLength = static_cast<double>(totalLen) / tokens.size();
    
    return res;
}

bool FileAnalyzer::compareStringLength(const std::string &a, const std::string &b) {
    return a.size() < b.size();
}

std::string FileAnalyzer::computeLongest(const std::vector<std::string>& tokens) {
    return *std::max_element(tokens.begin(), tokens.end(), compareStringLength);
}

std::string FileAnalyzer::computeShortest(const std::vector<std::string>& tokens) {
    return *std::min_element(tokens.begin(), tokens.end(), compareStringLength);
}
