#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <mutex>

struct FileContent {
    std::string rawText;
    std::vector<std::string> words;
};

class File {
public:
    explicit File(const std::string &filename);
    File(const File &other);
    File& operator=(const File &other);
    File(File &&other) noexcept = default;
    File& operator=(File &&other) noexcept = default;
    void setContent(const FileContent &fc);
    FileContent getContent() const;
    std::string getFileName() const;
private:
    std::string fileName;
    FileContent content;
    mutable std::mutex mtx;
};

#endif // FILE_H
