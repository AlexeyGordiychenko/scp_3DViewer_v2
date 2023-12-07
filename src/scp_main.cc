#include <QApplication>

#include "controller/scp_controller.h"
#include "model/scp_model.h"
#include "view/scp_view.h"

int main(int argc, char* argv[]) {
  QLocale::setDefault(QLocale::C);
  QApplication app(argc, argv);
  scp::Model model;
  scp::Controller controller(&model);
  scp::View view(&controller);
  view.show();
  return app.exec();
}
