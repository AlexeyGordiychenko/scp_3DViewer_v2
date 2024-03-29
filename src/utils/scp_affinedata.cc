#include "scp_affinedata.h"

#include "ui_scp_view.h"

scp::AffineData::AffineData() {
  scale_k = 1;
  move_x = 0;
  move_y = 0;
  move_z = 0;
  rotate_x = 0;
  rotate_y = 0;
  rotate_z = 0;
}

scp::AffineData::AffineData(Ui::View* ui) {
  move_x = (ui->move_on_x->value());
  move_y = (ui->move_on_y->value());
  move_z = (ui->move_on_z->value());
  scale_k = (ui->scale_on_k->value());
  rotate_x = (ui->rotate_x->value());
  rotate_y = (ui->rotate_y->value());
  rotate_z = (ui->rotate_z->value());
}

bool scp::AffineData::operator!=(AffineData& other) {
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
