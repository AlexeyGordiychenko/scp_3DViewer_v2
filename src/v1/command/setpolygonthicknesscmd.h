#ifndef SETPOLYGONTHICKNESSCMD_H
#define SETPOLYGONTHICKNESSCMD_H

#include "s21_command.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

class SetPolygonThicknessCmd : public s21_Command
{
public:
    SetPolygonThicknessCmd(double old_thickness, double new_thickness, MainWindow* mw);
    void redo() override;
    void undo() override;
private:
    MainWindow* mw;
    void setPolygonThickness(double thickness);
    double old_thickness;
    double new_thickness;
};

}

#endif // SETPOLYGONTHICKNESSCMD_H

//#include "s21_command.h"
//#include <QColor>
//#include "mainwindow.h"
//#include "ui_mainwindow.h"

//class s21_setPolygonColorCommand : public s21_Command
//{
//public:
//    s21_setPolygonColorCommand(QColor old_color, QColor color, MainWindow* mw);

//    // s21_Command interface
//public:
//    void redo() override;
//    void undo() override;
//private:
//    MainWindow* mw;
//    void setPolygonColor(QColor color);
//    QColor old_color;
//    QColor color;
//};

//#endif // S21_SETPOLYGONCOLORCOMMAND_H
