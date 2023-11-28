#include "s21_affinesave.h"

s21::AffineSave::AffineSave(AffineData old_data, AffineData new_data,
                            View* view)
    : view_(view), old_data_(old_data), new_data_(new_data) {}

void s21::AffineSave::Undo() { Transform(old_data_); }

void s21::AffineSave::Redo() { Transform(new_data_); }

void s21::AffineSave::Transform(AffineData& data) {
  Ui::View* ui = view_->GetUI();
  ui->move_on_x->setValue(data.move_x);
  ui->move_on_y->setValue(data.move_y);
  ui->move_on_z->setValue(data.move_z);
  ui->scale_on_k->setValue(data.scale_k);
  ui->rotate_x->setValue(data.rotate_x);
  ui->rotate_y->setValue(data.rotate_y);
  ui->rotate_z->setValue(data.rotate_z);
}
