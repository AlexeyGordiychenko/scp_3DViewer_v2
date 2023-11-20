#include "s21_setBackgroundColorCommand.h"
#include "s21_glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


//s21_projectionTypeChangeCommand::s21_projectionTypeChangeCommand
//    (GLWidget *w, int old_idx, int new_idx, MainWindow *mw, QUndoCommand *parent)
//    :   QUndoCommand(parent), widget(w), mw(mw), old_idx(old_idx), new_idx(new_idx)
//{

//}

//void s21_projectionTypeChangeCommand::undo()
//{
//    widget->setProjectionType(old_idx);
//    widget->update();
//    mw->refresh_ui();
//}

//void s21_projectionTypeChangeCommand::redo()
//{
//    widget->setProjectionType(new_idx);
//    widget->update();
//    mw->refresh_ui();
//}

s21_setBackgroundColorCommand::s21_setBackgroundColorCommand(GLWidget *w, QColor old_color, QColor color, MainWindow *mw, QUndoCommand *parent)
    :   QUndoCommand(parent), openGLWidget(w), mw(mw), old_color(old_color), color(color)
{

}

void s21_setBackgroundColorCommand::undo()
{
    QColor color = old_color;
    if (color.isValid()) {
      openGLWidget->bg_red = color.redF();
      openGLWidget->bg_green = color.greenF();
      openGLWidget->bg_blue = color.blueF();
      char rgba_color[40];
      sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
              color.green(), color.blue());
      mw->refresh_ui();
      openGLWidget->update();
    }

}

void s21_setBackgroundColorCommand::redo()
{
    if (color.isValid()) {
      openGLWidget->bg_red = color.redF();
      openGLWidget->bg_green = color.greenF();
      openGLWidget->bg_blue = color.blueF();
      char rgba_color[40];
      sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
              color.green(), color.blue());
      mw->getUI()->setBgColor->setStyleSheet(rgba_color);
      openGLWidget->update();
    }
}


//void MainWindow::s21_setBackgroundColor() {
//  QColor color = QColorDialog::getColor();
//  if (color.isValid()) {
//    ui->openGLWidget->bg_red = color.redF();
//    ui->openGLWidget->bg_green = color.greenF();
//    ui->openGLWidget->bg_blue = color.blueF();
//    char rgba_color[40];
//    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
//            color.green(), color.blue());
//    ui->setBgColor->setStyleSheet(rgba_color);
//    ui->openGLWidget->update();
//  }
//}
