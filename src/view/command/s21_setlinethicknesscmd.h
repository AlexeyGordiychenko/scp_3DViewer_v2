#ifndef S21_3DVIEWER_V2_COMMAND_SETLINETHICKNESSCMD_H
#define S21_3DVIEWER_V2_COMMAND_SETLINETHICKNESSCMD_H

#include "../s21_view.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class SetLineThicknessCmd : public Command {
 public:
  SetLineThicknessCmd() = delete;
  SetLineThicknessCmd(double old_thickness, double new_thickness, Ui::View* ui);
  SetLineThicknessCmd(const SetLineThicknessCmd&) = delete;
  SetLineThicknessCmd& operator=(const SetLineThicknessCmd&) = delete;
  SetLineThicknessCmd(SetLineThicknessCmd&&) = delete;
  SetLineThicknessCmd& operator=(SetLineThicknessCmd&&) = delete;
  ~SetLineThicknessCmd() = default;
  void Redo() override;
  void Undo() override;
  void static init_old(double old);
  double static get_old();

 private:
  Ui::View* ui_;
  void SetLineThickness(double thickness);
  double old_thickness_;
  double new_thickness_;
  inline static double prev_old_;
};

}  // namespace s21

#endif
