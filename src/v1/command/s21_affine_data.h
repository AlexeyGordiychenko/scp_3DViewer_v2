#include "mainwindow.h"
#include "ui_mainwindow.h"

class s21_affine_data {
public:
    s21_affine_data(Ui::MainWindow* ui);
    double move_x;
    double move_y;
    double move_z;
    double scale_k;
    double rotate_x;
    double rotate_y;
    double rotate_z;
};
