#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H

#include "CompositeDocumentAnalyzer.h"
#include "Document.h"
#include "FileAnalyzer.h"
#include <vector>
#include <future>
#include <mutex>
#include <iostream>

class AnalysisManager {
public:
    AnalysisManager(std::vector<Document> docs);
    void runAnalysis();
private:
    std::vector<Document> documents;
    std::vector<std::future<AnalysisResult>> futures;
    std::mutex printMutex;
    AnalysisResult analyzeDocument(const Document &doc);
    void printResult(const AnalysisResult &res);
    void printFileResults();
};

#endif // ANALYSISMANAGER_H
