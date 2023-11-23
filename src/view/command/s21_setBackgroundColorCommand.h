#include <QUndoCommand>

#include "../mainwindow.h"

class s21_setBackgroundColorCommand : public s21_Command
{
public:
    s21_setBackgroundColorCommand(GLWidget* w, QColor old_color,
                                  QColor color, MainWindow* mw);
    void undo();
    void redo();
private:
    GLWidget* openGLWidget;
    MainWindow* mw;
    QColor old_color;
    QColor color;
};
