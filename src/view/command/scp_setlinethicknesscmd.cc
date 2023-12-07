#include "scp_setlinethicknesscmd.h"

#include "../scp_view.h"

scp::SetLineThicknessCmd::SetLineThicknessCmd(double old_thickness,
                                              double new_thickness, View* view)
    : view_(view),
      old_thickness_(old_thickness),
      new_thickness_(new_thickness) {}

void scp::SetLineThicknessCmd::Redo() {
  view_->SetLineThickness(new_thickness_);
  prev_old_ = new_thickness_;
}

void scp::SetLineThicknessCmd::Undo() {
  view_->SetLineThickness(old_thickness_);
  prev_old_ = old_thickness_;
}

void scp::SetLineThicknessCmd::init_old(double old) { prev_old_ = old; }

double scp::SetLineThicknessCmd::get_old() { return prev_old_; }
