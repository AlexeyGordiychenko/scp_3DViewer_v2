#ifndef S21_3DVIEWER_V2_COMMAND_AFFINECOMMAND_H
#define S21_3DVIEWER_V2_COMMAND_AFFINECOMMAND_H

#include "../s21_view.h"
#include "s21_affinedata.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class AffineCmd : public Command {
public:
  AffineCmd() = delete;
  AffineCmd(AffineData old_data, AffineData new_data, View *view);
  AffineCmd(const AffineCmd &) = delete;
  AffineCmd &operator=(const AffineCmd &) = delete;
  AffineCmd(AffineCmd &&) = delete;
  AffineCmd &operator=(AffineCmd &&) = delete;
  ~AffineCmd();
  void Undo() override;
  void Redo() override;

private:
  View *view_;
  AffineData old_data_;
  AffineData new_data_;
  void Transform(AffineData &data);
};

} // namespace s21

#endif
