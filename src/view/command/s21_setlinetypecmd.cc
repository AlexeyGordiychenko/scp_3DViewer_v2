#include "s21_setlinetypecmd.h"

s21::SetLineTypeCmd::SetLineTypeCmd(LineType old_type, LineType new_type,
                                    Ui::View* ui)
    : ui_(ui), old_type_(old_type), new_type_(new_type) {}

void s21::SetLineTypeCmd::Redo() { SetLineType(new_type_); }

void s21::SetLineTypeCmd::Undo() { SetLineType(old_type_); }

void s21::SetLineTypeCmd::SetLineType(LineType type) {
  ui_->openGLWidget->edges_type_ = type;
  ui_->openGLWidget->update();
  if (type == kSolid) {
    ui_->solidLineType->setChecked(true);
    ui_->dashedLineType->setChecked(false);
  } else {
    ui_->solidLineType->setChecked(false);
    ui_->dashedLineType->setChecked(true);
  }
}
