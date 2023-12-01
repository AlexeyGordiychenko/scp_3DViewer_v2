#ifndef S21_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H
#define S21_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H

#include <QColor>

#include "../s21_view.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class SetVerticeColorCmd : public Command {
 public:
  SetVerticeColorCmd() = delete;
  SetVerticeColorCmd(QColor old_color, QColor color, Ui::View* ui);
  SetVerticeColorCmd(const SetVerticeColorCmd&) = delete;
  SetVerticeColorCmd& operator=(const SetVerticeColorCmd&) = delete;
  SetVerticeColorCmd(SetVerticeColorCmd&&) = delete;
  SetVerticeColorCmd& operator=(SetVerticeColorCmd&&) = delete;
  ~SetVerticeColorCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  Ui::View* ui_;
  void SetVerticeColor(QColor color);
  QColor old_color_;
  QColor color_;
};

}  // namespace s21

#endif
