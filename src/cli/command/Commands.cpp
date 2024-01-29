#include "Commands.h"

#include "ApplyCommand.h"
#include "DeleteCommand.h"
#include "ListCommand.h"
#include "SaveCommand.h"

const QHash<QString, CommandParser> Commands::Parsers = {
    {ApplyCommand::ID, ApplyCommand::Parse},
    {DeleteCommand::ID, DeleteCommand::Parse},
    {ListCommand::ID, ListCommand::Parse},
    {SaveCommand::ID, SaveCommand::Parse}};

std::unique_ptr<BaseCommand> Commands::Parse(const QStringList &args)
{
  if (args.isEmpty())
  {
    return nullptr;
  }

  const auto &command_id = args.first();
  if (!Commands::Parsers.contains(command_id))
  {
    return nullptr;
  }

  return Commands::Parsers.value(command_id)(args);
}
