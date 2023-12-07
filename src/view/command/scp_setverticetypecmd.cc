#include "scp_setverticetypecmd.h"

#include "../scp_view.h"

scp::SetVerticeTypeCmd::SetVerticeTypeCmd(VerticeType old_type,
                                          VerticeType new_type, View* view)
    : view_(view), old_type_(old_type), new_type_(new_type) {}

void scp::SetVerticeTypeCmd::Redo() { view_->SetVerticeType(new_type_); }

void scp::SetVerticeTypeCmd::Undo() { view_->SetVerticeType(old_type_); }
