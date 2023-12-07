#ifndef SCP_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H
#define SCP_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H

#include <QColor>

#include "scp_command.h"

namespace scp {

class View;

class SetVerticeColorCmd : public Command {
 public:
  SetVerticeColorCmd() = delete;
  SetVerticeColorCmd(QColor old_color, QColor color, View* view);
  SetVerticeColorCmd(const SetVerticeColorCmd&) = delete;
  SetVerticeColorCmd& operator=(const SetVerticeColorCmd&) = delete;
  SetVerticeColorCmd(SetVerticeColorCmd&&) = delete;
  SetVerticeColorCmd& operator=(SetVerticeColorCmd&&) = delete;
  ~SetVerticeColorCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  QColor old_color_, color_;
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H
