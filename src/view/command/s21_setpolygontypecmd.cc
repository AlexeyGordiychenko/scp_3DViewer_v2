#include "s21_setpolygontypecmd.h"

s21::SetPolygonTypeCmd::SetPolygonTypeCmd(PolygonType old_type,
                                          PolygonType new_type, Ui::View* ui)
    : ui_(ui), old_type_(old_type), new_type_(new_type) {}

void s21::SetPolygonTypeCmd::Redo() { SetPolygonType(new_type_); }

void s21::SetPolygonTypeCmd::Undo() { SetPolygonType(old_type_); }

void s21::SetPolygonTypeCmd::SetPolygonType(PolygonType type) {
  ui_->openGLWidget->edges_type_ = type;
  ui_->openGLWidget->update();
  if (type == kSolid) {
    ui_->solidPolygonType->setChecked(true);
    ui_->dashedPolygonType->setChecked(false);
  } else {
    ui_->solidPolygonType->setChecked(false);
    ui_->dashedPolygonType->setChecked(true);
  }
}
