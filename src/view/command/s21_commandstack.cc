#include "s21_commandstack.h"

s21::CommandStack::CommandStack()
    : undo_stack_(std::stack<Command *>()),
      redo_stack_(std::stack<Command *>()) {}

s21::CommandStack::~CommandStack() {
  ClearRedoStack();
  ClearUndoStack();
}

void s21::CommandStack::Redo() {
  if (!redo_stack_.empty()) {
    redo_stack_.top()->Redo();
    undo_stack_.push(redo_stack_.top());
    redo_stack_.pop();
  }
}

void s21::CommandStack::Undo() {
  if (!undo_stack_.empty()) {
    undo_stack_.top()->Undo();
    redo_stack_.push(undo_stack_.top());
    undo_stack_.pop();
  }
}

void s21::CommandStack::Push(Command *cmd) {
  cmd->Redo();
  undo_stack_.push(cmd);
  ClearRedoStack();
}

void s21::CommandStack::ClearRedoStack() {
  while (!redo_stack_.empty()) {
    delete redo_stack_.top();
    redo_stack_.pop();
  }
}

void s21::CommandStack::ClearUndoStack() {
  while (!undo_stack_.empty()) {
    delete undo_stack_.top();
    undo_stack_.pop();
  }
}
