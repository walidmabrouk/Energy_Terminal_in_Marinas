#ifndef MYFILE_HPP
#define MYFILE_HPP

#include <string>
#include <LittleFS.h>
#include "../Domain/Services/InfrastructureServices/IFile/IFile.hpp"

class MyFile : public IFile
{
public:
  MyFile();
  ~MyFile() override;

  std::string readFile(const std::string &key, const std::string &field) const override;
  void saveData(const std::string &key, const std::string &field, const std::string &content) override;

private:
  bool openFileForReading(const std::string &filePath) const;
  bool openFileForWriting(const std::string &filePath);
  void closeFile() const;
  std::string findLineWithRfidTag(const std::string &filePath, const std::string &rfidTag) const;

  mutable fs::File file;
};

#endif // MYFILE_HPP
