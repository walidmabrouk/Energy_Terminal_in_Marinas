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

  std::string line = findLineWithRfidTag(filePath, key);
  if (line.empty())
  {
    return "";
  }

  return extractFieldFromLine(line, field);
}

void MyFile::saveData(const std::string &key, const std::string &field, const std::string &content)
{
  std::string filePath = "/data.txt";

  if (!openFileForReading(filePath))
  {
    // Handle error as appropriate
    return;
  }

  std::string updatedContent;
  bool keyFound = false;

  while (file.available())
  {
    String line = file.readStringUntil('\n');
    std::string lineStr = line.c_str();

    if (lineStr.find(key) == 0)
    {
      keyFound = true;
      lineStr = key + " " + content; // Assuming content replaces entire line for simplicity
    }

    updatedContent += lineStr + "\n";
  }

  closeFile();

  if (keyFound)
  {
    if (!openFileForWriting(filePath))
    {
      // Handle error as appropriate
      return;
    }
    file.print(updatedContent.c_str());
    closeFile();
  }
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

std::string MyFile::findLineWithRfidTag(const std::string &filePath, const std::string &rfidTag) const
{
  if (!openFileForReading(filePath))
  {
    return "";
  }

  String line;
  while (file.available())
  {
    line = file.readStringUntil('\n');
    std::string lineStr = line.c_str();
    if (lineStr.find(rfidTag) == 0)
    {
      closeFile();
      return lineStr;
    }
  }

  closeFile();
  return "";
}

std::string MyFile::extractFieldFromLine(const std::string &line, const std::string &field) const
{
  // Assuming a simple delimiter-based extraction for demonstration purposes
  std::istringstream iss(line);
  std::string token;

  while (std::getline(iss, token, ' '))
  {
    if (token == field)
    {
      std::getline(iss, token, ' ');
      return token;
    }
  }

  return "";
}
