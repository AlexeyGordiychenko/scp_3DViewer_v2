#ifndef S21_3DVIEWER_V2_COMMAND_COMMANDSTACK_H
#define S21_3DVIEWER_V2_COMMAND_COMMANDSTACK_H

#include <QObject>
#include <stack>

#include "s21_command.h"

namespace s21 {

class CommandStack : public QObject {
 public:
  CommandStack();
  CommandStack(const CommandStack&) = delete;
  CommandStack& operator=(const CommandStack&) = delete;
  CommandStack(CommandStack&&) = delete;
  CommandStack& operator=(CommandStack&&) = delete;
  ~CommandStack();
  void Push(Command* cmd);
 public slots:
  void Redo();
  void Undo();

 private:
  std::stack<Command*> undo_stack_;
  std::stack<Command*> redo_stack_;
  void ClearRedoStack();
  void ClearUndoStack();
};

}  // namespace s21

#endif
