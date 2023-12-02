#include "s21_projectiontypechangecmd.h"

#include "../s21_view.h"

s21::ProjectionTypeChangeCommand::ProjectionTypeChangeCommand(
    ProjectionType old_idx, ProjectionType new_idx, View* view)
    : view_(view), old_idx_(old_idx), new_idx_(new_idx) {}

void s21::ProjectionTypeChangeCommand::Undo() {
  view_->SetProjectionType(old_idx_);
}

void s21::ProjectionTypeChangeCommand::Redo() {
  view_->SetProjectionType(new_idx_);
}
