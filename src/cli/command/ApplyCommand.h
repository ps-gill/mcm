#ifndef MCM_APPLYCOMMAND_H
#define MCM_APPLYCOMMAND_H

#include "BaseCommand.h"

class ApplyCommand : public BaseCommand
{
private:
  const QString m_name;
  const bool m_temporary;
  const bool m_force;

public:
  explicit ApplyCommand(const QString name, bool temporary = false,
                        bool force = false);
  int Run() override;

  static const QString ID;
  static std::unique_ptr<BaseCommand> Parse(const QStringList &args);
};

#endif
