#include "s21_setverticecolorcmd.h"

s21::SetVerticeColorCmd::SetVerticeColorCmd(QColor old_color, QColor color,
                                            View* mw)
    : view_(mw), old_color_(old_color), color_(color) {}

void s21::SetVerticeColorCmd::Redo() { SetVerticeColor(color_); }

void s21::SetVerticeColorCmd::Undo() { SetVerticeColor(old_color_); }

void s21::SetVerticeColorCmd::SetVerticeColor(QColor color) {
  Ui::View* ui = view_->GetUI();
  if (color.isValid()) {
    ui->openGLWidget->ver_red_ = color.redF();
    ui->openGLWidget->ver_green_ = color.greenF();
    ui->openGLWidget->ver_blue_ = color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
            color.green(), color.blue());
    ui->setVerticeColor->setStyleSheet(rgba_color);
    ui->openGLWidget->update();
  }
}
