#ifndef S21_3DVIEWER_V2_COMMAND_AFFINESAVECOMMAND_H
#define S21_3DVIEWER_V2_COMMAND_AFFINESAVECOMMAND_H

#include "../s21_view.h"
#include "s21_affinedata.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class AffineSave : public Command {
 public:
  AffineSave() = delete;
  AffineSave(AffineData old_data, AffineData new_data, View* view);
  AffineSave(const AffineSave&) = delete;
  AffineSave& operator=(const AffineSave&) = delete;
  AffineSave(AffineSave&&) = delete;
  AffineSave& operator=(AffineSave&&) = delete;
  ~AffineSave() = default;
  void Undo() override;
  void Redo() override;

 private:
  View* view_;
  AffineData old_data_;
  AffineData new_data_;
  void Transform(AffineData& data);
};

}  // namespace s21

#endif
