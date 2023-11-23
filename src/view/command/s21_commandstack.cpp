#include "s21_commandstack.h"


s21_CommandStack::s21_CommandStack()
    : undo_stack(std::stack<Command*>()), redo_stack(std::stack<Command*>())
{

}

void s21_CommandStack::redo()
{
    if (!redo_stack.empty()) {
        redo_stack.top()->redo();
        undo_stack.push(redo_stack.top());
        redo_stack.pop();
    }
}

void s21_CommandStack::undo()
{
    if (!undo_stack.empty()) {
        undo_stack.top()->undo();
        redo_stack.push(undo_stack.top());
        undo_stack.pop();
    }
}

s21_CommandStack::~s21_CommandStack()
{

}

void s21_CommandStack::push(Command* cmd)
{
    cmd->redo();
    undo_stack.push(cmd);
    clear_redo();
}

void s21_CommandStack::clear_redo()
{
    while(!redo_stack.empty())
        redo_stack.pop();
}
