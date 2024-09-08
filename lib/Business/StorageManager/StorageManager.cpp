#include "StorageManager.hpp"

StorageManager::StorageManager(IFile *file) : file(file) {}

std::string StorageManager::getData(const std::string &key, const std::string &field) const
{
  return file->readFile(key, field);
}

void StorageManager::persistData(const std::string &key, const std::string &field, bool value)
{
  const std::string data = value ? "true" : "false";
  file->saveData(key, field, data);
}
