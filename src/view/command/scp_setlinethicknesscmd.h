#ifndef SCP_3DVIEWER_V2_COMMAND_SETLINETHICKNESSCMD_H
#define SCP_3DVIEWER_V2_COMMAND_SETLINETHICKNESSCMD_H

#include "scp_command.h"

namespace scp {

class View;

class SetLineThicknessCmd : public Command {
 public:
  SetLineThicknessCmd() = delete;
  SetLineThicknessCmd(double old_thickness, double new_thickness, View* view);
  SetLineThicknessCmd(const SetLineThicknessCmd&) = delete;
  SetLineThicknessCmd& operator=(const SetLineThicknessCmd&) = delete;
  SetLineThicknessCmd(SetLineThicknessCmd&&) = delete;
  SetLineThicknessCmd& operator=(SetLineThicknessCmd&&) = delete;
  ~SetLineThicknessCmd() = default;
  void Redo() override;
  void Undo() override;
  void static init_old(double old);
  double static get_old();

 private:
  View* view_;
  double old_thickness_, new_thickness_;
  inline static double prev_old_;
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_SETLINETHICKNESSCMD_H
