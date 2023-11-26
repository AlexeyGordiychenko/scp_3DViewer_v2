#include "s21_setbackgroundcolorcmd.h"
#include "ui_s21_view.h"

s21::SetBackgroundColorCmd::SetBackgroundColorCmd(QColor old_color, QColor color, View *view)
    :    view_(view), old_color_(old_color), color_(color)
{

}

void s21::SetBackgroundColorCmd::Undo()
{
    SetBackgroundColor(old_color_);
}

void s21::SetBackgroundColorCmd::Redo()
{
    SetBackgroundColor(color_);
}

void s21::SetBackgroundColorCmd::SetBackgroundColor(QColor color)
{
      if (color.isValid()) {
        Ui::View* ui = view_->GetUI();
        ui->openGLWidget->bg_red_ = color.redF();
        ui->openGLWidget->bg_green_ = color.greenF();
        ui->openGLWidget->bg_blue_ = color.blueF();
        char rgba_color[40];
        sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
                color.green(), color.blue());
        ui->setBgColor->setStyleSheet(rgba_color);
        ui->openGLWidget->update();
      }
}
