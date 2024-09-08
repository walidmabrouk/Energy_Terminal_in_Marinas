#ifndef IFILE_HPP
#define IFILE_HPP

#include <string>

class IFile
{
public:
  virtual ~IFile() = default;

  virtual std::string readFile(const std::string &key, const std::string &field) const = 0;
  virtual void saveData(const std::string &key, const std::string &field, const std::string &content) = 0;
};

#endif // IFILE_HPP
