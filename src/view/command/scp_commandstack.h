#ifndef SCP_3DVIEWER_V2_COMMAND_COMMANDSTACK_H
#define SCP_3DVIEWER_V2_COMMAND_COMMANDSTACK_H

#include <QObject>
#include <stack>

#include "scp_command.h"

namespace scp {

class CommandStack : public QObject {
 public:
  CommandStack();
  CommandStack(const CommandStack&) = delete;
  CommandStack& operator=(const CommandStack&) = delete;
  CommandStack(CommandStack&&) = delete;
  CommandStack& operator=(CommandStack&&) = delete;
  ~CommandStack();
  void Push(Command* cmd);
  void PushNoRedo(Command* cmd);
 public slots:
  void Redo();
  void Undo();

 private:
  std::stack<Command*> undo_stack_;
  std::stack<Command*> redo_stack_;
  void ClearRedoStack();
  void ClearUndoStack();
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_COMMANDSTACK_H
