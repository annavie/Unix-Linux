#ifndef FILEANALYZER_H
#define FILEANALYZER_H

#include "DocumentAnalyzer.h"
#include "File.h"
#include <vector>
#include <future>
#include <numeric>
#include <algorithm>
#include <cctype>
#include <string>

class FileAnalyzer {
public:
    AnalysisResult analyze(const File &file);
private:
    static bool compareStringLength(const std::string &a, const std::string &b);
    static std::string computeLongest(const std::vector<std::string>& tokens);
    static std::string computeShortest(const std::vector<std::string>& tokens);
};

#endif
