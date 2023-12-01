#include <QUndoCommand>

#include "../s21_view.h"
#include "s21_command.h"
#include "ui_s21_view.h"

namespace s21 {

class ProjectionTypeChangeCommand : public Command {
 public:
  ProjectionTypeChangeCommand() = delete;
  ProjectionTypeChangeCommand(int old_idx, int new_idx, Ui::View* ui);
  ProjectionTypeChangeCommand(const ProjectionTypeChangeCommand&) = delete;
  ProjectionTypeChangeCommand& operator=(const ProjectionTypeChangeCommand&) =
      delete;
  ProjectionTypeChangeCommand(ProjectionTypeChangeCommand&&) = delete;
  ProjectionTypeChangeCommand& operator=(ProjectionTypeChangeCommand&&) =
      delete;
  ~ProjectionTypeChangeCommand() = default;
  void Undo() override;
  void Redo() override;

 private:
  Ui::View* ui_;
  int old_idx_;
  int new_idx_;
  void SetProjectionType(int idx);
};

}  // namespace s21
