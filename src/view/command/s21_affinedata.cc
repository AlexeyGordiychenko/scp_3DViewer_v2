#include "s21_affinedata.h"

s21::AffineData::AffineData(Ui::View *ui) {
  move_x = (ui->move_on_x->value());
  move_y = (ui->move_on_y->value());
  move_z = (ui->move_on_z->value());
  scale_k = (ui->scale_on_k->value());
  rotate_x = (ui->rotate_x->value());
  rotate_y = (ui->rotate_y->value());
  rotate_z = (ui->rotate_z->value());
}
