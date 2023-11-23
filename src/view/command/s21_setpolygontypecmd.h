#ifndef S21_3DVIEWER_V2_COMMAND_SETPOLYGONTYPECOMMAND_H
#define S21_3DVIEWER_V2_COMMAND_SETPOLYGONTYPECOMMAND_H

#include <QColor>
#include "s21_command.h"
#include "../s21_view.h"
#include "ui_s21_view.h"
#include "../s21_glwidget.h"

namespace s21 {

class SetPolygonTypeCmd : public Command
{
public:
    SetPolygonTypeCmd() = delete;
    SetPolygonTypeCmd(polygonType old_type, polygonType new_type, View *mw);
    SetPolygonTypeCmd(const SetPolygonTypeCmd&) = delete;
    SetPolygonTypeCmd& operator=(const SetPolygonTypeCmd&) = delete;
    SetPolygonTypeCmd(SetPolygonTypeCmd&&) = delete;
    SetPolygonTypeCmd& operator=(SetPolygonTypeCmd&&) = delete;
    ~SetPolygonTypeCmd() = default;
    void Redo() override;
    void Undo() override;
private:
    View* view_;
    void SetPolygonType(polygonType type);
    polygonType old_type_;
    polygonType new_type_;
};

}

#endif

