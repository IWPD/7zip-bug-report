#ifndef SEVENZIP_H
#define SEVENZIP_H

#include <string>
#include <vector>

class SevenZip {
public:
    // Создать архив
    bool createArchive(const std::string& archivePath,
        const std::vector<std::string>& files);

    // Создать архив с паролем
    bool createSecureArchive(const std::string& archivePath,
        const std::vector<std::string>& files,
        const std::string& password);

    // Извлечь файл
    bool extractFile(const std::string& archivePath,
        const std::string& filePath);

    // Извлечь файл с паролем
    bool extractWithPassword(const std::string& archivePath,
        const std::string& filePath,
        const std::string& password);

    // Проверить целостность архива
    bool verifyArchive(const std::string& archivePath);

    // Добавить файл в архив
    bool addToArchive(const std::string& archivePath,
        const std::vector<std::string>& files);

    // Удалить файл из архива
    bool removeFromArchive(const std::string& archivePath,
        const std::string& filePath);

    // Получить список файлов
    std::vector<std::string> listArchive(const std::string& archivePath);

private:
    bool archiveExists(const std::string& path);
    bool fileExists(const std::string& path);
};

#endif