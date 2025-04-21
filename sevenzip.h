#ifndef SEVENZIP_H
#define SEVENZIP_H

#include <string>
#include <vector>

class SevenZip {
public:
    // ������� �����
    bool createArchive(const std::string& archivePath,
        const std::vector<std::string>& files);

    // ������� ����� � �������
    bool createSecureArchive(const std::string& archivePath,
        const std::vector<std::string>& files,
        const std::string& password);

    // ������� ����
    bool extractFile(const std::string& archivePath,
        const std::string& filePath);

    // ������� ���� � �������
    bool extractWithPassword(const std::string& archivePath,
        const std::string& filePath,
        const std::string& password);

    // ��������� ����������� ������
    bool verifyArchive(const std::string& archivePath);

    // �������� ���� � �����
    bool addToArchive(const std::string& archivePath,
        const std::vector<std::string>& files);

    // ������� ���� �� ������
    bool removeFromArchive(const std::string& archivePath,
        const std::string& filePath);

    // �������� ������ ������
    std::vector<std::string> listArchive(const std::string& archivePath);

private:
    bool archiveExists(const std::string& path);
    bool fileExists(const std::string& path);
};

#endif