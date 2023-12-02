#include "s21_setlinethicknesscmd.h"

#include "../s21_view.h"

s21::SetLineThicknessCmd::SetLineThicknessCmd(double old_thickness,
                                              double new_thickness, View* view)
    : view_(view),
      old_thickness_(old_thickness),
      new_thickness_(new_thickness) {}

void s21::SetLineThicknessCmd::Redo() {
  view_->SetLineThickness(new_thickness_);
  prev_old_ = new_thickness_;
}

void s21::SetLineThicknessCmd::Undo() {
  view_->SetLineThickness(old_thickness_);
  prev_old_ = old_thickness_;
}

void s21::SetLineThicknessCmd::init_old(double old) { prev_old_ = old; }

double s21::SetLineThicknessCmd::get_old() { return prev_old_; }
