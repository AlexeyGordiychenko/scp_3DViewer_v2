#ifndef S21_COMMANDSTACK_H
#define S21_COMMANDSTACK_H

#include <stack>
#include "s21_command.h"
#include <QObject>

class s21_CommandStack : public QObject
{
    //Q_OBJECT
public:
    s21_CommandStack();
     ~s21_CommandStack();
    void push(Command* cmd);
public slots:
    void redo();
    void undo();

private:
    std::stack<Command*> undo_stack;
    std::stack<Command*> redo_stack;
    void clear_redo();
};

#endif // S21_COMMANDSTACK_H
