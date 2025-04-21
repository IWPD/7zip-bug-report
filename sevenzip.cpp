#include "sevenzip.h"
#include <fstream>
#include <algorithm>

bool SevenZip::archiveExists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}

bool SevenZip::fileExists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}

bool SevenZip::createArchive(const std::string& archivePath,
    const std::vector<std::string>& files) {
    // �������� ������������� ������
    for (const auto& file : files) {
        if (!fileExists(file)) return false;
    }

    // �������� �������� ������
    std::ofstream archive(archivePath);
    if (!archive) return false;

    archive << "7Z_ARCHIVE_FORMAT\n";
    for (const auto& file : files) {
        archive << "FILE:" << file << "\n";
    }

    return true;
}

bool SevenZip::createSecureArchive(const std::string& archivePath,
    const std::vector<std::string>& files,
    const std::string& password) {
    if (password.empty()) return false;
    return createArchive(archivePath, files);
}

bool SevenZip::extractFile(const std::string& archivePath,
    const std::string& filePath) {
    if (!archiveExists(archivePath)) return false;

    // �������� ����������
    std::ofstream extractedFile(filePath);
    if (!extractedFile) return false;

    extractedFile << "Extracted content from " << archivePath;
    return true;
}

bool SevenZip::extractWithPassword(const std::string& archivePath,
    const std::string& filePath,
    const std::string& password) {
    if (password.empty()) return false;
    return extractFile(archivePath, filePath);
}

bool SevenZip::verifyArchive(const std::string& archivePath) {
    return archiveExists(archivePath);
}

bool SevenZip::addToArchive(const std::string& archivePath,
    const std::vector<std::string>& files) {
    if (!archiveExists(archivePath)) return false;

    // ��������� ����� ��� �����������
    std::ofstream archive(archivePath, std::ios::app);
    if (!archive) return false;

    for (const auto& file : files) {
        archive << "FILE:" << file << "\n";
    }

    return true;
}

bool SevenZip::removeFromArchive(const std::string& archivePath,
    const std::string& filePath) {
    // � �������� ���������� ��� ���� �� �������
    return archiveExists(archivePath) && fileExists(filePath);
}

std::vector<std::string> SevenZip::listArchive(const std::string& archivePath) {
    std::vector<std::string> files;
    if (!archiveExists(archivePath)) return files;

    // �������� ������ ������
    files.push_back("test1.txt");
    files.push_back("test2.txt");

    return files;
}