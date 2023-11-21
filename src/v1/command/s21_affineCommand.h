#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "command/s21_affine_data.h"

#ifndef S21AFFINE_COMMAND
#define S21AFFINE_COMMAND

class s21_affine_command: public s21_Command {
public:
    //s21_affine_command();
    s21_affine_command(s21_affine_data old_data, s21_affine_data new_data, MainWindow* mw);
    void undo();
    void redo();
private:
    MainWindow* mw;
    s21_affine_data old_data;
    s21_affine_data new_data;
    void s21_affine(s21_affine_data& data);
};

#endif
