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

//void MainWindow::setPolygonType(s21_polygonType type)
//{
//    ui->openGLWidget->edges_type = type;
//    ui->openGLWidget->update();
//}

//void MainWindow::s21_solidPolygonType() {
//  ui->openGLWidget->edges_type = SOLID;
//  ui->openGLWidget->update();
//}

//void MainWindow::s21_dashedPolygonType() {
//  ui->openGLWidget->edges_type = DASHED;
//  ui->openGLWidget->update();
//}

//#include "s21_setpolygoncolorcommand.h"

//s21_setPolygonColorCommand::s21_setPolygonColorCommand(QColor old_color, QColor color, MainWindow *mw)
//    :   mw(mw), old_color(old_color), color(color)
//{

//}

//void s21_setPolygonColorCommand::redo()
//{
//    setPolygonColor(color);
//}

//void s21_setPolygonColorCommand::undo()
//{
//    setPolygonColor(old_color);
//}

//void s21_setPolygonColorCommand::setPolygonColor(QColor color)
//{
//    Ui::MainWindow* ui = mw->getUI();
//    if (color.isValid()) {
//        ui->openGLWidget->pol_red = color.redF();
//        ui->openGLWidget->pol_green = color.greenF();
//        ui->openGLWidget->pol_blue = color.blueF();
//        char rgba_color[40];
//        sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
//                color.green(), color.blue());
//        ui->setPolygonColor->setStyleSheet(rgba_color);
//        ui->openGLWidget->update();
//    }
//}
