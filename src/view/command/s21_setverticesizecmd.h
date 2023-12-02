#ifndef S21_3DVIEWER_V2_COMMAND_SETVERTICESIZECMD_H
#define S21_3DVIEWER_V2_COMMAND_SETVERTICESIZECMD_H

#include "s21_command.h"

namespace s21 {

class View;

class SetVerticeSizeCmd : public Command {
 public:
  SetVerticeSizeCmd() = delete;
  SetVerticeSizeCmd(double old_thickness, double new_thickness, View* view);
  SetVerticeSizeCmd(const SetVerticeSizeCmd&) = delete;
  SetVerticeSizeCmd& operator=(const SetVerticeSizeCmd&) = delete;
  SetVerticeSizeCmd(SetVerticeSizeCmd&&) = delete;
  SetVerticeSizeCmd& operator=(SetVerticeSizeCmd&&) = delete;
  ~SetVerticeSizeCmd() = default;
  void Redo() override;
  void Undo() override;
  static void init_old(double old);
  static double get_old();

 private:
  View* view_;
  double old_thickness_, new_thickness_;
  inline static double prev_old_;
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_COMMAND_SETVERTICESIZECMD_H
