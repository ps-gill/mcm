#include "Task.h"
#include <QCoreApplication>
#include <QTimer>
#include <mcm/Mcm.h>
#include <mcm/config.h>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  QCoreApplication::setApplicationName(MCM_APPLICATION);
  QCoreApplication::setApplicationVersion(MCM_VERSION.toString());
  Task t(&a);
  QObject::connect(&a, &QCoreApplication::aboutToQuit, &a, &Mcm::terminate);
  QObject::connect(&t, &Task::finished, &a, &QCoreApplication::exit,
                   Qt::QueuedConnection);
  QTimer::singleShot(0, &t, &Task::run);
  return QCoreApplication::exec();
}
