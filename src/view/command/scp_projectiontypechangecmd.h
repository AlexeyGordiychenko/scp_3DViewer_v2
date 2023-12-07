#ifndef SCP_3DVIEWER_V2_COMMAND_SETPROJECTIONTYPECHANGECMD_H
#define SCP_3DVIEWER_V2_COMMAND_SETPROJECTIONTYPECHANGECMD_H

#include "../utils/scp_enums.h"
#include "scp_command.h"

namespace scp {

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

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_SETPROJECTIONTYPECHANGECMD_H
