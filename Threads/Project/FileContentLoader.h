#ifndef FILECONTENTLOADER_H
#define FILECONTENTLOADER_H

#include "File.h"
#include <stdexcept>
#include <string>

class FileContentLoader {
public:
    static void load(const std::string &filename, FileContent &fc);
private:
    static void tokenize(FileContent &fc);
};

#endif
