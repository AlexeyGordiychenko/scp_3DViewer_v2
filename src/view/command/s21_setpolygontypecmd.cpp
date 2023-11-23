#include "s21_polygontypecommand.h"

s21_PolygonTypeCommand::s21_PolygonTypeCommand(s21_polygonType old_type, s21_polygonType new_type, MainWindow *mw)
:   mw(mw), old_type(old_type), new_type(new_type)
{

}

void s21_PolygonTypeCommand::redo()
{
    setPolygonType(new_type);
}

void s21_PolygonTypeCommand::undo()
{
    setPolygonType(old_type);
}

void s21_PolygonTypeCommand::setPolygonType(s21_polygonType type)
{
    Ui::MainWindow* ui = mw->getUI();
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
