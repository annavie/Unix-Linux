#include "FileContentLoader.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>

void FileContentLoader::load(const std::string &filename, FileContent &fc) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    std::string line;
    fc.rawText.clear();
    while (std::getline(inFile, line)) {
        fc.rawText += line + "\n";
    }
    inFile.close();
    tokenize(fc);
}

void FileContentLoader::tokenize(FileContent &fc) {
    fc.words.clear();
    std::istringstream iss(fc.rawText);
    std::string word;
    while (iss >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (!word.empty())
            fc.words.push_back(word);
    }
}
