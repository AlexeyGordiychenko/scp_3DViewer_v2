#include "s21_setverticetypecmd.h"

s21::SetVerticeTypeCmd::SetVerticeTypeCmd(VerticeType old_type,
                                          VerticeType new_type, Ui::View* ui)
    : ui_(ui), old_type_(old_type), new_type_(new_type) {}

void s21::SetVerticeTypeCmd::Redo() { SetVerticeType(new_type_); }

void s21::SetVerticeTypeCmd::Undo() { SetVerticeType(old_type_); }

void s21::SetVerticeTypeCmd::SetVerticeType(VerticeType type) {
  ui_->openGLWidget->vertice_type_ = type;
  ui_->openGLWidget->update();
  if (type == kNone) {
    ui_->noneVerticeType->setChecked(true);
    ui_->circleVerticeType->setChecked(false);
    ui_->squareVerticeType->setChecked(false);
  } else if (type == kCircle) {
    ui_->noneVerticeType->setChecked(false);
    ui_->circleVerticeType->setChecked(true);
    ui_->squareVerticeType->setChecked(false);
  } else {
    ui_->noneVerticeType->setChecked(false);
    ui_->circleVerticeType->setChecked(false);
    ui_->squareVerticeType->setChecked(true);
  }
}
