#ifndef STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_HPP

#include <string>
#include "../../lib/Domain/Services/BuisnessServices/IRead/IRead.hpp"
#include "../../lib/Domain/Services/BuisnessServices/ISave/ISave.hpp"
#include "../../lib/Domain/Services/InfrastructureServices/IFile/IFile.hpp"

class StorageManager : public IRead, public ISave
{
public:
  explicit StorageManager(IFile *file);

  std::string getData(const std::string &key, const std::string &field) const override;
  void persistData(const std::string &key, const std::string &field, bool value) override;

private:
  IFile *file;
};

#endif // STORAGE_MANAGER_HPP
