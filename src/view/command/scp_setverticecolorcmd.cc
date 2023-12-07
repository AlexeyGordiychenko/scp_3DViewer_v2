#include "scp_setverticecolorcmd.h"

#include "../scp_view.h"

scp::SetVerticeColorCmd::SetVerticeColorCmd(QColor old_color, QColor color,
                                            View* view)
    : view_(view), old_color_(old_color), color_(color) {}

void scp::SetVerticeColorCmd::Redo() { view_->SetVerticeColor(color_); }

void scp::SetVerticeColorCmd::Undo() { view_->SetVerticeColor(old_color_); }
