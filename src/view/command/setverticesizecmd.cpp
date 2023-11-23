#include "setverticesizecmd.h"

s21::SetVerticeSizeCmd::SetVerticeSizeCmd(double old_thickness, double new_thickness, MainWindow *mw)
    : mw(mw), old_thickness(old_thickness), new_thickness(new_thickness)
{

}

void s21::SetVerticeSizeCmd::Redo()
{
    setVerticeSize(new_thickness);
}

void s21::SetVerticeSizeCmd::Undo()
{
    setVerticeSize(old_thickness);
}

void s21::SetVerticeSizeCmd::setVerticeSize(double thickness)
{
    Ui::MainWindow* ui = mw->getUI();
    ui->openGLWidget->vertice_size = thickness / 5;
    ui->openGLWidget->update();
    ui->sizeVertice->setValue(thickness);
}
