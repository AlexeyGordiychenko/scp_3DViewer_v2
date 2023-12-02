#include "s21_setlinecolorcmd.h"

s21::SetLineColorCmd::SetLineColorCmd(QColor old_color, QColor color,
                                      Ui::View* ui)
    : ui_(ui), old_color_(old_color), color_(color) {}

void s21::SetLineColorCmd::Redo() { SetLineColor(color_); }

void s21::SetLineColorCmd::Undo() { SetLineColor(old_color_); }

void s21::SetLineColorCmd::SetLineColor(QColor color) {
  if (color.isValid()) {
    ui_->openGLWidget->line_color_ = color;
    ui_->lineColor->setStyleSheet(
        QString("background-color: %1").arg(color.name()));
    ui_->openGLWidget->update();
  }
}
