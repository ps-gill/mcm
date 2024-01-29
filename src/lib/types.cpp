#include "include/mcm/types.h"
#include <QDBusMetaType>

void Registry::registerMetaType()
{
  qRegisterMetaType<GetCurrentStateMonitorInfo>("GetCurrentStateMonitorInfo");
  qDBusRegisterMetaType<GetCurrentStateMonitorInfo>();

  qRegisterMetaType<GetCurrentStateMonitorMode>("GetCurrentStateMonitorMode");
  qDBusRegisterMetaType<GetCurrentStateMonitorMode>();

  qDBusRegisterMetaType<QList<GetCurrentStateMonitorMode>>();

  qRegisterMetaType<GetCurrentStateMonitor>("GetCurrentStateMonitor");
  qDBusRegisterMetaType<GetCurrentStateMonitor>();

  qDBusRegisterMetaType<QList<GetCurrentStateMonitor>>();

  qRegisterMetaType<GetCurrentStateLogicalMonitorMonitor>(
      "GetCurrentStateLogicalMonitorMonitor");
  qDBusRegisterMetaType<GetCurrentStateLogicalMonitorMonitor>();

  qDBusRegisterMetaType<QList<GetCurrentStateLogicalMonitorMonitor>>();

  qRegisterMetaType<GetCurrentStateLogicalMonitor>(
      "GetCurrentStateLogicalMonitor");
  qDBusRegisterMetaType<GetCurrentStateLogicalMonitor>();

  qDBusRegisterMetaType<QList<GetCurrentStateLogicalMonitor>>();

  qDBusRegisterMetaType<QHash<QString, QDBusVariant>>();

  qRegisterMetaType<ApplyMonitorsConfigMonitor>("ApplyMonitorsConfigMonitor");
  qDBusRegisterMetaType<ApplyMonitorsConfigMonitor>();

  qDBusRegisterMetaType<QList<ApplyMonitorsConfigMonitor>>();

  qRegisterMetaType<ApplyMonitorsConfigLogicalMonitor>(
      "ApplyMonitorsConfigLogicalMonitor");
  qDBusRegisterMetaType<ApplyMonitorsConfigLogicalMonitor>();

  qDBusRegisterMetaType<QList<ApplyMonitorsConfigLogicalMonitor>>();
}

QDBusArgument &operator<<(QDBusArgument &argument,
                          const GetCurrentStateMonitorInfo &info)
{
  argument.beginStructure();
  argument << info.m_connector;
  argument << info.m_vendor;
  argument << info.m_product;
  argument << info.m_serial;
  argument.endStructure();

  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument,
                                GetCurrentStateMonitorInfo &info)
{
  argument.beginStructure();
  argument >> info.m_connector;
  argument >> info.m_vendor;
  argument >> info.m_product;
  argument >> info.m_serial;
  argument.endStructure();

  return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument,
                          const GetCurrentStateMonitorMode &mode)
{
  argument.beginStructure();
  argument << mode.m_id;
  argument << mode.m_width;
  argument << mode.m_height;
  argument << mode.m_refresh_rate;
  argument << mode.m_preferred_scale;
  argument << mode.m_supported_scales;
  argument << mode.m_properties;
  argument.endStructure();

  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument,
                                GetCurrentStateMonitorMode &mode)
{
  argument.beginStructure();
  argument >> mode.m_id;
  argument >> mode.m_width;
  argument >> mode.m_height;
  argument >> mode.m_refresh_rate;
  argument >> mode.m_preferred_scale;
  argument >> mode.m_supported_scales;
  argument >> mode.m_properties;
  argument.endStructure();

  return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument,
                          const GetCurrentStateMonitor &monitor)
{
  argument.beginStructure();
  argument << monitor.m_info;
  argument << monitor.m_modes;
  argument << monitor.m_properties;
  argument.endStructure();

  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument,
                                GetCurrentStateMonitor &monitor)
{
  argument.beginStructure();
  argument >> monitor.m_info;
  argument >> monitor.m_modes;
  argument >> monitor.m_properties;
  argument.endStructure();

  return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument,
                          const GetCurrentStateLogicalMonitorMonitor &monitor)
{
  argument.beginStructure();
  argument << monitor.m_connector;
  argument << monitor.m_vendor;
  argument << monitor.m_product;
  argument << monitor.m_serial;
  argument.endStructure();

  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument,
                                GetCurrentStateLogicalMonitorMonitor &monitor)
{
  argument.beginStructure();
  argument >> monitor.m_connector;
  argument >> monitor.m_vendor;
  argument >> monitor.m_product;
  argument >> monitor.m_serial;
  argument.endStructure();

  return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument,
                          const GetCurrentStateLogicalMonitor &logicalMonitor)
{
  argument.beginStructure();
  argument << logicalMonitor.m_x;
  argument << logicalMonitor.m_y;
  argument << logicalMonitor.m_scale;
  argument << logicalMonitor.m_transform;
  argument << logicalMonitor.m_primary;
  argument << logicalMonitor.m_monitors;
  argument << logicalMonitor.m_properties;
  argument.endStructure();

  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument,
                                GetCurrentStateLogicalMonitor &logicalMonitor)
{
  argument.beginStructure();
  argument >> logicalMonitor.m_x;
  argument >> logicalMonitor.m_y;
  argument >> logicalMonitor.m_scale;
  argument >> logicalMonitor.m_transform;
  argument >> logicalMonitor.m_primary;
  argument >> logicalMonitor.m_monitors;
  argument >> logicalMonitor.m_properties;
  argument.endStructure();

  return argument;
}

