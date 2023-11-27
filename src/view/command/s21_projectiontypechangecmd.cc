#include "s21_projectiontypechangecmd.h"

#include "../s21_view.h"
#include "ui_s21_view.h"

s21::ProjectionTypeChangeCommand::ProjectionTypeChangeCommand(int old_idx,
                                                              int new_idx,
                                                              View* view)
    : view_(view), old_idx_(old_idx), new_idx_(new_idx) {}

void s21::ProjectionTypeChangeCommand::Undo() { SetProjectionType(old_idx_); }

void s21::ProjectionTypeChangeCommand::Redo() { SetProjectionType(new_idx_); }

void s21::ProjectionTypeChangeCommand::SetProjectionType(int idx) {
  Ui::View* ui = view_->GetUI();
  ui->openGLWidget->SetProjectionType(idx);
  ui->openGLWidget->update();
  ui->projectionType->setCurrentIndex(idx);
}
