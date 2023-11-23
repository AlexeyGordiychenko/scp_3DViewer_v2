#ifndef S21_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H
#define S21_3DVIEWER_V2_COMMAND_SETVERTICECOLORCMD_H

#include "s21_command.h"
#include <QColor>
#include "../s21_view.h"
#include "ui_s21_view.h"

namespace s21 {

class SetVerticeColorCmd : public Command
{
public:
    SetVerticeColorCmd() = delete;
    SetVerticeColorCmd(QColor old_color, QColor color, View* view);
    SetVerticeColorCmd(const SetVerticeColorCmd&) = delete;
    SetVerticeColorCmd& operator=(const SetVerticeColorCmd&) = delete;
    SetVerticeColorCmd(SetVerticeColorCmd&&) = delete;
    SetVerticeColorCmd& operator=(SetVerticeColorCmd&&) = delete;
    ~SetVerticeColorCmd() = default;
    void Redo() override;
    void Undo() override;
private:
    View* view_;
    void SetVerticeColor(QColor color);
    QColor old_color_;
    QColor color_;
};

}

#endif
