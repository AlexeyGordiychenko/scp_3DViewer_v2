#include "command/s21_affineCommand.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

s21_affine_command::s21_affine_command(s21_affine_data old_data, s21_affine_data new_data, MainWindow *mw, QUndoCommand *parent)
    :    QUndoCommand(parent), mw(mw), old_data(old_data), new_data(new_data)
{}

void s21_affine_command::undo()
{
    s21_affine(old_data);
}

void s21_affine_command::redo()
{
    s21_affine(new_data);
}

void s21_affine_command::s21_affine(s21_affine_data& data)
{
    Ui::MainWindow* ui = mw->getUI();
    if (ui->openGLWidget->isParsed && !ui->openGLWidget->fileChanged) {
        if (data.scale_k == 0) data.scale_k = 1;
        ui->openGLWidget->clearTransformations();
        ui->openGLWidget->matrix_reset_to_start();
        ui->openGLWidget->scale(data.scale_k);
        ui->openGLWidget->move(data.move_x, data.move_y, data.move_z);
        ui->openGLWidget->rotate((data.rotate_x)*M_PI / 180, (data.rotate_y)*M_PI / 180,
                                 (data.rotate_z)*M_PI / 180);
        ui->openGLWidget->update();
        //mw->refresh_ui();

        ui->move_on_x->setValue(data.move_x);
        ui->move_on_y->setValue(data.move_y);
        ui->move_on_z->setValue(data.move_z);
        ui->scale_on_k->setValue(data.scale_k);
        ui->rotate_x->setValue(data.rotate_x);
        ui->rotate_y->setValue(data.rotate_y);
        ui->rotate_z->setValue(data.rotate_z);
    }
}
