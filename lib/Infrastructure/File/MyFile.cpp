#include "MyFile.hpp"

MyFile::MyFile()
{
  // Initialization if needed
}

MyFile::~MyFile()
{
  closeFile();
}

std::string MyFile::readFile(const std::string &key, const std::string &field) const
{
  std::string filePath = "/data.txt";

  if (!openFileForReading(filePath))
  {
    return "";
  }

  String content;
  std::array listOfData = []; // array vide
  while (file.available())
  {
    content += (char)file.read();
    if ((char)file.read() == "/n")
    {
      // convert content to array with separate ; 
      listOfData.push_back(content);
      content = "";
    }
  }
  
  

  closeFile();
  return content.c_str();
}

void MyFile::saveData(const std::string &key, const std::string &field, const std::string &content)
{
  std::string filePath = "/" + key + "_" + field + ".txt";

  if (!openFileForWriting(filePath))
  {
    // Handle error as appropriate
    return;
  }

  file.print(content.c_str());
  closeFile();
}

bool MyFile::openFileForReading(const std::string &filePath) const
{
  file = LittleFS.open(filePath.c_str(), "r");
  return file;
}

bool MyFile::openFileForWriting(const std::string &filePath)
{
  file = LittleFS.open(filePath.c_str(), "w");
  return file;
}

void MyFile::closeFile() const
{
  if (file)
  {
    file.close();
  }
}
