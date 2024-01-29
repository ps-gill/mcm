#ifndef MCM_MCM_H
#define MCM_MCM_H

#include "DataManager.h"
#include "displayconfig.h"
#include "types.h"

class Mcm
{
public:
  static QString defaultDataDirectory();
  static bool initialize(const QString &dataDirectoryPath);
  static std::unique_ptr<DisplayState> GetCurrentState();
  static bool ApplyConfig(std::unique_ptr<ApplyMonitorsConfig> &config);
  static DataManager *GetDataManager();
public slots:
  static void terminate();
};

#endif
