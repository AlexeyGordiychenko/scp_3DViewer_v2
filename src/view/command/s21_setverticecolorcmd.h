#ifndef S21_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H
#define S21_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H

#include <QColor>

#include "s21_command.h"

namespace s21 {

class View;

class SetVerticeColorCmd : public Command {
 public:
  SetVerticeColorCmd() = delete;
  SetVerticeColorCmd(QColor old_color, QColor color, View* view);
  SetVerticeColorCmd(const SetVerticeColorCmd&) = delete;
  SetVerticeColorCmd& operator=(const SetVerticeColorCmd&) = delete;
  SetVerticeColorCmd(SetVerticeColorCmd&&) = delete;
  SetVerticeColorCmd& operator=(SetVerticeColorCmd&&) = delete;
  ~SetVerticeColorCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  QColor old_color_, color_;
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H
