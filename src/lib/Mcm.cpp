#include <QStandardPaths>

#include "include/mcm/Mcm.h"

#define SERVICE_NAME "org.gnome.Mutter.DisplayConfig"
#define OBJECT_PATH "/org/gnome/Mutter/DisplayConfig"

static org::gnome::Mutter::DisplayConfig *display_config_interface = nullptr;
static DataManager *dataManager = nullptr;

bool Mcm::initialize(const QString &dataDirectoryPath)
{
  if (display_config_interface)
  {
    return true;
  }
  auto connection = QDBusConnection::sessionBus();
  if (!connection.isConnected())
  {
    qWarning("Cannot connect to the D-Bus session bus.");
    return false;
  }

  Registry::registerMetaType();
  auto dc = new org::gnome::Mutter::DisplayConfig(
      org::gnome::Mutter::DisplayConfig::staticInterfaceName(), OBJECT_PATH,
      connection);
  if (!dc->isValid())
  {
    qWarning("Cannot create DisplayConfig proxy.");
    return false;
  }
  display_config_interface = dc;

  dataManager = new DataManager(dataDirectoryPath);
  return true;
}

void Mcm::terminate()
{
  if (dataManager)
  {
    delete dataManager;
    dataManager = nullptr;
  }

  if (display_config_interface)
  {
    delete display_config_interface;
    display_config_interface = nullptr;
  }
}

std::unique_ptr<DisplayState> Mcm::GetCurrentState()
{
  if (!display_config_interface)
  {
    return nullptr;
  }
  QList<GetCurrentStateMonitor> monitors;
  QList<GetCurrentStateLogicalMonitor> logical_monitors;
  QHash<QString, QDBusVariant> properties;
  auto cs = display_config_interface->GetCurrentState(
      monitors, logical_monitors, properties);
  if (!cs.isValid())
  {
    qWarning() << cs.error();
    return nullptr;
  }
  return std::make_unique<DisplayState>(cs.value(), monitors, logical_monitors,
                                        properties);
}

DataManager *Mcm::GetDataManager() { return dataManager; }

bool Mcm::ApplyConfig(std::unique_ptr<ApplyMonitorsConfig> &config)
{
  if (!display_config_interface)
  {
    return false;
  }
  auto reply = display_config_interface->ApplyMonitorsConfig(
      config->m_serial, static_cast<uint>(config->m_method),
      config->m_logical_monitors, config->m_properties);
  reply.waitForFinished();
  if (reply.isError())
  {
    qWarning() << reply.error();
    return false;
  }
  return true;
}

QString Mcm::defaultDataDirectory()
{
  return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}
