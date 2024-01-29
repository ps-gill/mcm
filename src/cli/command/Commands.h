#ifndef MCM_COMMANDS_H
#define MCM_COMMANDS_H

#include <QHash>
#include <QStringList>

#include "BaseCommand.h"

class Commands
{
public:
  static const QHash<QString, CommandParser> Parsers;
  static std::unique_ptr<BaseCommand> Parse(const QStringList &args);
};

#endif
