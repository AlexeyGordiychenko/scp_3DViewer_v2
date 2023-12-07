#ifndef SCP_3DVIEWER_V2_COMMAND_SETLINECOLORCMD_H
#define SCP_3DVIEWER_V2_COMMAND_SETLINECOLORCMD_H

#include <QColor>

#include "scp_command.h"

namespace scp {

class View;

class SetLineColorCmd : public Command {
 public:
  SetLineColorCmd() = delete;
  SetLineColorCmd(QColor old_color, QColor color, View* view);
  SetLineColorCmd(const SetLineColorCmd&) = delete;
  SetLineColorCmd& operator=(const SetLineColorCmd&) = delete;
  SetLineColorCmd(SetLineColorCmd&&) = delete;
  SetLineColorCmd& operator=(SetLineColorCmd&&) = delete;
  ~SetLineColorCmd() = default;
  void Redo() override;
  void Undo() override;

 private:
  View* view_;
  QColor old_color_, color_;
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_SETLINECOLORCMD_H
