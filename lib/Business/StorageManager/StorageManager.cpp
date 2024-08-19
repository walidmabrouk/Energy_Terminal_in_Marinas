#include "StorageManager.hpp"
#include <iostream>

StorageManager::StorageManager(IFile *file) : file(file) {}

std::string StorageManager::readData() const
{
  return file->readFile();
}

void StorageManager::saveData(const std::string &data)
{
  file->saveData(data);
}
