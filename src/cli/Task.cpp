#include "Task.h"
#include "command/Commands.h"
#include "mcm/Mcm.h"

Task::Task(QCoreApplication *parent) : QObject(parent) { app = parent; }

void Task::run()
{
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  const auto &dataOption = QCommandLineOption(
      "data", QCoreApplication::translate("main", "data directory path"),
      "path", Mcm::defaultDataDirectory());
  parser.addOption(dataOption);
  parser.setOptionsAfterPositionalArgumentsMode(
      QCommandLineParser::ParseAsPositionalArguments);
  parser.addPositionalArgument("command", "command to run",
                               '(' + Commands::Parsers.keys().join('|') + ')');

  parser.process(*app);
  const QStringList &args = parser.positionalArguments();
  Mcm::initialize(parser.value(dataOption));
  const auto &cmd = Commands::Parse(args);
  int exit_code = EXIT_FAILURE;
  if (cmd != nullptr)
  {
    exit_code = cmd->Run();
  }

  emit finished(exit_code);
}
