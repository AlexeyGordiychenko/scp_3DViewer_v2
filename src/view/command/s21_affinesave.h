#ifndef S21_3DVIEWER_V2_COMMAND_AFFINESAVECOMMAND_H
#define S21_3DVIEWER_V2_COMMAND_AFFINESAVECOMMAND_H

#include "../s21_view.h"
#include "s21_affinedata.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class AffineSaveCmd : public Command {
 public:
  AffineSaveCmd() = delete;
  AffineSaveCmd(AffineData old_data, AffineData new_data, View* view);
  AffineSaveCmd(AffineData new_data, View* view);
  AffineSaveCmd(const AffineSaveCmd&) = delete;
  AffineSaveCmd& operator=(const AffineSaveCmd&) = delete;
  AffineSaveCmd(AffineSaveCmd&&) = delete;
  AffineSaveCmd& operator=(AffineSaveCmd&&) = delete;
  ~AffineSaveCmd() = default;
  void Undo() override;
  void Redo() override;
  static void init_old(AffineData old_data);
  static AffineData get_old();

 private:
  View* view_;
  inline static AffineData prev_old = AffineData();
  AffineData new_data_;
  AffineData old_data_;
  void Transform(AffineData& data);
};

}  // namespace s21

#endif
