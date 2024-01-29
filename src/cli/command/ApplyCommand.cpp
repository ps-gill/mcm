#include "ApplyCommand.h"
#include "mcm/Mcm.h"
#include <QCommandLineParser>

const QString ApplyCommand::ID = QStringLiteral("apply");

ApplyCommand::ApplyCommand(const QString name, bool temporary, bool force)
    : BaseCommand(ApplyCommand::ID), m_name(name), m_temporary(temporary),
      m_force(force)
{
}

int ApplyCommand::Run()
{
  auto target_ma = Mcm::GetDataManager()->LoadMonitorArrangement(m_name);
  if (!target_ma)
  {
    return EXIT_FAILURE;
  }
  auto state = Mcm::GetCurrentState();
  if (!state)
  {
    return EXIT_FAILURE;
  }
  auto current_ma = MonitorArrangement::createFromDisplayState(state);
  if (current_ma == nullptr)
  {
    return EXIT_FAILURE;
  }
  if (*target_ma == *current_ma)
  {
    if (!m_force)
    {
      qInfo() << m_name << "is already the current monitor arrangement.";
      return EXIT_SUCCESS;
    }
  }
  auto amc = target_ma->toApplyMonitorConfig(
      m_temporary ? ApplyMonitorConfigMethod::TEMPORARY
                  : ApplyMonitorConfigMethod::PERSISTENT,
      state);
  if (!amc)
  {
    return EXIT_FAILURE;
  }
  return Mcm::ApplyConfig(amc) ? EXIT_SUCCESS : EXIT_FAILURE;
}

std::unique_ptr<BaseCommand> ApplyCommand::Parse(const QStringList &args)
{
  QCommandLineParser parser;
  parser.setApplicationDescription("applies a monitor arrangement");
  parser.addHelpOption();
  parser.addPositionalArgument("name", "monitor arrangement name");
  const auto &temporaryOption = QCommandLineOption(
      "temporary", QCoreApplication::translate(
                       "main", "monitor arrangement application is temporary"));
  parser.addOption(temporaryOption);
  const auto &forceOption = QCommandLineOption(
      "force",
      QCoreApplication::translate("main", "re-applies monitor arrangement"));
  parser.addOption(forceOption);

  if (!parser.parse(args))
  {
    return nullptr;
  }

  if (parser.isSet("help"))
  {
    showHelp(ApplyCommand::ID, parser);
    return nullptr;
  }

  const auto &cmd_args = parser.positionalArguments();
  if (cmd_args.isEmpty())
  {
    showHelp(ApplyCommand::ID, parser);
    return nullptr;
  }

  std::unique_ptr<BaseCommand> cmd = std::make_unique<ApplyCommand>(
      cmd_args[0], parser.isSet(temporaryOption), parser.isSet(forceOption));
  return cmd;
}
