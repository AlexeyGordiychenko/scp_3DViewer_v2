#include "setpolygonthicknesscmd.h"

s21::SetPolygonThicknessCmd::SetPolygonThicknessCmd(double old_thickness, double new_thickness, MainWindow *mw)
    : mw(mw), old_thickness(old_thickness), new_thickness(new_thickness)
{

}

void s21::SetPolygonThicknessCmd::Redo()
{
    setPolygonThickness(new_thickness);
}

void s21::SetPolygonThicknessCmd::Undo()
{
    setPolygonThickness(old_thickness);
}

void s21::SetPolygonThicknessCmd::setPolygonThickness(double thickness)
{
    Ui::MainWindow* ui = mw->getUI();
    ui->openGLWidget->edges_thickness = thickness / 10;
    ui->openGLWidget->update();
    ui->polygonThickness->setValue(thickness);
}
