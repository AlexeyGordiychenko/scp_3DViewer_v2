#include <QUndoCommand>

#include "../mainwindow.h"

class s21_projectionTypeChangeCommand : public QUndoCommand
{
public:
    s21_projectionTypeChangeCommand(GLWidget* w, int old_idx, int new_idx, MainWindow* mw, QUndoCommand *parent = 0);
    void undo();
    void redo();
private:
    GLWidget* widget;
    MainWindow* mw;
    int old_idx;
    int new_idx;
};
