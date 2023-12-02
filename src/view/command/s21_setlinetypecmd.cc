#include "s21_setlinetypecmd.h"

#include "../s21_view.h"

s21::SetLineTypeCmd::SetLineTypeCmd(LineType old_type, LineType new_type,
                                    View* view)
    : view_(view), old_type_(old_type), new_type_(new_type) {}

void s21::SetLineTypeCmd::Redo() { view_->SetLineType(new_type_); }

void s21::SetLineTypeCmd::Undo() { view_->SetLineType(old_type_); }
