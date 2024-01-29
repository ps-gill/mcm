#include "../include/mcm/MonitorArrangement.h"
#include "../include/mcm/config.h"
#include "../include/mcm/types.h"
#include <QJsonArray>
#include <QtDebug>
#include <algorithm>
#include <utility>

static MAMonitor DefaultADMonitor("", "");
static MALogicalMonitor DefaultADLogicalMonitor(0, 0, 0, false, 0,
                                                QList<MAMonitor>());

static QString
get_monitor_mode_id(const QString &serial,
                    const QList<GetCurrentStateMonitor> &monitors)
{
  for (const auto &m : monitors)
  {
    if (serial != m.m_info.m_serial)
    {
      continue;
    }
    for (const auto &mode : m.m_modes)
    {
      if (!mode.m_properties.contains("is-current"))
      {
        continue;
      }
      if (mode.m_properties["is-current"].variant().toBool())
      {
        return mode.m_id;
      }
    }
  }
  return "";
}

QJsonObject MAMonitor::toJson() const
{
  QJsonObject obj;
  obj["serial"] = m_serial;
  obj["mode_id"] = m_mode_id;
  return obj;
}

MAMonitor::MAMonitor(QString serial, QString modeId)
    : m_serial(std::move(serial)), m_mode_id(std::move(modeId))
{
}

MAMonitor MAMonitor::fromJson(const QJsonObject &obj, bool *ok)
{
  *ok = false;
  auto serial_r = obj["serial"];
  if (!serial_r.isString())
  {
    return DefaultADMonitor;
  }
  auto mode_id_r = obj["mode_id"];
  if (!mode_id_r.isString())
  {
    return DefaultADMonitor;
  }
  *ok = true;
  return {serial_r.toString(), mode_id_r.toString()};
}

bool MAMonitor::operator==(const MAMonitor &other) const
{
  if (m_serial != other.m_serial)
  {
    return false;
  }
  if (m_mode_id != other.m_mode_id)
  {
    return false;
  }
  return true;
}

QJsonObject MALogicalMonitor::toJson() const
{
  QJsonObject obj;
  obj["x"] = m_x;
  obj["y"] = m_y;
  obj["transform"] = QString::number(m_transform);
  obj["scale"] = m_scale;
  obj["primary"] = m_primary;
  QJsonArray ms;
  for (const auto &m : m_monitors)
  {
    ms.append(m.toJson());
  }
  obj["monitors"] = ms;
  return obj;
}

MALogicalMonitor::MALogicalMonitor(int x, int y, uint transform, bool primary,
                                   double scale,
                                   const QList<MAMonitor> &monitors)
    : m_x(x), m_y(y), m_transform(transform), m_primary(primary),
      m_scale(scale), m_monitors(monitors)
{
}

MALogicalMonitor MALogicalMonitor::fromJson(const QJsonObject &obj, bool *ok)
{
  *ok = false;
  auto x_r = obj["x"];
  if (!x_r.isDouble())
  {
    return DefaultADLogicalMonitor;
  }
  auto y_r = obj["y"];
  if (!y_r.isDouble())
  {
    return DefaultADLogicalMonitor;
  }
  auto transform_r = obj["transform"];
  if (!transform_r.isString())
  {
    return DefaultADLogicalMonitor;
  }
  auto scale_r = obj["scale"];
  if (!scale_r.isDouble())
  {
    return DefaultADLogicalMonitor;
  }
  auto primary_r = obj["primary"];
  if (!primary_r.isBool())
  {
    return DefaultADLogicalMonitor;
  }
  auto monitors_r = obj["monitors"];
  if (!monitors_r.isArray())
  {
    return DefaultADLogicalMonitor;
  }
  bool ok_cast;
  auto transform = transform_r.toString().toUInt(&ok_cast);
  if (!ok_cast)
  {
    qWarning() << "display arrangement logical monitor transform is invalid. "
               << transform_r.toString();
    return DefaultADLogicalMonitor;
  }
  auto x = x_r.toInt(-1);
  if (x == -1)
  {
    qWarning() << "display arrangement logical monitor x is invalid. "
               << x_r.toDouble();
    return DefaultADLogicalMonitor;
  }
  auto y = y_r.toInt(-1);
  if (y == -1)
  {
    qWarning() << "display arrangement logical monitor x is invalid. "
               << y_r.toDouble();
    return DefaultADLogicalMonitor;
  }
  auto lm = MALogicalMonitor(x, y, transform, primary_r.toBool(),
                             scale_r.toDouble(), QList<MAMonitor>());
  for (const auto m : monitors_r.toArray())
  {
    if (m.isObject())
    {
      bool ok_monitor;
      auto monitor = MAMonitor::fromJson(m.toObject(), &ok_monitor);
      if (!ok_monitor)
      {
        return DefaultADLogicalMonitor;
      }
      lm.m_monitors += monitor;
    }
  }
  *ok = true;
  return lm;
}

bool MALogicalMonitor::operator==(const MALogicalMonitor &other) const
{
  if (m_x != other.m_x)
  {
    return false;
  }
  if (m_y != other.m_y)
  {
    return false;
  }
  if (m_transform != other.m_transform)
  {
    return false;
  }
  if (m_primary != other.m_primary)
  {
    return false;
  }
  if (m_scale != other.m_scale)
  {
    return false;
  }
  return std::equal(m_monitors.begin(), m_monitors.end(),
                    other.m_monitors.begin(), other.m_monitors.end());
}

