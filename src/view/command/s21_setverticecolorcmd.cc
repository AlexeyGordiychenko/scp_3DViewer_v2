#include "s21_setverticecolorcmd.h"

#include "../s21_view.h"

s21::SetVerticeColorCmd::SetVerticeColorCmd(QColor old_color, QColor color,
                                            View* view)
    : view_(view), old_color_(old_color), color_(color) {}

void s21::SetVerticeColorCmd::Redo() { view_->SetVerticeColor(color_); }

void s21::SetVerticeColorCmd::Undo() { view_->SetVerticeColor(old_color_); }
