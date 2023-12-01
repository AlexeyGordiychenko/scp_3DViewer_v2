#include "s21_setverticecolorcmd.h"

s21::SetVerticeColorCmd::SetVerticeColorCmd(QColor old_color, QColor color,
                                            Ui::View* ui)
    : ui_(ui), old_color_(old_color), color_(color) {}

void s21::SetVerticeColorCmd::Redo() { SetVerticeColor(color_); }

void s21::SetVerticeColorCmd::Undo() { SetVerticeColor(old_color_); }

void s21::SetVerticeColorCmd::SetVerticeColor(QColor color) {
  if (color.isValid()) {
    ui_->openGLWidget->vertice_color_ = color;
    ui_->setVerticeColor->setStyleSheet(
        QString("background-color: %1").arg(color.name()));
    ui_->openGLWidget->update();
  }
}
