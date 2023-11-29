#ifndef S21_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H
#define S21_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H

#include "../s21_glwidget.h"
#include "../s21_view.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class SetVerticeTypeCmd : public Command {
 public:
  SetVerticeTypeCmd() = delete;
  SetVerticeTypeCmd(VerticeType old_type, VerticeType new_type, View* view);
  SetVerticeTypeCmd(const SetVerticeTypeCmd&) = delete;
  SetVerticeTypeCmd& operator=(const SetVerticeTypeCmd&) = delete;
  SetVerticeTypeCmd(SetVerticeTypeCmd&&) = delete;
  SetVerticeTypeCmd& operator=(SetVerticeTypeCmd&&) = delete;
  ~SetVerticeTypeCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  void SetVerticeType(VerticeType type);
  VerticeType old_type_;
  VerticeType new_type_;
};

}  // namespace s21

#endif
