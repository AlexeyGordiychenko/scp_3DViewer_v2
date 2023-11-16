#include <QApplication>

#include "controller/s21_controller.h"
#include "model/s21_model.h"
#include "view/s21_view.h"

int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale::C);
  QApplication app(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);
  view.show();
  return app.exec();
}
