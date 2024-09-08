#include <Arduino.h>
#include <LittleFS.h>
#include "../Domain/Services/InfrastructureServices/IFile/IFile.hpp"
#include "../Domain/Services/BuisnessServices/IRead/IRead.hpp"

class MyFile : public IFile , public IRead
{
private:
  fs::File file;

public:


  std::string readFile() override;
  void saveData(const std::string &content) override;

private:
  bool openFileForReading();
  bool openFileForWriting();
  void closeFile();
};


