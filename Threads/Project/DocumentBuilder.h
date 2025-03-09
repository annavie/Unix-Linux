#ifndef DOCUMENTBUILDER_H
#define DOCUMENTBUILDER_H

#include "Document.h"
#include "File.h"
#include "FileContentLoader.h"
#include <vector>
#include <stdexcept>
#include <memory>

class DocumentBuilder {
public:
    static Document buildDocumentWithFiles(const std::vector<std::string> &fileNames) {
        Document doc;
        DocumentContent dc;
        loadFiles(fileNames, dc);

        doc.setContent(dc);
        return doc;
    }
    static Document buildCompositeDocument(const std::vector<std::string> &fileNames,
                                           std::vector<Document> subDocs) {
        Document doc;
        DocumentContent dc;
        loadFiles(fileNames, dc);
        for (auto &sd : subDocs) {
            dc.documents.push_back(std::make_unique<Document>(sd));
        }
        doc.setContent(dc);
        return doc;
    }

private:
   
    static void loadFiles(const std::vector<std::string>& fileNames, DocumentContent& dc) {
        for (const auto &fn : fileNames) {
            File f(fn);
            FileContent fc;
            FileContentLoader::load(f.getFileName(), fc);
            f.setContent(fc);
            dc.files.push_back(std::move(f));
        }
}
};

#endif
