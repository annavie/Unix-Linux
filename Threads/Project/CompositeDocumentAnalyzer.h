#ifndef COMPOSITEDOCUMENTANALYZER_H
#define COMPOSITEDOCUMENTANALYZER_H

#include "DocumentAnalyzer.h"
#include "FileAnalyzer.h"
#include <algorithm>
#include <numeric>

class CompositeDocumentAnalyzer : public DocumentAnalyzer {
public:
    AnalysisResult analyze(const Document &doc) override;
private:
    void updateAggregation(AnalysisResult &agg, size_t &totalLen, bool &firstEncounter, const AnalysisResult &partial);
    void updateFromFileResults(AnalysisResult &agg, size_t &totalLen, bool &firstEncounter, const Document &doc);
    void updateFromSubDocuments(AnalysisResult &agg, size_t &totalLen, bool &firstEncounter, const Document &doc);
};

#endif
