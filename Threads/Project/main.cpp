#include "DocumentBuilder.h"
#include "AnalysisManager.h"
#include <iostream>
#include <vector>

int main() {
    try {
        auto doc1 = DocumentBuilder::buildDocumentWithFiles({
            "doc1_file1.txt",
            "doc1_file2.txt"
        });
        auto subDoc = DocumentBuilder::buildDocumentWithFiles({
            "doc2_sub_file.txt"
        });
        auto doc2 = DocumentBuilder::buildCompositeDocument({
            "doc2_file.txt"
        }, {subDoc});
        
        AnalysisManager manager({doc1, doc2});
        manager.runAnalysis();
        std::cout << "All analyses completed.\n";
        return 0;
    }
    catch (const std::exception &ex) {
        std::cerr << "Fatal error in main: " << ex.what() << std::endl;
        return 1;
    }
}
