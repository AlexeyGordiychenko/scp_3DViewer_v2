#ifndef S21_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H
#define S21_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H

#include "s21_command.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

class SetVerticeTypeCmd : public Command
{
public:
    SetVerticeTypeCmd(s21_verticeType old_type, s21_verticeType new_type, MainWindow *mw);
    void Redo() override;
    void Undo() override;
private:
    MainWindow* mw;
    void setVerticeType(s21_verticeType type);
    s21_verticeType old_type;
    s21_verticeType new_type;
};

}

#endif // SETVERTICETYPECMD_H
