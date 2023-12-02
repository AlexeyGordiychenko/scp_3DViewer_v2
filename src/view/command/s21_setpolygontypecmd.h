#ifndef S21_3DVIEWER_V2_COMMAND_SETPOLYGONTYPECOMMAND_H
#define S21_3DVIEWER_V2_COMMAND_SETPOLYGONTYPECOMMAND_H

#include <QColor>

#include "../s21_glwidget.h"
#include "../s21_view.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class SetLineTypeCmd : public Command {
 public:
  SetLineTypeCmd() = delete;
  SetLineTypeCmd(LineType old_type, LineType new_type, Ui::View* ui);
  SetLineTypeCmd(const SetLineTypeCmd&) = delete;
  SetLineTypeCmd& operator=(const SetLineTypeCmd&) = delete;
  SetLineTypeCmd(SetLineTypeCmd&&) = delete;
  SetLineTypeCmd& operator=(SetLineTypeCmd&&) = delete;
  ~SetLineTypeCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  Ui::View* ui_;
  void SetLineType(LineType type);
  LineType old_type_;
  LineType new_type_;
};

}  // namespace s21

#endif
