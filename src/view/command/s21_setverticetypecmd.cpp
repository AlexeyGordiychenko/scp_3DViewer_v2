#include "s21_setverticetypecmd.h"

s21::SetVerticeTypeCmd::SetVerticeTypeCmd(verticeType old_type, verticeType new_type, View *view)
:   view_(view), old_type_(old_type), new_type_(new_type)
{

}

void s21::SetVerticeTypeCmd::Redo()
{
    SetVerticeType(new_type_);
}

void s21::SetVerticeTypeCmd::Undo()
{
    SetVerticeType(old_type_);
}

void s21::SetVerticeTypeCmd::SetVerticeType(verticeType type)
{
    Ui::View* ui = view_->GetUI();
    ui->openGLWidget->vertice_type_ = type;
    ui->openGLWidget->update();
    if (type == NONE) {
        ui->noneVertice->setChecked(true);
        ui->circleVertice->setChecked(false);
        ui->squareVertice->setChecked(false);
    } else if (type == CIRCLE){
        ui->noneVertice->setChecked(false);
        ui->circleVertice->setChecked(true);
        ui->squareVertice->setChecked(false);
    } else {
        ui->noneVertice->setChecked(false);
        ui->circleVertice->setChecked(false);
        ui->squareVertice->setChecked(true);
    }
}
