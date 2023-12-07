#include "scp_setlinecolorcmd.h"

#include "../scp_view.h"

scp::SetLineColorCmd::SetLineColorCmd(QColor old_color, QColor color,
                                      View* view)
    : view_(view), old_color_(old_color), color_(color) {}

void scp::SetLineColorCmd::Redo() { view_->SetLineColor(color_); }

void scp::SetLineColorCmd::Undo() { view_->SetLineColor(old_color_); }
