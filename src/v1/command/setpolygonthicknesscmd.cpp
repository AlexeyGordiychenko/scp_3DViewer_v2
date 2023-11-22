#include "setpolygonthicknesscmd.h"

s21::SetPolygonThicknessCmd::SetPolygonThicknessCmd(double old_thickness, double new_thickness, MainWindow *mw)
    : mw(mw), old_thickness(old_thickness), new_thickness(new_thickness)
{

}

void s21::SetPolygonThicknessCmd::redo()
{
    setPolygonThickness(new_thickness);
}

void s21::SetPolygonThicknessCmd::undo()
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

//void MainWindow::s21_setPolygonThickness(int value) {
//  ui->openGLWidget->edges_thickness = value / 10;
//  ui->openGLWidget->update();
//}
