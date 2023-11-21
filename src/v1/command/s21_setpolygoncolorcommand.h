#ifndef S21_SETPOLYGONCOLORCOMMAND_H
#define S21_SETPOLYGONCOLORCOMMAND_H

#include "s21_command.h"
#include <QColor>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class s21_setPolygonColorCommand : public s21_Command
{
public:
    s21_setPolygonColorCommand(QColor old_color, QColor color, MainWindow* mw);

    // s21_Command interface
public:
    void redo() override;
    void undo() override;
private:
    MainWindow* mw;
    void setPolygonColor(QColor color);
    QColor old_color;
    QColor color;
};

#endif // S21_SETPOLYGONCOLORCOMMAND_H

//void MainWindow::s21_setPolygonColor() {
//  QColor color = QColorDialog::getColor();
//  if (color.isValid()) {
//    ui->openGLWidget->pol_red = color.redF();
//    ui->openGLWidget->pol_green = color.greenF();
//    ui->openGLWidget->pol_blue = color.blueF();
//    char rgba_color[40];
//    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
//            color.green(), color.blue());
//    ui->setPolygonColor->setStyleSheet(rgba_color);
//    ui->openGLWidget->update();
//  }
//}
