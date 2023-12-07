#ifndef SCP_3DVIEWER_V2_COMMAND_SETLINETYPECMD_H
#define SCP_3DVIEWER_V2_COMMAND_SETLINETYPECMD_H

#include "../utils/scp_enums.h"
#include "scp_command.h"

namespace scp {

class View;

class SetLineTypeCmd : public Command {
 public:
  SetLineTypeCmd() = delete;
  SetLineTypeCmd(LineType old_type, LineType new_type, View* view);
  SetLineTypeCmd(const SetLineTypeCmd&) = delete;
  SetLineTypeCmd& operator=(const SetLineTypeCmd&) = delete;
  SetLineTypeCmd(SetLineTypeCmd&&) = delete;
  SetLineTypeCmd& operator=(SetLineTypeCmd&&) = delete;
  ~SetLineTypeCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  LineType old_type_, new_type_;
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_SETLINETYPECMD_H
