#ifndef S21_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H
#define S21_3DVIEWER_V2_COMMAND_SETVERTICETYPECMD_H

#include "s21_command.h"
#include "../s21_view.h"
#include "ui_s21_view.h"
#include "../s21_glwidget.h"

namespace s21 {

class SetVerticeTypeCmd : public Command
{
public:
    SetVerticeTypeCmd() = delete;
    SetVerticeTypeCmd(verticeType old_type, verticeType new_type, View *view);
    SetVerticeTypeCmd(const SetVerticeTypeCmd&) = delete;
    SetVerticeTypeCmd& operator=(const SetVerticeTypeCmd&) = delete;
    SetVerticeTypeCmd(SetVerticeTypeCmd&&) = delete;
    SetVerticeTypeCmd& operator=(SetVerticeTypeCmd&&) = delete;
    ~SetVerticeTypeCmd() = default;
    void Redo() override;
    void Undo() override;
private:
    View* view_;
    void SetVerticeType(verticeType type);
    verticeType old_type_;
    verticeType new_type_;
};

}

#endif
