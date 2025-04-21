#include <gtest/gtest.h>
#include "sevenzip.h"
#include <filesystem>

namespace fs = std::filesystem;

class SevenZipTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаем тестовые файлы
        createTestFile("test1.txt", "Test content 1");
        createTestFile("test2.txt", "Test content 2");
        createTestFile("тест_кириллица.txt", "Кириллическое содержимое");
    }

    void TearDown() override {
        // Удаляем тестовые файлы
        fs::remove("test1.txt");
        fs::remove("test2.txt");
        fs::remove("тест_кириллица.txt");
        fs::remove("test_archive.7z");
        fs::remove("secure_archive.7z");
        fs::remove("extracted_file.txt");
    }

    void createTestFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);
        file << content;
        file.close();
    }

    SevenZip archiver;
};

// 1. Тест создания простого архива
TEST_F(SevenZipTest, CreatesArchiveSuccessfully) {
    EXPECT_TRUE(archiver.createArchive("test_archive.7z", { "test1.txt" }));
    EXPECT_TRUE(fs::exists("test_archive.7z"));
}

// 2. Тест создания архива с несуществующим файлом
TEST_F(SevenZipTest, FailsWhenFileNotExists) {
    EXPECT_FALSE(archiver.createArchive("test_archive.7z", { "nonexistent.txt" }));
}

// 3. Тест извлечения файла из архива
TEST_F(SevenZipTest, ExtractsFileSuccessfully) {
    ASSERT_TRUE(archiver.createArchive("test_archive.7z", { "test1.txt" }));
    EXPECT_TRUE(archiver.extractFile("test_archive.7z", "extracted_file.txt"));
    EXPECT_TRUE(fs::exists("extracted_file.txt"));
}

// 4. Тест работы с кириллическими именами файлов
TEST_F(SevenZipTest, HandlesCyrillicFilenames) {
    EXPECT_TRUE(archiver.createArchive("test_archive.7z", { "тест_кириллица.txt" }));
    EXPECT_TRUE(archiver.extractFile("test_archive.7z", "extracted_cyrillic.txt"));
    EXPECT_TRUE(fs::exists("extracted_cyrillic.txt"));
}

// 5. Тест создания архива с паролем
TEST_F(SevenZipTest, CreatesPasswordProtectedArchive) {
    EXPECT_TRUE(archiver.createSecureArchive("secure_archive.7z", { "test1.txt" }, "strongpassword"));
    EXPECT_TRUE(fs::exists("secure_archive.7z"));
}

// 6. Тест извлечения с правильным паролем
TEST_F(SevenZipTest, ExtractsWithCorrectPassword) {
    ASSERT_TRUE(archiver.createSecureArchive("secure_archive.7z", { "test1.txt" }, "strongpassword"));
    EXPECT_TRUE(archiver.extractWithPassword("secure_archive.7z", "extracted_file.txt", "strongpassword"));
}

// 7. Тест извлечения с неправильным паролем
TEST_F(SevenZipTest, FailsWithWrongPassword) {
    ASSERT_TRUE(archiver.createSecureArchive("secure_archive.7z", { "test1.txt" }, "strongpassword"));
    EXPECT_FALSE(archiver.extractWithPassword("secure_archive.7z", "extracted_file.txt", "wrongpassword"));
}

// 8. Тест проверки целостности архива
TEST_F(SevenZipTest, VerifiesGoodArchive) {
    ASSERT_TRUE(archiver.createArchive("test_archive.7z", { "test1.txt" }));
    EXPECT_TRUE(archiver.verifyArchive("test_archive.7z"));
}

// 9. Тест проверки поврежденного архива
TEST_F(SevenZipTest, DetectsCorruptedArchive) {
    std::ofstream bad_archive("bad_archive.7z");
    bad_archive << "CORRUPTED_DATA";
    bad_archive.close();

    EXPECT_FALSE(archiver.verifyArchive("bad_archive.7z"));
    fs::remove("bad_archive.7z");
}

// 10. Тест получения списка файлов
TEST_F(SevenZipTest, ListsArchiveContents) {
    ASSERT_TRUE(archiver.createArchive("test_archive.7z", { "test1.txt", "test2.txt" }));
    auto files = archiver.listArchive("test_archive.7z");

    ASSERT_EQ(files.size(), 2);
    EXPECT_EQ(files[0], "test1.txt");
    EXPECT_EQ(files[1], "test2.txt");
}

// 11. Тест добавления файла в архив
TEST_F(SevenZipTest, AddsFileToExistingArchive) {
    ASSERT_TRUE(archiver.createArchive("test_archive.7z", { "test1.txt" }));
    EXPECT_TRUE(archiver.addToArchive("test_archive.7z", { "test2.txt" }));
}

// 12. Тест удаления файла из архива
TEST_F(SevenZipTest, RemovesFileFromArchive) {
    ASSERT_TRUE(archiver.createArchive("test_archive.7z", { "test1.txt", "test2.txt" }));
    EXPECT_TRUE(archiver.removeFromArchive("test_archive.7z", "test1.txt"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}