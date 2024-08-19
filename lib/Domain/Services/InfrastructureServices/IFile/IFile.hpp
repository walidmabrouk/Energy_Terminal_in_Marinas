#include <string>

struct IFile
{
  virtual std::string readFile() = 0;
  virtual void saveData(std::string content) = 0;
};