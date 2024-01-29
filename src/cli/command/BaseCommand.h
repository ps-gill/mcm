#ifndef MCM_BASECOMMAND_H
#define MCM_BASECOMMAND_H

#include <QCommandLineParser>
#include <QString>

class BaseCommand
{
protected:
  const QString &m_id;

public:
  explicit BaseCommand(const QString &id);
  [[nodiscard]] QString getId() const;
  static void showHelp(const QString &id, const QCommandLineParser &parser);
  virtual ~BaseCommand() = default;
  virtual int Run() = 0;
};

using CommandParser = std::unique_ptr<BaseCommand> (*)(const QStringList &);

#endif
