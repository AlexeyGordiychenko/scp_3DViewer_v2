#include "s21_setverticesizecmd.h"

s21::SetVerticeSizeCmd::SetVerticeSizeCmd(double old_thickness, double new_thickness, View *view)
    : view_(view), old_thickness_(old_thickness), new_thickness_(new_thickness)
{

}

void s21::SetVerticeSizeCmd::Redo()
{
    SetVerticeSize(new_thickness_);
}

void s21::SetVerticeSizeCmd::Undo()
{
    SetVerticeSize(old_thickness_);
}

void s21::SetVerticeSizeCmd::SetVerticeSize(double thickness)
{
    Ui::View* ui = view_->GetUI();
    ui->openGLWidget->vertice_size_ = thickness / 5;
    ui->openGLWidget->update();
    ui->sizeVertice->setValue(thickness);
}
