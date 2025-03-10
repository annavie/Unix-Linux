#include "AnalysisManager.h"
#include "CompositeDocumentAnalyzer.h"
#include "FileAnalyzer.h"
#include <iostream>
#include <future>

AnalysisManager::AnalysisManager(std::vector<Document> docs)
    : documents(std::move(docs))
{ }

void AnalysisManager::runAnalysis() {
    for (auto &doc : documents) {
        futures.push_back(std::async(std::launch::async,
                                      &AnalysisManager::analyzeDocument,
                                      this, doc));
    }

    for (auto &f : futures) {
        AnalysisResult res = f.get();
        printResult(res);
    }

    printFileResults();
}

AnalysisResult AnalysisManager::analyzeDocument(const Document &doc) {
    CompositeDocumentAnalyzer analyzer;
    return analyzer.analyze(doc);
}

void AnalysisManager::printResult(const AnalysisResult &res) {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << "[Aggregated Document Analysis]\n"
              << "  Total Words: " << res.totalWords << "\n"
              << "  Longest Word: " << res.longestWord << "\n"
              << "  Shortest Word: " << res.shortestWord << "\n"
              << "  Average Word Length: " << res.averageWordLength << "\n\n";
}

void AnalysisManager::printFileResults() {
    std::lock_guard<std::mutex> lock(printMutex);
    for (const auto &doc : documents) {
        printFileResultsForDocument(doc);
    }
}

void AnalysisManager::printFileResultsForDocument(const Document &doc) {
    FileAnalyzer fileAnalyzer;
    const DocumentContent &dc = doc.getContent();
    
    for (const auto &f : dc.files) {
        AnalysisResult fileRes = fileAnalyzer.analyze(f);
        std::cout << "[File Analysis] " << f.getFileName() << "\n"
                  << "  Total Words: " << fileRes.totalWords << "\n"
                  << "  Longest Word: " << fileRes.longestWord << "\n"
                  << "  Shortest Word: " << fileRes.shortestWord << "\n"
                  << "  Average Word Length: " << fileRes.averageWordLength << "\n\n";
    }
    
    for (const auto &subDocPtr : dc.documents) {
        printFileResultsForDocument(*subDocPtr);
    }
}
