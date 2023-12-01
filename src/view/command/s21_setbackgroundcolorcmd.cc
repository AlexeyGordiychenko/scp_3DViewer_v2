#include "s21_setbackgroundcolorcmd.h"

#include "ui_s21_view.h"

s21::SetBackgroundColorCmd::SetBackgroundColorCmd(QColor old_color,
                                                  QColor color, Ui::View* view)
    : ui_(view), old_color_(old_color), color_(color) {}

void s21::SetBackgroundColorCmd::Undo() { SetBackgroundColor(old_color_); }

void s21::SetBackgroundColorCmd::Redo() { SetBackgroundColor(color_); }

void s21::SetBackgroundColorCmd::SetBackgroundColor(QColor color) {
  if (color.isValid()) {
    ui_->openGLWidget->bg_red_ = color.redF();
    ui_->openGLWidget->bg_green_ = color.greenF();
    ui_->openGLWidget->bg_blue_ = color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
            color.green(), color.blue());
    ui_->setBgColor->setStyleSheet(rgba_color);
    ui_->openGLWidget->update();
  }
}
