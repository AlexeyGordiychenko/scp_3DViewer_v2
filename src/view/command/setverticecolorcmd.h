#ifndef SETVERTICECOLORCMD_H
#define SETVERTICECOLORCMD_H

#include "s21_command.h"
#include <QColor>
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

class setVerticeColorCmd : public Command
{
public:
    setVerticeColorCmd(QColor old_color, QColor color, MainWindow* mw);
    void Redo() override;
    void Undo() override;
private:
    MainWindow* mw;
    void setVerticeColor(QColor color);
    QColor old_color;
    QColor color;
};

}

#endif // SETVERTICECOLORCMD_H
