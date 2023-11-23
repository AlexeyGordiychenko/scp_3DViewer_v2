#ifndef S21_3DVIEWER_V2_COMMAND_SETPOLYGONCOLORCOMMAND_H
#define S21_3DVIEWER_V2_COMMAND_SETPOLYGONCOLORCOMMAND_H

#include "s21_command.h"
#include <QColor>
#include "../s21_view.h"
#include "ui_s21_view.h"

namespace s21 {

class SetPolygonColorCmd : public Command
{
public:
    SetPolygonColorCmd() = delete;
    SetPolygonColorCmd(QColor old_color, QColor color, View* mw);
    SetPolygonColorCmd(const SetPolygonColorCmd&) = delete;
    SetPolygonColorCmd& operator=(const SetPolygonColorCmd&) = delete;
    SetPolygonColorCmd(SetPolygonColorCmd&&) = delete;
    SetPolygonColorCmd& operator=(SetPolygonColorCmd&&) = delete;
    ~SetPolygonColorCmd() = default;
    void Redo() override;
    void Undo() override;
private:
    View* view_;
    void SetPolygonColor(QColor color);
    QColor old_color_;
    QColor color_;
};

}

#endif
