#include "scp_affinesavecmd.h"

#include "../scp_view.h"

scp::AffineSaveCmd::AffineSaveCmd(AffineData old_data, AffineData new_data,
                                  Ui::View* ui)
    : ui_(ui), new_data_(new_data), old_data_(old_data) {}

void scp::AffineSaveCmd::Undo() { Transform(old_data_); }

void scp::AffineSaveCmd::Redo() { Transform(new_data_); }

scp::AffineData scp::AffineSaveCmd::get_old() { return prev_old; }

void scp::AffineSaveCmd::Transform(AffineData& data) {
  ui_->move_on_x->setValue(data.move_x);
  ui_->move_on_y->setValue(data.move_y);
  ui_->move_on_z->setValue(data.move_z);
  ui_->scale_on_k->setValue(data.scale_k);
  ui_->rotate_x->setValue(data.rotate_x);
  ui_->rotate_y->setValue(data.rotate_y);
  ui_->rotate_z->setValue(data.rotate_z);
  prev_old = data;
}
