#include "scp_setbackgroundcolorcmd.h"

#include "../scp_view.h"

scp::SetBackgroundColorCmd::SetBackgroundColorCmd(QColor old_color,
                                                  QColor color, View* view)
    : view_(view), old_color_(old_color), color_(color) {}

void scp::SetBackgroundColorCmd::Undo() {
  view_->SetBackgroundColor(old_color_);
}

void scp::SetBackgroundColorCmd::Redo() { view_->SetBackgroundColor(color_); }
