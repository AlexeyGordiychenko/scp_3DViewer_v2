#ifndef S21_3DVIEWER_V2_COMMAND_SETBACKGROUNDCOLORCMD_H
#define S21_3DVIEWER_V2_COMMAND_SETBACKGROUNDCOLORCMD_H

#include <QColor>

#include "s21_command.h"

namespace s21 {

class View;

class SetBackgroundColorCmd : public Command {
 public:
  SetBackgroundColorCmd() = delete;
  SetBackgroundColorCmd(QColor old_color, QColor color, View* view);
  SetBackgroundColorCmd(const SetBackgroundColorCmd&) = delete;
  SetBackgroundColorCmd& operator=(const SetBackgroundColorCmd&) = delete;
  SetBackgroundColorCmd(SetBackgroundColorCmd&&) = delete;
  SetBackgroundColorCmd& operator=(SetBackgroundColorCmd&&) = delete;
  ~SetBackgroundColorCmd() = default;
  void Undo();
  void Redo();

 private:
  View* view_;
  QColor old_color_, color_;
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_COMMAND_SETBACKGROUNDCOLORCMD_H