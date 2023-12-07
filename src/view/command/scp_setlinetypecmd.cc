#include "scp_setlinetypecmd.h"

#include "../scp_view.h"

scp::SetLineTypeCmd::SetLineTypeCmd(LineType old_type, LineType new_type,
                                    View* view)
    : view_(view), old_type_(old_type), new_type_(new_type) {}

void scp::SetLineTypeCmd::Redo() { view_->SetLineType(new_type_); }

void scp::SetLineTypeCmd::Undo() { view_->SetLineType(old_type_); }
