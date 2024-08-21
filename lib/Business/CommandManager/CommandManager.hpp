#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include "../../Domain/Services/InfrastructureServices/IBrokerCommunication/IBrokerCommunication.hpp"
#include "../../lib/Domain/Services/BuisnessServices/IEnergySourceManager/IEnergySourceManager.hpp"
#include "../../lib/Domain/Services/BuisnessServices/ISave/ISave.hpp"
#include <string>

class CommandManager
{
private:
  IBrokerCommunication &brokerCommunication;
  IEnergySourceManager &energySourceManager;
  ISave &saveManager;

public:
  CommandManager(IBrokerCommunication &brokerComm,
                 IEnergySourceManager &energyMgr,
                 ISave &saveMgr);

  void executeCommand(const std::string &command);
};

#endif // COMMANDMANAGER_HPP
