#include "scp_projectiontypechangecmd.h"

#include "../scp_view.h"

scp::ProjectionTypeChangeCommand::ProjectionTypeChangeCommand(
    ProjectionType old_idx, ProjectionType new_idx, View* view)
    : view_(view), old_idx_(old_idx), new_idx_(new_idx) {}

void scp::ProjectionTypeChangeCommand::Undo() {
  view_->SetProjectionType(old_idx_);
}

void scp::ProjectionTypeChangeCommand::Redo() {
  view_->SetProjectionType(new_idx_);
}
