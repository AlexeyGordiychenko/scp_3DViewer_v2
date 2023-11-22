#include "setverticecolorcmd.h"

s21::setVerticeColorCmd::setVerticeColorCmd(QColor old_color, QColor color, MainWindow *mw)
    :   mw(mw), old_color(old_color), color(color)
{

}

void s21::setVerticeColorCmd::redo()
{
    setVerticeColor(color);
}

void s21::setVerticeColorCmd::undo()
{
    setVerticeColor(old_color);
}

void s21::setVerticeColorCmd::setVerticeColor(QColor color)
{
    Ui::MainWindow* ui = mw->getUI();
    if (color.isValid()) {
      ui->openGLWidget->ver_red = color.redF();
      ui->openGLWidget->ver_green = color.greenF();
      ui->openGLWidget->ver_blue = color.blueF();
      char rgba_color[40];
      sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
              color.green(), color.blue());
      ui->setVerticeColor->setStyleSheet(rgba_color);
      ui->openGLWidget->update();
    }
}
