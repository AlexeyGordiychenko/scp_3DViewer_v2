#include "s21_setpolygonthicknesscmd.h"

s21::SetPolygonThicknessCmd::SetPolygonThicknessCmd(double old_thickness,
                                                    double new_thickness,
                                                    Ui::View* ui)
    : ui_(ui), old_thickness_(old_thickness), new_thickness_(new_thickness) {}

void s21::SetPolygonThicknessCmd::Redo() {
  SetPolygonThickness(new_thickness_);
}

void s21::SetPolygonThicknessCmd::Undo() {
  SetPolygonThickness(old_thickness_);
}

void s21::SetPolygonThicknessCmd::init_old(double old) { prev_old_ = old; }

double s21::SetPolygonThicknessCmd::get_old() { return prev_old_; }

void s21::SetPolygonThicknessCmd::SetPolygonThickness(double thickness) {
  ui_->openGLWidget->edges_thickness_ = thickness / 10;
  ui_->openGLWidget->update();
  ui_->polygonThickness->setValue(thickness);
  prev_old_ = thickness;
}
