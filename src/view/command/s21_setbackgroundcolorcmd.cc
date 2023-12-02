#include "s21_setbackgroundcolorcmd.h"

#include "../s21_view.h"

s21::SetBackgroundColorCmd::SetBackgroundColorCmd(QColor old_color,
                                                  QColor color, View* view)
    : view_(view), old_color_(old_color), color_(color) {}

void s21::SetBackgroundColorCmd::Undo() {
  view_->SetBackgroundColor(old_color_);
}

void s21::SetBackgroundColorCmd::Redo() { view_->SetBackgroundColor(color_); }
