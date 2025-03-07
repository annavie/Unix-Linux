#ifndef DOCUMENTANALYZER_H
#define DOCUMENTANALYZER_H

#include "Document.h"

struct AnalysisResult {
    size_t totalWords = 0;
    std::string longestWord;
    std::string shortestWord;
    double averageWordLength = 0.0;

};

class DocumentAnalyzer {
public:
    virtual ~DocumentAnalyzer() = default;
    virtual AnalysisResult analyze(const Document &doc) = 0;
};

#endif
