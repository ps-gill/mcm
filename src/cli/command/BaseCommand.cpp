#include "BaseCommand.h"

BaseCommand::BaseCommand(const QString &mId) : m_id(mId) {}

QString BaseCommand::getId() const { return m_id; }

void BaseCommand::showHelp(const QString &id, const QCommandLineParser &parser)
{
  QTextStream(stdout) << parser.helpText().replace(
      QStringLiteral("[options]"), id + QStringLiteral(" [options]"));
}
