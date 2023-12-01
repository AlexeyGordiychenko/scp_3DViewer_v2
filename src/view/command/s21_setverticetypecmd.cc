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
    ui_->noneVertice->setChecked(true);
    ui_->circleVertice->setChecked(false);
    ui_->squareVertice->setChecked(false);
  } else if (type == kCircle) {
    ui_->noneVertice->setChecked(false);
    ui_->circleVertice->setChecked(true);
    ui_->squareVertice->setChecked(false);
  } else {
    ui_->noneVertice->setChecked(false);
    ui_->circleVertice->setChecked(false);
    ui_->squareVertice->setChecked(true);
  }
}
