#include "s21_affinesave.h"

s21::AffineSaveCmd::AffineSaveCmd(AffineData old_data, AffineData new_data,
                                  View* view)
    : view_(view), new_data_(new_data), old_data_(old_data) {}

s21::AffineSaveCmd::AffineSaveCmd(AffineData new_data, View* view)
    : view_(view), new_data_(new_data) {
  old_data_ = prev_old;
  prev_old = new_data_;
}

void s21::AffineSaveCmd::Undo() {
  Transform(old_data_);
  prev_old = old_data_;
}

void s21::AffineSaveCmd::Redo() {
  Transform(new_data_);
  prev_old = new_data_;
}

s21::AffineData s21::AffineSaveCmd::get_old() { return prev_old; }

void s21::AffineSaveCmd::Transform(AffineData& data) {
  Ui::View* ui = view_->GetUI();
  ui->move_on_x->setValue(data.move_x);
  ui->move_on_y->setValue(data.move_y);
  ui->move_on_z->setValue(data.move_z);
  ui->scale_on_k->setValue(data.scale_k);
  ui->rotate_x->setValue(data.rotate_x);
  ui->rotate_y->setValue(data.rotate_y);
  ui->rotate_z->setValue(data.rotate_z);
}
