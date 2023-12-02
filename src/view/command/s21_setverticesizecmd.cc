#include "s21_setverticesizecmd.h"

#include "../s21_view.h"

s21::SetVerticeSizeCmd::SetVerticeSizeCmd(double old_thickness,
                                          double new_thickness, View* view)
    : view_(view),
      old_thickness_(old_thickness),
      new_thickness_(new_thickness) {}

void s21::SetVerticeSizeCmd::Redo() {
  view_->SetVerticeSize(new_thickness_);
  prev_old_ = new_thickness_;
}

void s21::SetVerticeSizeCmd::Undo() {
  view_->SetVerticeSize(old_thickness_);
  prev_old_ = old_thickness_;
}

void s21::SetVerticeSizeCmd::init_old(double old) { prev_old_ = old; }

double s21::SetVerticeSizeCmd::get_old() { return prev_old_; }
