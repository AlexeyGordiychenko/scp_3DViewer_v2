#ifndef SCP_3DVIEWER_V2_COMMAND_SETVERTICESIZECMD_H
#define SCP_3DVIEWER_V2_COMMAND_SETVERTICESIZECMD_H

#include "scp_command.h"

namespace scp {

class View;

class SetVerticeSizeCmd : public Command {
 public:
  SetVerticeSizeCmd() = delete;
  SetVerticeSizeCmd(double old_thickness, double new_thickness, View* view);
  SetVerticeSizeCmd(const SetVerticeSizeCmd&) = delete;
  SetVerticeSizeCmd& operator=(const SetVerticeSizeCmd&) = delete;
  SetVerticeSizeCmd(SetVerticeSizeCmd&&) = delete;
  SetVerticeSizeCmd& operator=(SetVerticeSizeCmd&&) = delete;
  ~SetVerticeSizeCmd() = default;
  void Redo() override;
  void Undo() override;
  static void init_old(double old);
  static double get_old();

 private:
  View* view_;
  double old_thickness_, new_thickness_;
  inline static double prev_old_;
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_SETVERTICESIZECMD_H
