#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "command/s21_affine_data.h"

#ifndef S21AFFINE_COMMAND
#define S21AFFINE_COMMAND

class s21_affine_command: public QUndoCommand {
public:
    //s21_affine_command();
    s21_affine_command(s21_affine_data old_data, s21_affine_data new_data, MainWindow* mw, QUndoCommand *parent = 0);
    void undo();
    void redo();
private:
    MainWindow* mw;
    s21_affine_data old_data;
    s21_affine_data new_data;
    void s21_affine(s21_affine_data& data);
};

#endif

//class s21_projectionTypeChangeCommand : public QUndoCommand
//{
//public:
//    s21_projectionTypeChangeCommand(GLWidget* w, int old_idx, int new_idx, MainWindow* mw, QUndoCommand *parent = 0);
//    void undo();
//    void redo();
//private:
//    GLWidget* widget;
//    MainWindow* mw;
//    int old_idx;
//    int new_idx;
//};

