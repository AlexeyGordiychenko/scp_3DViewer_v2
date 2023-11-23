#include "setverticetypecmd.h"

s21::SetVerticeTypeCmd::SetVerticeTypeCmd(s21_verticeType old_type, s21_verticeType new_type, MainWindow *mw)
:   mw(mw), old_type(old_type), new_type(new_type)
{

}

void s21::SetVerticeTypeCmd::Redo()
{
    setVerticeType(new_type);
}

void s21::SetVerticeTypeCmd::Undo()
{
    setVerticeType(old_type);
}

void s21::SetVerticeTypeCmd::setVerticeType(s21_verticeType type)
{
    Ui::MainWindow* ui = mw->getUI();
    ui->openGLWidget->vertice_type = type;
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
