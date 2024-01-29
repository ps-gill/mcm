#ifndef MCM_TASK_H
#define MCM_TASK_H

#include <QCoreApplication>
#include <QObject>

class Task : public QObject
{
  Q_OBJECT
public:
  explicit Task(QCoreApplication *parent);

private:
  const QCoreApplication *app;

public slots:
  void run();

signals:
  void finished(int exit_code);
};
#endif
