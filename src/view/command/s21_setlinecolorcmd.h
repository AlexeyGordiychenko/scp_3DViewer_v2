#ifndef S21_3DVIEWER_V2_COMMAND_SETLINECOLORCMD_H
#define S21_3DVIEWER_V2_COMMAND_SETLINECOLORCMD_H

#include <QColor>

#include "s21_command.h"

namespace s21 {

class View;

class SetLineColorCmd : public Command {
 public:
  SetLineColorCmd() = delete;
  SetLineColorCmd(QColor old_color, QColor color, View* view);
  SetLineColorCmd(const SetLineColorCmd&) = delete;
  SetLineColorCmd& operator=(const SetLineColorCmd&) = delete;
  SetLineColorCmd(SetLineColorCmd&&) = delete;
  SetLineColorCmd& operator=(SetLineColorCmd&&) = delete;
  ~SetLineColorCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  QColor old_color_, color_;
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_COMMAND_SETLINECOLORCMD_H
