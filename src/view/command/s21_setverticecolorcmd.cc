#include "s21_setverticecolorcmd.h"

s21::SetVerticeColorCmd::SetVerticeColorCmd(QColor old_color, QColor color,
                                            Ui::View* ui)
    : ui_(ui), old_color_(old_color), color_(color) {}

void s21::SetVerticeColorCmd::Redo() { SetVerticeColor(color_); }

void s21::SetVerticeColorCmd::Undo() { SetVerticeColor(old_color_); }

void s21::SetVerticeColorCmd::SetVerticeColor(QColor color) {
  if (color.isValid()) {
    ui_->openGLWidget->ver_red_ = color.redF();
    ui_->openGLWidget->ver_green_ = color.greenF();
    ui_->openGLWidget->ver_blue_ = color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
            color.green(), color.blue());
    ui_->setVerticeColor->setStyleSheet(rgba_color);
    ui_->openGLWidget->update();
  }
}
