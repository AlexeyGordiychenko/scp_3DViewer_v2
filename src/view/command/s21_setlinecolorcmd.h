#ifndef S21_3DVIEWER_V2_COMMAND_SETLINECOLORCMD_H
#define S21_3DVIEWER_V2_COMMAND_SETLINECOLORCMD_H

#include <QColor>

#include "../s21_view.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class SetLineColorCmd : public Command {
 public:
  SetLineColorCmd() = delete;
  SetLineColorCmd(QColor old_color, QColor color, Ui::View* ui);
  SetLineColorCmd(const SetLineColorCmd&) = delete;
  SetLineColorCmd& operator=(const SetLineColorCmd&) = delete;
  SetLineColorCmd(SetLineColorCmd&&) = delete;
  SetLineColorCmd& operator=(SetLineColorCmd&&) = delete;
  ~SetLineColorCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  Ui::View* ui_;
  void SetLineColor(QColor color);
  QColor old_color_;
  QColor color_;
};

}  // namespace s21

#endif
