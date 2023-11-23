#ifndef S21_SETPOLYGONCOLORCOMMAND_H
#define S21_SETPOLYGONCOLORCOMMAND_H

#include "s21_command.h"
#include <QColor>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class s21_setPolygonColorCommand : public Command
{
public:
    s21_setPolygonColorCommand(QColor old_color, QColor color, MainWindow* mw);

    // s21_Command interface
public:
    void redo() override;
    void undo() override;
private:
    MainWindow* mw;
    void setPolygonColor(QColor color);
    QColor old_color;
    QColor color;
};

#endif // S21_SETPOLYGONCOLORCOMMAND_H