DisplayState::DisplayState(
    uint serial, const QList<GetCurrentStateMonitor> &monitors,
    const QList<GetCurrentStateLogicalMonitor> &logicalMonitors,
    const QHash<QString, QDBusVariant> &properties)
    : m_serial(serial), m_monitors(monitors),
      m_logical_monitors(logicalMonitors), m_properties(properties)
{
}

bool DisplayState::supportsChangingLayoutMode()
{
  QHashIterator<QString, QDBusVariant> pi(m_properties);
  while (pi.hasNext())
  {
    pi.next();
    if (pi.key() == "supports-changing-layout-mode")
    {
      return pi.value().variant().toBool();
    }
  }
  return false;
}

QDBusArgument &operator<<(QDBusArgument &argument,
                          const ApplyMonitorsConfigMonitor &monitor)
{
  argument.beginStructure();
  argument << monitor.m_connector;
  argument << monitor.m_mode_id;
  argument << monitor.m_properties;
  argument.endStructure();

  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument,
                                ApplyMonitorsConfigMonitor &monitor)
{
  argument.beginStructure();
  argument >> monitor.m_connector;
  argument >> monitor.m_mode_id;
  argument >> monitor.m_properties;
  argument.endStructure();

  return argument;
}

QDBusArgument &
operator<<(QDBusArgument &argument,
           const ApplyMonitorsConfigLogicalMonitor &logicalMonitor)
{
  argument.beginStructure();
  argument << logicalMonitor.m_x;
  argument << logicalMonitor.m_y;
  argument << logicalMonitor.m_scale;
  argument << logicalMonitor.m_transform;
  argument << logicalMonitor.m_primary;
  argument << logicalMonitor.m_monitors;
  argument.endStructure();

  return argument;
}

const QDBusArgument &
operator>>(const QDBusArgument &argument,
           ApplyMonitorsConfigLogicalMonitor &logicalMonitor)
{
  argument.beginStructure();
  argument >> logicalMonitor.m_x;
  argument >> logicalMonitor.m_y;
  argument >> logicalMonitor.m_scale;
  argument >> logicalMonitor.m_transform;
  argument >> logicalMonitor.m_primary;
  argument >> logicalMonitor.m_monitors;
  argument.endStructure();

  return argument;
}

ApplyMonitorsConfig::ApplyMonitorsConfig(
    uint serial, ApplyMonitorConfigMethod method,
    const QList<ApplyMonitorsConfigLogicalMonitor> &logicalMonitors,
    const QHash<QString, QDBusVariant> &properties)
    : m_serial(serial), m_method(method), m_logical_monitors(logicalMonitors),
      m_properties(properties)
{
}
