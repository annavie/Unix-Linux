#include "Document.h"

Document::Document(const Document &other) {
    std::lock_guard<std::mutex> lock(other.mtx);
    content = cloneContent(other.content);
}

Document& Document::operator=(const Document &other) {
    if(this != &other) {
        std::lock_guard<std::mutex> lock1(mtx);
        std::lock_guard<std::mutex> lock2(other.mtx);
        content = cloneContent(other.content);
    }
    return *this;
}

void Document::setContent(const DocumentContent &c) {
    std::lock_guard<std::mutex> lock(mtx);
    content.files = c.files;
    content.documents.clear();
    for (const auto &dPtr : c.documents) {
        content.documents.push_back(std::make_unique<Document>(*dPtr));
    }
}

DocumentContent Document::getContent() const {
    std::lock_guard<std::mutex> lock(mtx);
    return cloneContent(content);
}

DocumentContent Document::cloneContent(const DocumentContent &src) {
    DocumentContent dst;
    dst.files = src.files;
    for (const auto &sd : src.documents) {
        dst.documents.push_back(std::make_unique<Document>(*sd));
    }
    return dst;
}
