#include "CompositeDocumentAnalyzer.h"

AnalysisResult CompositeDocumentAnalyzer::analyze(const Document &doc) {
    AnalysisResult aggregated{};
    size_t totalLen = 0;
    bool firstEncounter = true;
    
    updateFromFileResults(aggregated, totalLen, firstEncounter, doc);
    
    updateFromSubDocuments(aggregated, totalLen, firstEncounter, doc);
    
    if (aggregated.totalWords > 0)
        aggregated.averageWordLength = static_cast<double>(totalLen) / aggregated.totalWords;
    return aggregated;
}

void CompositeDocumentAnalyzer::updateAggregation(AnalysisResult &agg, size_t &totalLen, bool &firstEncounter, const AnalysisResult &partial) {
    agg.totalWords += partial.totalWords;
    totalLen += static_cast<size_t>(partial.averageWordLength * partial.totalWords);
    if (firstEncounter) {
        agg.longestWord = partial.longestWord;
        agg.shortestWord = partial.shortestWord;
        firstEncounter = false;
    } else {
        if (partial.longestWord.size() > agg.longestWord.size())
            agg.longestWord = partial.longestWord;
        if (!partial.shortestWord.empty() && partial.shortestWord.size() < agg.shortestWord.size())
            agg.shortestWord = partial.shortestWord;
    }
}

void CompositeDocumentAnalyzer::updateFromFileResults(AnalysisResult &agg, size_t &totalLen, bool &firstEncounter, const Document &doc) {
    FileAnalyzer fileAnalyzer;
    const DocumentContent &dc = doc.getContent();
    for (const auto &f : dc.files) {
        AnalysisResult fileRes = fileAnalyzer.analyze(f);
        updateAggregation(agg, totalLen, firstEncounter, fileRes);
    }
}

void CompositeDocumentAnalyzer::updateFromSubDocuments(AnalysisResult &agg, size_t &totalLen, bool &firstEncounter, const Document &doc) {
    const DocumentContent &dc = doc.getContent();
    for (const auto &subDocPtr : dc.documents) {
        AnalysisResult subRes = analyze(*subDocPtr);
        updateAggregation(agg, totalLen, firstEncounter, subRes);
    }
}
