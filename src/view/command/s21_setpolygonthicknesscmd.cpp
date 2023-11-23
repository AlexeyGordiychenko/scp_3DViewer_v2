#include "s21_setpolygonthicknesscmd.h"

s21::SetPolygonThicknessCmd::SetPolygonThicknessCmd(double old_thickness, double new_thickness, View *mw)
    : view_(mw), old_thickness_(old_thickness), new_thickness_(new_thickness)
{

}

void s21::SetPolygonThicknessCmd::Redo()
{
    SetPolygonThickness(new_thickness_);
}

void s21::SetPolygonThicknessCmd::Undo()
{
    SetPolygonThickness(old_thickness_);
}

void s21::SetPolygonThicknessCmd::SetPolygonThickness(double thickness)
{
    Ui::View* ui = view_->getUI();
    ui->openGLWidget->edges_thickness = thickness / 10;
    ui->openGLWidget->update();
    ui->polygonThickness->setValue(thickness);
}
