#ifndef STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_HPP

#include <string>
#include "../lib/Domain/Services/BuisnessServices/IRead/IRead.hpp"
#include "../lib/Domain/Services/BuisnessServices/ISave/ISave.hpp"
#include "../lib/Domain/Services/InfrastructureServices/IFile/IFile.hpp"

class StorageManager : public IRead, public ISave
{
public:
  StorageManager(IFile *file);
  std::string readData() const override;
  void saveData(const std::string &data) override;

private:
  IFile *file;
};

#endif // STORAGE_MANAGER_HPP
