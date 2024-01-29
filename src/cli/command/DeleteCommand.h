#ifndef MCM_DELETECOMMAND_H
#define MCM_DELETECOMMAND_H

#include "BaseCommand.h"

class DeleteCommand : public BaseCommand
{
private:
  const QString m_name;
  const bool m_force;

public:
  explicit DeleteCommand(QString name, bool force = false);
  int Run() override;

  static const QString ID;
  static std::unique_ptr<BaseCommand> Parse(const QStringList &args);
};

#endif
