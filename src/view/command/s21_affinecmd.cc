#include "s21_affinecmd.h"
#include "../s21_view.h"
#include "ui_s21_view.h"

s21::AffineCmd::AffineCmd(AffineData old_data, AffineData new_data, View *view)
    : view_(view), old_data_(old_data), new_data_(new_data) {}

s21::AffineCmd::~AffineCmd() {}

void s21::AffineCmd::Undo() { Transform(old_data_); }

void s21::AffineCmd::Redo() { Transform(new_data_); }

void s21::AffineCmd::Transform(AffineData &data) {
  Ui::View *ui = view_->GetUI();
  if (data.scale_k == 0)
    data.scale_k = 1;
  ui->openGLWidget->ClearTransformations();
  ui->openGLWidget->RestoreVertices();
  ui->openGLWidget->Scale(data.scale_k);
  ui->openGLWidget->Move(data.move_x, data.move_y, data.move_z);
  ui->openGLWidget->Rotate((data.rotate_x) * M_PI / 180,
                           (data.rotate_y) * M_PI / 180,
                           (data.rotate_z) * M_PI / 180);
  ui->openGLWidget->update();

  ui->move_on_x->setValue(data.move_x);
  ui->move_on_y->setValue(data.move_y);
  ui->move_on_z->setValue(data.move_z);
  ui->scale_on_k->setValue(data.scale_k);
  ui->rotate_x->setValue(data.rotate_x);
  ui->rotate_y->setValue(data.rotate_y);
  ui->rotate_z->setValue(data.rotate_z);
}
