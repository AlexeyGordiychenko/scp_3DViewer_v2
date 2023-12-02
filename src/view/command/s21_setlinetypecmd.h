#ifndef S21_3DVIEWER_V2_COMMAND_SETLINETYPECMD_H
#define S21_3DVIEWER_V2_COMMAND_SETLINETYPECMD_H

#include <QColor>

#include "../utils/s21_enums.h"
#include "s21_command.h"

namespace s21 {

class View;

class SetLineTypeCmd : public Command {
 public:
  SetLineTypeCmd() = delete;
  SetLineTypeCmd(LineType old_type, LineType new_type, View* view);
  SetLineTypeCmd(const SetLineTypeCmd&) = delete;
  SetLineTypeCmd& operator=(const SetLineTypeCmd&) = delete;
  SetLineTypeCmd(SetLineTypeCmd&&) = delete;
  SetLineTypeCmd& operator=(SetLineTypeCmd&&) = delete;
  ~SetLineTypeCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  LineType old_type_, new_type_;
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_COMMAND_SETLINETYPECMD_H
