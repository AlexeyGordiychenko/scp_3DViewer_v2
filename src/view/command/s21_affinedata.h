#ifndef S21_3DVIEWER_V2_COMMAND_AFFINE_DATA_H
#define S21_3DVIEWER_V2_COMMAND_AFFINE_DATA_H

#include "ui_s21_view.h"
#include "../s21_view.h"

namespace s21 {

class AffineData {
public:
    AffineData() = default;
    AffineData(Ui::View *ui);
    AffineData(const AffineData&) = default;
    AffineData& operator=(const AffineData&) = delete;
    AffineData(AffineData&&) = delete;
    AffineData& operator=(AffineData&&) = delete;
    ~AffineData() = default;
    double move_x;
    double move_y;
    double move_z;
    double scale_k;
    double rotate_x;
    double rotate_y;
    double rotate_z;
};

}

#endif
