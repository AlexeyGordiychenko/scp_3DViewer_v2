#include "s21_setverticesizecmd.h"

s21::SetVerticeSizeCmd::SetVerticeSizeCmd(double old_thickness,
                                          double new_thickness, Ui::View* ui)
    : ui_(ui), old_thickness_(old_thickness), new_thickness_(new_thickness) {}

void s21::SetVerticeSizeCmd::Redo() { SetVerticeSize(new_thickness_); }

void s21::SetVerticeSizeCmd::Undo() { SetVerticeSize(old_thickness_); }

void s21::SetVerticeSizeCmd::init_old(double old) { prev_old_ = old; }

double s21::SetVerticeSizeCmd::get_old() { return prev_old_; }

void s21::SetVerticeSizeCmd::SetVerticeSize(double thickness) {
  ui_->openGLWidget->vertice_size_ = thickness / 5;
  ui_->openGLWidget->update();
  ui_->verticeSize->setValue(thickness);
  prev_old_ = thickness;
}
