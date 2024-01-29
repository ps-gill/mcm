#include "DeleteCommand.h"
#include "mcm/Mcm.h"
#include <QCommandLineParser>

const QString DeleteCommand::ID = QStringLiteral("delete");

DeleteCommand::DeleteCommand(const QString name, const bool force)
    : BaseCommand(DeleteCommand::ID), m_name(name), m_force(force)
{
}

int DeleteCommand::Run()
{
  if (!m_force)
  {
    const auto &delete_ma =
        Mcm::GetDataManager()->LoadMonitorArrangement(m_name);
    if (delete_ma == nullptr)
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
    if (*delete_ma == *current_ma)
    {
      qInfo() << m_name << "is the current monitor arrangement";
      qInfo() << "Use --force flag to delete current monitor arrangement";
      return EXIT_SUCCESS;
    }
  }
  return Mcm::GetDataManager()->DeleteMonitorArrangement(m_name) ? EXIT_SUCCESS
                                                                 : EXIT_FAILURE;
}

std::unique_ptr<BaseCommand> DeleteCommand::Parse(const QStringList &args)
{
  QCommandLineParser parser;
  parser.setApplicationDescription("delete a saved monitor arrangement");
  parser.addHelpOption();
  parser.addPositionalArgument("name", "monitor arrangement name");
  const auto &forceOption = QCommandLineOption(
      "force", QCoreApplication::translate(
                   "main", "deletes even when current monitor arrangement"));
  parser.addOption(forceOption);

  if (!parser.parse(args))
  {
    return nullptr;
  }

  if (parser.isSet("help"))
  {
    showHelp(DeleteCommand::ID, parser);
    return nullptr;
  }

  const auto &cmd_args = parser.positionalArguments();
  if (cmd_args.isEmpty())
  {
    showHelp(DeleteCommand::ID, parser);
    return nullptr;
  }

  std::unique_ptr<BaseCommand> cmd =
      std::make_unique<DeleteCommand>(cmd_args[0], parser.isSet(forceOption));
  return cmd;
}
