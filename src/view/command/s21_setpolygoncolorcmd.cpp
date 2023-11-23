#include "s21_setpolygoncolorcommand.h"

s21_setPolygonColorCommand::s21_setPolygonColorCommand(QColor old_color, QColor color, MainWindow *mw)
    :   mw(mw), old_color(old_color), color(color)
{

}

void s21_setPolygonColorCommand::redo()
{
    setPolygonColor(color);
}

void s21_setPolygonColorCommand::undo()
{
    setPolygonColor(old_color);
}

void s21_setPolygonColorCommand::setPolygonColor(QColor color)
{
    Ui::MainWindow* ui = mw->getUI();
    if (color.isValid()) {
        ui->openGLWidget->pol_red = color.redF();
        ui->openGLWidget->pol_green = color.greenF();
        ui->openGLWidget->pol_blue = color.blueF();
        char rgba_color[40];
        sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
                color.green(), color.blue());
        ui->setPolygonColor->setStyleSheet(rgba_color);
        ui->openGLWidget->update();
    }
}
