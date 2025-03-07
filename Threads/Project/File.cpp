#include "File.h"

File::File(const std::string &filename) : fileName(filename) { }

File::File(const File &other) : fileName(other.fileName) {
    std::lock_guard<std::mutex> lock(other.mtx);
    content = other.content;
}

File& File::operator=(const File &other) {
    if (this != &other) {
        std::lock_guard<std::mutex> lock1(mtx);
        std::lock_guard<std::mutex> lock2(other.mtx);
        fileName = other.fileName;
        content = other.content;
    }
    return *this;
}

void File::setContent(const FileContent &fc) {
    std::lock_guard<std::mutex> lock(mtx);
    content = fc;
}

FileContent File::getContent() const {
    std::lock_guard<std::mutex> lock(mtx);
    return content;
}

std::string File::getFileName() const {
    return fileName;
}
