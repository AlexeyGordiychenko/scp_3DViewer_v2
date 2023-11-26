#ifndef S21_SETPOLYGONTHICKNESSCMD_H
#define S21_SETPOLYGONTHICKNESSCMD_H

#include "s21_command.h"
#include "../s21_view.h"
#include "ui_s21_view.h"

namespace s21 {

class SetPolygonThicknessCmd : public Command
{
public:
    SetPolygonThicknessCmd() = delete;
    SetPolygonThicknessCmd(double old_thickness, double new_thickness, View *view);
    SetPolygonThicknessCmd(const SetPolygonThicknessCmd&) = delete;
    SetPolygonThicknessCmd& operator=(const SetPolygonThicknessCmd&) = delete;
    SetPolygonThicknessCmd(SetPolygonThicknessCmd&&) = delete;
    SetPolygonThicknessCmd& operator=(SetPolygonThicknessCmd&&) = delete;
    ~SetPolygonThicknessCmd();
    void Redo() override;
    void Undo() override;
private:
    View* view_;
    void SetPolygonThickness(double thickness);
    double old_thickness_;
    double new_thickness_;
};

}

#endif
