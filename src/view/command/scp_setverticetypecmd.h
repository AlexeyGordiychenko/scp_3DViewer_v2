#ifndef SCP_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H
#define SCP_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H

#include "../utils/scp_enums.h"
#include "scp_command.h"

namespace scp {

class View;

class SetVerticeTypeCmd : public Command {
 public:
  SetVerticeTypeCmd() = delete;
  SetVerticeTypeCmd(VerticeType old_type, VerticeType new_type, View* view);
  SetVerticeTypeCmd(const SetVerticeTypeCmd&) = delete;
  SetVerticeTypeCmd& operator=(const SetVerticeTypeCmd&) = delete;
  SetVerticeTypeCmd(SetVerticeTypeCmd&&) = delete;
  SetVerticeTypeCmd& operator=(SetVerticeTypeCmd&&) = delete;
  ~SetVerticeTypeCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  VerticeType old_type_, new_type_;
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H
