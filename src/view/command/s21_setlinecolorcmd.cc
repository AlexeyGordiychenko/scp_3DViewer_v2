#include "s21_setlinecolorcmd.h"

#include "../s21_view.h"

s21::SetLineColorCmd::SetLineColorCmd(QColor old_color, QColor color,
                                      View* view)
    : view_(view), old_color_(old_color), color_(color) {}

void s21::SetLineColorCmd::Redo() { view_->SetLineColor(color_); }

void s21::SetLineColorCmd::Undo() { view_->SetLineColor(old_color_); }
