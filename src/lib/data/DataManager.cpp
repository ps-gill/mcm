#include <QDir>
#include <QJsonDocument>
#include <QStandardPaths>

#include "../include/mcm/DataManager.h"

static QString da_name_to_file_name(const QString &name)
{
  return name + ".json";
}

DataManager::DataManager(const QString &data_directory)
{
  m_data_directory = data_directory;
  m_ma_directory = m_data_directory + "/" + "ma";
}

bool DataManager::SaveMonitorArrangement(const QString &name,
                                         std::unique_ptr<MonitorArrangement> ma,
                                         const bool overwrite)
{
  QDir dd = QDir(m_ma_directory);
  const auto &file_path = dd.filePath(da_name_to_file_name(name));
  if (QFile::exists(file_path) && !overwrite)
  {
    qWarning() << "Monitor arrangement already exists" << file_path;
    return false;
  }
  if (!dd.exists() && !dd.mkpath(m_ma_directory))
  {
    qWarning() << "Unable to create directory '" << m_ma_directory << "'";
    return false;
  }
  auto f = QFile(file_path);
  if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate))
  {
    qWarning() << "Unable to open file '" << f.fileName() << "'";
    return false;
  }

  auto data = QJsonDocument(ma->toJson()).toJson(QJsonDocument::Indented);
  return f.write(data) == data.length();
}

std::unique_ptr<MonitorArrangement>
DataManager::LoadMonitorArrangement(const QString &name)
{
  auto f = QFile(m_ma_directory + "/" + da_name_to_file_name(name));
  if (!f.open(QIODevice::ReadOnly))
  {
    qWarning() << "Unable to open file" << f.fileName();
    return nullptr;
  }
  QJsonParseError error;
  auto doc = QJsonDocument::fromJson(f.readAll(), &error);
  if (doc.isNull())
  {
    qWarning() << error.errorString();
    return nullptr;
  }

  if (!doc.isObject())
  {
    qWarning() << "Monitor arrangement json is not an object";
    return nullptr;
  }

  return MonitorArrangement::fromJson(doc.object());
}

QStringList DataManager::GetMonitorArrangementNames()
{
  return QDir(m_ma_directory)
      .entryList({"*.json"}, QDir::Files, QDir::Name)
      .replaceInStrings(".json", "");
}

bool DataManager::DeleteMonitorArrangement(const QString &name)
{
  auto f = QFile(m_ma_directory + "/" + da_name_to_file_name(name));
  if (!f.exists())
  {
    qWarning() << "Monitor arrangement not found " << f.fileName();
    return false;
  }
  return f.remove();
}
