#include <QApplication>
#include <QPushButton>
#include <mcm/config.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setApplicationName(MCM_APPLICATION);
  QApplication::setApplicationVersion(MCM_VERSION.toString());
  QPushButton button("TODO!", nullptr);
  button.resize(200, 100);
  button.show();
  return QApplication::exec();
}
