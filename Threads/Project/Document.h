#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "File.h"
#include <vector>
#include <memory>
#include <mutex>

struct DocumentContent {
    std::vector<std::unique_ptr<class Document>> documents;
    std::vector<File> files;
};

class Document {
public:
    Document() = default;
    Document(const Document &other);
    Document& operator=(const Document &other);

    void setContent(const DocumentContent &c);
    DocumentContent getContent() const;
    
private:
    static DocumentContent cloneContent(const DocumentContent &src);
    mutable std::mutex mtx;
    DocumentContent content;
};

#endif
