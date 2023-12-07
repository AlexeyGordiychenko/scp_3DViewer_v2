#include "scp_setverticesizecmd.h"

#include "../scp_view.h"

scp::SetVerticeSizeCmd::SetVerticeSizeCmd(double old_thickness,
                                          double new_thickness, View* view)
    : view_(view),
      old_thickness_(old_thickness),
      new_thickness_(new_thickness) {}

void scp::SetVerticeSizeCmd::Redo() {
  view_->SetVerticeSize(new_thickness_);
  prev_old_ = new_thickness_;
}

void scp::SetVerticeSizeCmd::Undo() {
  view_->SetVerticeSize(old_thickness_);
  prev_old_ = old_thickness_;
}

void scp::SetVerticeSizeCmd::init_old(double old) { prev_old_ = old; }

double scp::SetVerticeSizeCmd::get_old() { return prev_old_; }
