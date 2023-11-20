#include <QUndoCommand>

#include "../mainwindow.h"

class s21_setBackgroundColorCommand : public QUndoCommand
{
public:
    s21_setBackgroundColorCommand(GLWidget* w, QColor old_color,
                                  QColor color, MainWindow* mw, QUndoCommand *parent = 0);
    void undo();
    void redo();
private:
    GLWidget* openGLWidget;
    MainWindow* mw;
    QColor old_color;
    QColor color;
};
