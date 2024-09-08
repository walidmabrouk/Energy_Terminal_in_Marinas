#include "MyFile.hpp"

MyFile::MyFile()
{
  // Initialization if needed
}

MyFile::~MyFile()
{
  // Clean up resources if needed
  closeFile();
}

std::string MyFile::readFile()
{
  if (!openFileForReading())
  {
    return ""; // or handle the error
  }
  String content;
  while (file.available())
  {
    content += String((char)file.read());
  }
  closeFile();
  return content.c_str(); // Convert to std::string if needed
}

void MyFile::saveData(const std::string &content)
{
  if (!openFileForWriting())
  {
    // Handle the error
    return;
  }
  file.print(content.c_str());
  closeFile();
}

bool MyFile::openFileForReading()
{
  file = LittleFS.open("/data.txt", "r");
  return file;
}

bool MyFile::openFileForWriting()
{
  file = LittleFS.open("/data.txt", "w");
  return file;
}

void MyFile::closeFile()
{
  if (file)
  {
    file.close();
  }
}
