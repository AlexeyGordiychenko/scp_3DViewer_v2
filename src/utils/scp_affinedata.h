#ifndef SCP_3DVIEWER_V2_AFFINE_DATA_H
#define SCP_3DVIEWER_V2_AFFINE_DATA_H

namespace Ui {
class View;
}

namespace scp {

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

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_AFFINE_DATA_H
