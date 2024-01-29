#ifndef MCM_SAVECOMMAND_H
#define MCM_SAVECOMMAND_H

#include "BaseCommand.h"

class SaveCommand : public BaseCommand
{
private:
  const QString m_name;
  const bool m_overwrite;

public:
  explicit SaveCommand(const QString name, bool overwrite = false);
  int Run() override;

  static const QString ID;
  static std::unique_ptr<BaseCommand> Parse(const QStringList &args);
};

#endif
