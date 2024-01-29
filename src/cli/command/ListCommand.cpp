#include "ListCommand.h"
#include "mcm/Mcm.h"
#include <QCommandLineParser>

const QString ListCommand::ID = QStringLiteral("list");

ListCommand::ListCommand(const QString name, const bool detailed)
    : BaseCommand(ListCommand::ID), m_name(name), m_detailed(detailed)
{
}

int ListCommand::Run()
{
  QStringList mas;
  if (m_name.isEmpty())
  {
    mas = Mcm::GetDataManager()->GetMonitorArrangementNames();
  }
  else
  {
    mas = {m_name};
  }
  if (!m_detailed)
  {
    qInfo("%s", mas.join(" ").toUtf8().constData());
    return EXIT_SUCCESS;
  }
  for (const auto &ma_name : mas)
  {
    const auto &ma = Mcm::GetDataManager()->LoadMonitorArrangement(ma_name);
    if (ma == nullptr)
    {
      qWarning() << "Unable to load " << ma_name << " monitor arrangement";
      continue;
    }
    qInfo() << "- " << ma_name;
    qInfo() << QJsonDocument(ma->toJson())
                   .toJson(QJsonDocument::Indented)
                   .constData();
  }
  return EXIT_SUCCESS;
}

std::unique_ptr<BaseCommand> ListCommand::Parse(const QStringList &args)
{
  QCommandLineParser parser;
  parser.setApplicationDescription("lists the saved monitor arrangements");
  parser.addHelpOption();
  parser.addPositionalArgument("name", "monitor arrangement name");
  const auto &detailedOption = QCommandLineOption(
      "detailed",
      QCoreApplication::translate("main", "show monitor arrangements details"));
  parser.addOption(detailedOption);

  if (!parser.parse(args))
  {
    return nullptr;
  }

  if (parser.isSet("help"))
  {
    showHelp(ListCommand::ID, parser);
    return nullptr;
  }

  QString name;
  const auto &cmd_args = parser.positionalArguments();
  if (!cmd_args.isEmpty())
  {
    name = cmd_args[0];
  }

  std::unique_ptr<BaseCommand> cmd =
      std::make_unique<ListCommand>(name, parser.isSet(detailedOption));
  return cmd;
}
