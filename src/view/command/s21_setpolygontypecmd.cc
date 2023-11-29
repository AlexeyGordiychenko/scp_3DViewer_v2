#include "s21_setpolygontypecmd.h"

s21::SetPolygonTypeCmd::SetPolygonTypeCmd(PolygonType old_type,
                                          PolygonType new_type, View* mw)
    : view_(mw), old_type_(old_type), new_type_(new_type) {}

void s21::SetPolygonTypeCmd::Redo() { SetPolygonType(new_type_); }

void s21::SetPolygonTypeCmd::Undo() { SetPolygonType(old_type_); }

void s21::SetPolygonTypeCmd::SetPolygonType(PolygonType type) {
  Ui::View* ui = view_->GetUI();
  ui->openGLWidget->edges_type_ = type;
  ui->openGLWidget->update();
  if (type == kSolid) {
    ui->solidPolygonType->setChecked(true);
    ui->dashedPolygonType->setChecked(false);
  } else {
    ui->solidPolygonType->setChecked(false);
    ui->dashedPolygonType->setChecked(true);
  }
}
