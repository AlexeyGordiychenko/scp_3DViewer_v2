#ifndef SETPOLYGONTHICKNESSCMD_H
#define SETPOLYGONTHICKNESSCMD_H

#include "s21_command.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

class SetPolygonThicknessCmd : public Command
{
public:
    SetPolygonThicknessCmd(double old_thickness, double new_thickness, MainWindow* mw);
    void Redo() override;
    void Undo() override;
private:
    MainWindow* mw;
    void setPolygonThickness(double thickness);
    double old_thickness;
    double new_thickness;
};

}

#endif // SETPOLYGONTHICKNESSCMD_H
