#include "s21_setpolygonthicknesscmd.h"

s21::SetLineThicknessCmd::SetLineThicknessCmd(double old_thickness,
                                              double new_thickness,
                                              Ui::View* ui)
    : ui_(ui), old_thickness_(old_thickness), new_thickness_(new_thickness) {}

void s21::SetLineThicknessCmd::Redo() { SetLineThickness(new_thickness_); }

void s21::SetLineThicknessCmd::Undo() { SetLineThickness(old_thickness_); }

void s21::SetLineThicknessCmd::init_old(double old) { prev_old_ = old; }

double s21::SetLineThicknessCmd::get_old() { return prev_old_; }

void s21::SetLineThicknessCmd::SetLineThickness(double thickness) {
  ui_->openGLWidget->edges_thickness_ = thickness / 10;
  ui_->openGLWidget->update();
  ui_->lineThickness->setValue(thickness);
  prev_old_ = thickness;
}
