#ifndef S21_3DVIEWER_V2_AFFINE_DATA_H
#define S21_3DVIEWER_V2_AFFINE_DATA_H

namespace Ui {
class View;
}

namespace s21 {

class AffineData {
 public:
  AffineData();
  AffineData(Ui::View* ui);
  AffineData(const AffineData&) = default;
  AffineData& operator=(const AffineData&) = default;
  AffineData(AffineData&&) = delete;
  AffineData& operator=(AffineData&&) = default;
  ~AffineData() = default;
  bool operator!=(AffineData&);
  double move_x;
  double move_y;
  double move_z;
  double scale_k;
  double rotate_x;
  double rotate_y;
  double rotate_z;
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_AFFINE_DATA_H
