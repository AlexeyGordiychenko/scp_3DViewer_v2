#include "s21_projectionTypeChangeCommand.h"
#include "s21_glwidget.h"

//s21_projectionTypeChangeCommand::s21_projectionTypeChangeCommand
//    (GLWidget *w, int old_idx, int new_idx, MainWindow *mw, QUndoCommand *parent)
//    :   QUndoCommand(parent), widget(w), mw(mw), old_idx(old_idx), new_idx(new_idx)
//{

s21_projectionTypeChangeCommand::s21_projectionTypeChangeCommand(GLWidget *w, int old_idx, int new_idx, MainWindow *mw)
:   widget(w), mw(mw), old_idx(old_idx), new_idx(new_idx)
{

}

void s21_projectionTypeChangeCommand::undo()
{
    widget->setProjectionType(old_idx);
    widget->update();
    mw->refresh_ui();
}

void s21_projectionTypeChangeCommand::redo()
{
    widget->setProjectionType(new_idx);
    widget->update();
    mw->refresh_ui();
}