QJsonObject MonitorArrangement::toJson() const
{
  QJsonObject obj;
  QJsonArray arr;
  for (auto &m : m_logical_monitors)
  {
    arr += m.toJson();
  }
  obj["logical_monitors"] = arr;
  obj["layout_mode"] = QString::number(static_cast<uint>(m_layout_mode));
  obj["version"] = m_version.toString();
  return obj;
}

std::unique_ptr<MonitorArrangement>
MonitorArrangement::fromJson(const QJsonObject &obj)
{
  if (auto lms = obj["logical_monitors"]; lms.isArray())
  {
    auto ma = std::make_unique<MonitorArrangement>();
    ma->m_layout_mode = MonitorArrangementLayoutMode::UNKNOWN;
    for (const auto lm : lms.toArray())
    {
      if (lm.isObject())
      {
        bool ok;
        auto lmObj = MALogicalMonitor::fromJson(lm.toObject(), &ok);
        if (!ok)
        {
          return nullptr;
        }
        ma->m_logical_monitors += lmObj;
      }
    }
    if (auto layout_mode = obj["layout_mode"]; layout_mode.isString())
    {
      bool ok_cast;
      auto transform = layout_mode.toString().toUInt(&ok_cast);
      if (!ok_cast)
      {
        return nullptr;
      }
      ma->m_layout_mode = static_cast<MonitorArrangementLayoutMode>(transform);
    }

    if (auto version = obj["version"]; version.isString())
    {
      ma->m_version = QVersionNumber::fromString(version.toString());
    }
    else
    {
      ma->m_version = MCM_VERSION;
    }

    return ma;
  }
  return nullptr;
}

std::unique_ptr<MonitorArrangement> MonitorArrangement::createFromDisplayState(
    const std::unique_ptr<DisplayState> &state)
{
  if (state == nullptr)
  {
    return nullptr;
  }

  auto logicalMonitors = QList<MALogicalMonitor>();
  for (const auto &lm : state->m_logical_monitors)
  {
    auto monitors = QList<MAMonitor>();
    for (const auto &m : lm.m_monitors)
    {
      monitors += MAMonitor(m.m_serial,
                            get_monitor_mode_id(m.m_serial, state->m_monitors));
    }
    logicalMonitors += MALogicalMonitor(lm.m_x, lm.m_y, lm.m_transform,
                                        lm.m_primary, lm.m_scale, monitors);
  }

  auto ma = std::make_unique<MonitorArrangement>();
  ma->m_logical_monitors = logicalMonitors;
  ma->m_layout_mode = MonitorArrangementLayoutMode::UNKNOWN;
  ma->m_version = MCM_VERSION;

  QHashIterator<QString, QDBusVariant> pi(state->m_properties);
  while (pi.hasNext())
  {
    pi.next();
    if (pi.key() == "layout-mode")
    {
      ma->m_layout_mode = static_cast<MonitorArrangementLayoutMode>(
          pi.value().variant().toUInt());
    }
  }

  return ma;
}

std::unique_ptr<ApplyMonitorsConfig> MonitorArrangement::toApplyMonitorConfig(
    ApplyMonitorConfigMethod method, const std::unique_ptr<DisplayState> &state)
{
  QList<ApplyMonitorsConfigLogicalMonitor> lms;
  QHash<QString, QDBusVariant> properties;

  for (const auto &malm : this->m_logical_monitors)
  {
    ApplyMonitorsConfigLogicalMonitor m;
    m.m_x = malm.m_x;
    m.m_y = malm.m_y;
    m.m_scale = malm.m_scale;
    m.m_transform = malm.m_transform;
    m.m_primary = malm.m_primary;
    for (const auto &mam : malm.m_monitors)
    {
      GetCurrentStateMonitor state_monitor;
      bool found_state_monitor = false;
      for (const auto &sm : state->m_monitors)
      {
        if (sm.m_info.m_serial == mam.m_serial)
        {
          state_monitor = sm;
          found_state_monitor = true;
          break;
        }
      }
      if (!found_state_monitor)
      {
        qWarning() << "monitor not found in current state. serial:"
                   << mam.m_serial;
        return nullptr;
      }
      bool found_mode = false;
      for (const auto &mode : state_monitor.m_modes)
      {
        if (mode.m_id == mam.m_mode_id)
        {
          found_mode = true;
          break;
        }
      }
      if (!found_mode)
      {
        qWarning() << "monitor mode not found. serial:" << mam.m_serial
                   << "mode:" << mam.m_mode_id;
        return nullptr;
      }
      ApplyMonitorsConfigMonitor amcm(state_monitor.m_info.m_connector,
                                      mam.m_mode_id);
      m.m_monitors += amcm;
    }
    lms += m;
  }

  if (m_layout_mode != MonitorArrangementLayoutMode::UNKNOWN &&
      state->supportsChangingLayoutMode())
  {
    properties["layout-mode"] =
        QDBusVariant(QVariant(static_cast<uint>(m_layout_mode)));
  }

  return std::make_unique<ApplyMonitorsConfig>(state->m_serial, method, lms,
                                               properties);
}

bool MonitorArrangement::operator==(const MonitorArrangement &other) const
{
  // ignore version for equality comparison
  if (m_layout_mode != other.m_layout_mode)
  {
    return false;
  }
  return std::equal(m_logical_monitors.begin(), m_logical_monitors.end(),
                    other.m_logical_monitors.begin(),
                    other.m_logical_monitors.end());
}
