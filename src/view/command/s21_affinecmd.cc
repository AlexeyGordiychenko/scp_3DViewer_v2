#include "s21_affinecmd.h"

#include "../s21_view.h"
#include "ui_s21_view.h"

s21::AffineCmd::AffineCmd(AffineData old_data, AffineData new_data,
                          Ui::View* ui)
    : ui_(ui), old_data_(old_data), new_data_(new_data) {}

void s21::AffineCmd::Undo() { Transform(old_data_); }

void s21::AffineCmd::Redo() { Transform(new_data_); }

void s21::AffineCmd::Transform(AffineData& data) {
  if (data.scale_k == 0) data.scale_k = 1;
  ui_->openGLWidget->ClearTransformations();
  ui_->openGLWidget->RestoreVertices();
  // ui_->openGLWidget->Scale(data.scale_k);
  // ui_->openGLWidget->Move(data.move_x, data.move_y, data.move_z);
  // ui_->openGLWidget->Rotate((data.rotate_x) * M_PI / 180,
  //                          (data.rotate_y) * M_PI / 180,
  //                          (data.rotate_z) * M_PI / 180);
  ui_->openGLWidget->update();

  ui_->move_on_x->setValue(data.move_x);
  ui_->move_on_y->setValue(data.move_y);
  ui_->move_on_z->setValue(data.move_z);
  ui_->scale_on_k->setValue(data.scale_k);
  ui_->rotate_x->setValue(data.rotate_x);
  ui_->rotate_y->setValue(data.rotate_y);
  ui_->rotate_z->setValue(data.rotate_z);
}
