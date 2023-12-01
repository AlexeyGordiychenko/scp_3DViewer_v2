#include <QUndoCommand>

#include "../s21_view.h"
#include "s21_command.h"

namespace s21 {

class SetBackgroundColorCmd : public Command {
 public:
  SetBackgroundColorCmd() = delete;
  SetBackgroundColorCmd(QColor old_color, QColor color, Ui::View* view);
  SetBackgroundColorCmd(const SetBackgroundColorCmd&) = delete;
  SetBackgroundColorCmd& operator=(const SetBackgroundColorCmd&) = delete;
  SetBackgroundColorCmd(SetBackgroundColorCmd&&) = delete;
  SetBackgroundColorCmd& operator=(SetBackgroundColorCmd&&) = delete;
  ~SetBackgroundColorCmd() = default;
  void Undo();
  void Redo();

 private:
  Ui::View* ui_;
  QColor old_color_;
  QColor color_;
  void SetBackgroundColor(QColor color);
};

}  // namespace s21
