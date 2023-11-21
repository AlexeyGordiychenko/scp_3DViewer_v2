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
    void push(s21_Command* cmd);
public slots:
    void redo();
    void undo();

private:
    std::stack<s21_Command*> undo_stack;
    std::stack<s21_Command*> redo_stack;
    void clear_redo();
};

#endif // S21_COMMANDSTACK_H
