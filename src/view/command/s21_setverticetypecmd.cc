#include "s21_setverticetypecmd.h"

#include "../s21_view.h"

s21::SetVerticeTypeCmd::SetVerticeTypeCmd(VerticeType old_type,
                                          VerticeType new_type, View* view)
    : view_(view), old_type_(old_type), new_type_(new_type) {}

void s21::SetVerticeTypeCmd::Redo() { view_->SetVerticeType(new_type_); }

void s21::SetVerticeTypeCmd::Undo() { view_->SetVerticeType(old_type_); }
