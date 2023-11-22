#ifndef SETVERTICESIZECMD_H
#define SETVERTICESIZECMD_H

#include "s21_command.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

class SetVerticeSizeCmd : public s21_Command
{
public:
    SetVerticeSizeCmd(double old_thickness, double new_thickness, MainWindow* mw);
    void redo() override;
    void undo() override;
private:
    MainWindow* mw;
    void setVerticeSize(double thickness);
    double old_thickness;
    double new_thickness;
};

}

#endif // SETVERTICESIZECMD_H
