#include "scp_commandstack.h"

scp::CommandStack::CommandStack()
    : undo_stack_(std::stack<Command*>()),
      redo_stack_(std::stack<Command*>()) {}

scp::CommandStack::~CommandStack() {
  ClearRedoStack();
  ClearUndoStack();
}

void scp::CommandStack::Redo() {
  if (!redo_stack_.empty()) {
    redo_stack_.top()->Redo();
    undo_stack_.push(redo_stack_.top());
    redo_stack_.pop();
  }
}

void scp::CommandStack::Undo() {
  if (!undo_stack_.empty()) {
    undo_stack_.top()->Undo();
    redo_stack_.push(undo_stack_.top());
    undo_stack_.pop();
  }
}

void scp::CommandStack::Push(Command* cmd) {
  cmd->Redo();
  undo_stack_.push(cmd);
  ClearRedoStack();
}

void scp::CommandStack::PushNoRedo(Command* cmd) {
  undo_stack_.push(cmd);
  ClearRedoStack();
}

void scp::CommandStack::ClearRedoStack() {
  while (!redo_stack_.empty()) {
    delete redo_stack_.top();
    redo_stack_.pop();
  }
}

void scp::CommandStack::ClearUndoStack() {
  while (!undo_stack_.empty()) {
    delete undo_stack_.top();
    undo_stack_.pop();
  }
}
