#ifndef MCM_TYPES_H
#define MCM_TYPES_H

#include <QDBusArgument>
#include <QHash>
#include <QList>
#include <QMetaType>

class Registry
{
public:
  static void registerMetaType();
};

class GetCurrentStateMonitorInfo
{
public:
  QString m_connector, m_vendor, m_product, m_serial;
  friend QDBusArgument &operator<<(QDBusArgument &argument,
                                   const GetCurrentStateMonitorInfo &info);
  friend const QDBusArgument &operator>>(const QDBusArgument &argument,
                                         GetCurrentStateMonitorInfo &info);
};

class GetCurrentStateMonitorMode
{
public:
  QString m_id;
  int m_width, m_height;
  double m_refresh_rate, m_preferred_scale;
  QList<double> m_supported_scales;
  QHash<QString, QDBusVariant> m_properties;
  friend QDBusArgument &operator<<(QDBusArgument &argument,
                                   const GetCurrentStateMonitorMode &mode);
  friend const QDBusArgument &operator>>(const QDBusArgument &argument,
                                         GetCurrentStateMonitorMode &mode);
};
Q_DECLARE_METATYPE(GetCurrentStateMonitorMode);

class GetCurrentStateMonitor
{
public:
  GetCurrentStateMonitorInfo m_info;
  QHash<QString, QDBusVariant> m_properties;
  QList<GetCurrentStateMonitorMode> m_modes;
  friend QDBusArgument &operator<<(QDBusArgument &argument,
                                   const GetCurrentStateMonitor &monitor);
  friend const QDBusArgument &operator>>(const QDBusArgument &argument,
                                         GetCurrentStateMonitor &monitor);
};
Q_DECLARE_METATYPE(GetCurrentStateMonitor);

class GetCurrentStateLogicalMonitorMonitor
{
public:
  QString m_connector, m_vendor, m_product, m_serial;
  friend QDBusArgument &
  operator<<(QDBusArgument &argument,
             const GetCurrentStateLogicalMonitorMonitor &monitor);
  friend const QDBusArgument &
  operator>>(const QDBusArgument &argument,
             GetCurrentStateLogicalMonitorMonitor &monitor);
};
Q_DECLARE_METATYPE(GetCurrentStateLogicalMonitorMonitor);

class GetCurrentStateLogicalMonitor
{
public:
  int m_x, m_y;
  double m_scale;
  uint m_transform;
  bool m_primary;
  QList<GetCurrentStateLogicalMonitorMonitor> m_monitors;
  QHash<QString, QDBusVariant> m_properties;
  friend QDBusArgument &
  operator<<(QDBusArgument &argument,
             const GetCurrentStateLogicalMonitor &logicalMonitor);
  friend const QDBusArgument &
  operator>>(const QDBusArgument &argument,
             GetCurrentStateLogicalMonitor &logicalMonitor);
};
Q_DECLARE_METATYPE(GetCurrentStateLogicalMonitor);

class DisplayState
{
public:
  const uint m_serial;
  const QList<GetCurrentStateMonitor> m_monitors;
  const QList<GetCurrentStateLogicalMonitor> m_logical_monitors;
  const QHash<QString, QDBusVariant> m_properties;
  DisplayState(uint serial, const QList<GetCurrentStateMonitor> &monitors,
               const QList<GetCurrentStateLogicalMonitor> &logicalMonitors,
               const QHash<QString, QDBusVariant> &properties);
  bool supportsChangingLayoutMode();
};

class ApplyMonitorsConfigMonitor
{
public:
  QString m_connector, m_mode_id;
  QHash<QString, QDBusVariant> m_properties;
  friend QDBusArgument &
  operator<<(QDBusArgument &argument,
             const ApplyMonitorsConfigMonitor &logicalMonitor);
  friend const QDBusArgument &
  operator>>(const QDBusArgument &argument,
             ApplyMonitorsConfigMonitor &logicalMonitor);
};
Q_DECLARE_METATYPE(ApplyMonitorsConfigMonitor);

class ApplyMonitorsConfigLogicalMonitor
{
public:
  int m_x, m_y;
  double m_scale;
  uint m_transform;
  bool m_primary;
  QList<ApplyMonitorsConfigMonitor> m_monitors;
  friend QDBusArgument &
  operator<<(QDBusArgument &argument,
             const ApplyMonitorsConfigLogicalMonitor &logicalMonitor);
  friend const QDBusArgument &
  operator>>(const QDBusArgument &argument,
             ApplyMonitorsConfigLogicalMonitor &logicalMonitor);
};
Q_DECLARE_METATYPE(ApplyMonitorsConfigLogicalMonitor);

enum class ApplyMonitorConfigMethod
{
  VERIFY = 0U,
  TEMPORARY,
  PERSISTENT
};

class ApplyMonitorsConfig
{
public:
  uint m_serial;
  ApplyMonitorConfigMethod m_method;
  QList<ApplyMonitorsConfigLogicalMonitor> m_logical_monitors;
  QHash<QString, QDBusVariant> m_properties;

  ApplyMonitorsConfig(
      uint serial, ApplyMonitorConfigMethod method,
      const QList<ApplyMonitorsConfigLogicalMonitor> &logicalMonitors,
      const QHash<QString, QDBusVariant> &properties);
};

#endif
