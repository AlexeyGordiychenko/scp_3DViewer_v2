#include "s21_affinedata.h"

s21::AffineData::AffineData() { scale_k = 1; }

s21::AffineData::AffineData(Ui::View* ui) {
  move_x = (ui->move_on_x->value());
  move_y = (ui->move_on_y->value());
  move_z = (ui->move_on_z->value());
  scale_k = (ui->scale_on_k->value());
  rotate_x = (ui->rotate_x->value());
  rotate_y = (ui->rotate_y->value());
  rotate_z = (ui->rotate_z->value());
}

bool s21::AffineData::operator!=(AffineData& other) {
  bool is_equals = true;
  if (this->move_x != other.move_x)
    is_equals = false;
  else if (this->move_y != other.move_y)
    is_equals = false;
  else if (this->move_z != other.move_z)
    is_equals = false;
  else if (this->scale_k != other.scale_k)
    is_equals = false;
  else if (this->rotate_x != other.rotate_x)
    is_equals = false;
  else if (this->rotate_y != other.rotate_y)
    is_equals = false;
  else if (this->rotate_z != other.rotate_z)
    is_equals = false;
  return !is_equals;
}
