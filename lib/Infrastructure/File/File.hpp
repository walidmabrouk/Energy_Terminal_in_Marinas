#ifndef FILE_HPP
#define FILE_HPP

#include <Arduino.h>
#include <LittleFS.h>
#include "../Domain/Services/InfrastructureServices/IFile/IFile.hpp"

class File : public IFile
{
private:
  fs::File file;

public:
  File();
  ~File();

  std::string readFile() override;
  void saveData(std::string content) override;

private:
  bool openFileForReading();
  bool openFileForWriting();
  void closeFile();
};

#endif 
