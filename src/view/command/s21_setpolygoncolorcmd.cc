#include "s21_setpolygoncolorcmd.h"

s21::SetPolygonColorCmd::SetPolygonColorCmd(QColor old_color, QColor color,
                                            View *mw)
    : view_(mw), old_color_(old_color), color_(color) {}

void s21::SetPolygonColorCmd::Redo() { SetPolygonColor(color_); }

void s21::SetPolygonColorCmd::Undo() { SetPolygonColor(old_color_); }

void s21::SetPolygonColorCmd::SetPolygonColor(QColor color) {
  Ui::View *ui = view_->GetUI();
  if (color.isValid()) {
    ui->openGLWidget->pol_red_ = color.redF();
    ui->openGLWidget->pol_green = color.greenF();
    ui->openGLWidget->pol_blue_ = color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
            color.green(), color.blue());
    ui->setPolygonColor->setStyleSheet(rgba_color);
    ui->openGLWidget->update();
  }
}
