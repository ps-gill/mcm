#ifndef MCM_LISTCOMMAND_H
#define MCM_LISTCOMMAND_H

#include "BaseCommand.h"

class ListCommand : public BaseCommand
{
private:
  const QString m_name;
  const bool m_detailed;

public:
  explicit ListCommand(QString name, bool detailed = false);
  int Run() override;

  static const QString ID;
  static std::unique_ptr<BaseCommand> Parse(const QStringList &args);
};

#endif
