#ifndef S21_3DVIEWER_V2_COMMAND_SETPROJECTIONTYPECHANGECMD_H
#define S21_3DVIEWER_V2_COMMAND_SETPROJECTIONTYPECHANGECMD_H

#include "../utils/s21_enums.h"
#include "s21_command.h"

namespace s21 {

class View;

class ProjectionTypeChangeCommand : public Command {
 public:
  ProjectionTypeChangeCommand() = delete;
  ProjectionTypeChangeCommand(ProjectionType old_idx, ProjectionType new_idx,
                              View* view);
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
  View* view_;
  ProjectionType old_idx_, new_idx_;
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_COMMAND_SETPROJECTIONTYPECHANGECMD_H
