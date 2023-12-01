#ifndef S21_3DVIEWER_V2_COMMAND_SETPOLYGONTYPECOMMAND_H
#define S21_3DVIEWER_V2_COMMAND_SETPOLYGONTYPECOMMAND_H

#include <QColor>

#include "../s21_glwidget.h"
#include "../s21_view.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class SetPolygonTypeCmd : public Command {
 public:
  SetPolygonTypeCmd() = delete;
  SetPolygonTypeCmd(PolygonType old_type, PolygonType new_type, Ui::View* ui);
  SetPolygonTypeCmd(const SetPolygonTypeCmd&) = delete;
  SetPolygonTypeCmd& operator=(const SetPolygonTypeCmd&) = delete;
  SetPolygonTypeCmd(SetPolygonTypeCmd&&) = delete;
  SetPolygonTypeCmd& operator=(SetPolygonTypeCmd&&) = delete;
  ~SetPolygonTypeCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  Ui::View* ui_;
  void SetPolygonType(PolygonType type);
  PolygonType old_type_;
  PolygonType new_type_;
};

}  // namespace s21

#endif
