#include <QUndoCommand>

#include "../mainwindow.h"
#include "s21_command.h"

class s21_projectionTypeChangeCommand : public Command
{
public:
    //s21_projectionTypeChangeCommand(GLWidget* w, int old_idx, int new_idx, MainWindow* mw, QUndoCommand *parent = 0);
    s21_projectionTypeChangeCommand(GLWidget* w, int old_idx, int new_idx, MainWindow* mw);
    void undo() override;
    void redo() override;
private:
    GLWidget* widget;
    MainWindow* mw;
    int old_idx;
    int new_idx;
};
