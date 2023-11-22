#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <s21_glwidget.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>

#include "s21_gifcreator.h"
#include "command/s21_commandstack.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void refresh_ui();
  Ui::MainWindow* getUI();


 private:
  Ui::MainWindow *ui;
  GifCreator *gifCreator;
  QSettings *settings;

    s21_CommandStack *undoStack;
    QAction *undoAction;
    QAction *redoAction;
    void createCommandStack();
    void setPolygonType(s21_polygonType type);
    void setVerticeType(s21_verticeType type);

 private slots:
  void s21_openFile();
  void s21_renderFile();
  void s21_projectionTypeChange(int idx);
  void s21_takeScreenshot();
  void s21_getGIF();
  void s21_affine();
  void s21_reset();
  void s21_reset_params();
  void s21_setBackgroundColor();
  void s21_setPolygonColor();
  void s21_solidPolygonType();
  void s21_dashedPolygonType();
  void s21_setPolygonThickness(int value);
  void s21_setNoneVertice();
  void s21_setCircleVertice();
  void s21_setSquareVertice();
  void s21_setVerticeSize(int value);
  void s21_setVerticeColor();
  void s21_saveSettings();
  void s21_loadSettings();
  void s21_setValuesOnButtons();
  void s21_polygonThicknessSliderReleased();
  void s21_verticeSizeSliderReleased();
};
#endif  // MAINWINDOW_H
