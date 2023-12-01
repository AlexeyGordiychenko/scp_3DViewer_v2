#include "s21_setpolygoncolorcmd.h"

s21::SetPolygonColorCmd::SetPolygonColorCmd(QColor old_color, QColor color,
                                            Ui::View* ui)
    : ui_(ui), old_color_(old_color), color_(color) {}

void s21::SetPolygonColorCmd::Redo() { SetPolygonColor(color_); }

void s21::SetPolygonColorCmd::Undo() { SetPolygonColor(old_color_); }

void s21::SetPolygonColorCmd::SetPolygonColor(QColor color) {
  if (color.isValid()) {
    ui_->openGLWidget->line_color_ = color;
    ui_->setPolygonColor->setStyleSheet(
        QString("background-color: %1").arg(color.name()));
    ui_->openGLWidget->update();
  }
}
