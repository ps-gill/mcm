#ifndef MCM_CONFIGMANAGER_H
#define MCM_CONFIGMANAGER_H

#include "MonitorArrangement.h"
#include <QString>

class DataManager
{
private:
  QString m_data_directory;
  QString m_ma_directory;

public:
  explicit DataManager(const QString &data_directory);
  bool SaveMonitorArrangement(const QString &name,
                              std::unique_ptr<MonitorArrangement> ma,
                              const bool overwrite = false);
  std::unique_ptr<MonitorArrangement>
  LoadMonitorArrangement(const QString &name);
  QStringList GetMonitorArrangementNames();
  bool DeleteMonitorArrangement(const QString &name);
};

#endif
