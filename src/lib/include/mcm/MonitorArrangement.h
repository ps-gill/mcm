#ifndef MCM_MONITORARRANGEMENT_H
#define MCM_MONITORARRANGEMENT_H

#include <QJsonObject>
#include <QList>
#include <QString>
#include <QVersionNumber>
#include <memory>

#include "types.h"

class MAMonitor
{
public:
  QString m_serial;
  QString m_mode_id;

  MAMonitor(QString serial, QString modeId);

  QJsonObject toJson() const;
  static MAMonitor fromJson(const QJsonObject &obj, bool *ok);
  bool operator==(const MAMonitor &other) const;
};

class MALogicalMonitor
{
public:
  int m_x, m_y;
  uint m_transform;
  bool m_primary;
  double m_scale;
  QList<MAMonitor> m_monitors;

  MALogicalMonitor(int x, int y, uint transform, bool primary, double scale,
                   const QList<MAMonitor> &monitors);

  QJsonObject toJson() const;
  static MALogicalMonitor fromJson(const QJsonObject &obj, bool *ok);
  bool operator==(const MALogicalMonitor &other) const;
};

enum class MonitorArrangementLayoutMode
{
  UNKNOWN = 0U,
  LOGICAL,
  PHYSICAL
};

class MonitorArrangement
{
public:
  QList<MALogicalMonitor> m_logical_monitors;
  MonitorArrangementLayoutMode m_layout_mode;
  QVersionNumber m_version;

  QJsonObject toJson() const;
  static std::unique_ptr<MonitorArrangement> fromJson(const QJsonObject &obj);
  static std::unique_ptr<MonitorArrangement>
  createFromDisplayState(const std::unique_ptr<DisplayState> &state);
  std::unique_ptr<ApplyMonitorsConfig>
  toApplyMonitorConfig(ApplyMonitorConfigMethod method,
                       const std::unique_ptr<DisplayState> &state);
  bool operator==(const MonitorArrangement &other) const;
};

#endif
