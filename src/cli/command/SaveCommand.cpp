#include "SaveCommand.h"
#include "mcm/Mcm.h"
#include <QCommandLineParser>

const QString SaveCommand::ID = QStringLiteral("save");

SaveCommand::SaveCommand(const QString name, const bool overwrite)
    : BaseCommand(SaveCommand::ID), m_name(name), m_overwrite(overwrite)
{
}

int SaveCommand::Run()
{
  const auto &state = Mcm::GetCurrentState();
  if (state == nullptr)
  {
    return EXIT_FAILURE;
  }

  auto current_ma = MonitorArrangement::createFromDisplayState(state);
  if (current_ma == nullptr)
  {
    return EXIT_FAILURE;
  }
  const auto success = Mcm::GetDataManager()->SaveMonitorArrangement(
      m_name, std::move(current_ma), m_overwrite);

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

std::unique_ptr<BaseCommand> SaveCommand::Parse(const QStringList &args)
{
  QCommandLineParser parser;
  parser.setApplicationDescription("saves the current monitor arrangement");
  parser.addHelpOption();
  parser.addPositionalArgument("name", "monitor arrangement name");
  const auto &overwriteOption = QCommandLineOption(
      "overwrite", QCoreApplication::translate(
                       "main", "overwrite an existing monitor arrangement"));
  parser.addOption(overwriteOption);

  if (!parser.parse(args))
  {
    return nullptr;
  }

  if (parser.isSet("help"))
  {
    showHelp(SaveCommand::ID, parser);
    return nullptr;
  }

  const auto &cmd_args = parser.positionalArguments();
  if (cmd_args.isEmpty())
  {
    showHelp(SaveCommand::ID, parser);
    return nullptr;
  }

  std::unique_ptr<BaseCommand> cmd =
      std::make_unique<SaveCommand>(cmd_args[0], parser.isSet(overwriteOption));
  return cmd;
}
