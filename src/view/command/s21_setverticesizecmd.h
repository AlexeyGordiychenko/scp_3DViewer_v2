#ifndef S21_3DVIEWER_V2_COMMAND_SETVERTICESIZECMD_H
#define S21_3DVIEWER_V2_COMMAND_SETVERTICESIZECMD_H

#include "../s21_view.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class SetVerticeSizeCmd : public Command {
 public:
  SetVerticeSizeCmd() = delete;
  SetVerticeSizeCmd(double old_thickness, double new_thickness, View* mw);
  SetVerticeSizeCmd(const SetVerticeSizeCmd&) = delete;
  SetVerticeSizeCmd& operator=(const SetVerticeSizeCmd&) = delete;
  SetVerticeSizeCmd(SetVerticeSizeCmd&&) = delete;
  SetVerticeSizeCmd& operator=(SetVerticeSizeCmd&&) = delete;
  ~SetVerticeSizeCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  void SetVerticeSize(double thickness);
  double old_thickness_;
  double new_thickness_;
};

}  // namespace s21

#endif
