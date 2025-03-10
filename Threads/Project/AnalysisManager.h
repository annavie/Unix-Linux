#ifndef ANALYSISMANAGER_HPP
#define ANALYSISMANAGER_HPP

#include <vector>
#include <future>
#include <mutex>
#include "Document.h"
#include "DocumentAnalyzer.h"

class AnalysisManager {
public:
    AnalysisManager(std::vector<Document> docs);

    void runAnalysis();

private:
    AnalysisResult analyzeDocument(const Document &doc);

    void printResult(const AnalysisResult &res);

    void printFileResults();

    void printFileResultsForDocument(const Document &doc);

    std::vector<Document> documents;
    std::vector<std::future<AnalysisResult>> futures;
    std::mutex printMutex;
};

#endif 
