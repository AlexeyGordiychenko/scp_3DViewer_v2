#include "s21_setpolygontypecmd.h"

s21::SetPolygonTypeCmd::SetPolygonTypeCmd(polygonType old_type, polygonType new_type, View *mw)
:   view_(mw), old_type_(old_type), new_type_(new_type)
{

}

void s21::SetPolygonTypeCmd::Redo()
{
    SetPolygonType(new_type_);
}

void s21::SetPolygonTypeCmd::Undo()
{
    SetPolygonType(old_type_);
}

void s21::SetPolygonTypeCmd::SetPolygonType(polygonType type)
{
    Ui::View* ui = view_->getUI();
    ui->openGLWidget->edges_type = type;
    ui->openGLWidget->update();
    if (type == SOLID) {
        ui->solidPolygonType->setChecked(true);
        ui->dashedPolygonType->setChecked(false);
    } else {
        ui->solidPolygonType->setChecked(false);
        ui->dashedPolygonType->setChecked(true);
    }
}
