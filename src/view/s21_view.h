#ifndef S21_3DVIEWER_V2_VIEW_H
#define S21_3DVIEWER_V2_VIEW_H

#include <QMainWindow>
#include <QSettings>

#include "../controller/s21_controller.h"
#include "../utils/s21_enums.h"
#include "command/s21_commandstack.h"

namespace Ui {
class View;
}

namespace s21 {

class GifCreator;

class View : public QMainWindow {
  Q_OBJECT

 public:
  // Constructors and the destructor
  View(Controller* controller, QWidget* parent = nullptr);
  View(const View&) = delete;
  View& operator=(const View&) = delete;
  View(View&&) = delete;
  View& operator=(View&&) = delete;
  ~View();

 private slots:
  void OpenFile();
  void RenderFile();
  void ProjectionTypeChange(int idx);
  void TakeScreenshot();
  void GetGIF();
  void Affine();
  void Reset();
  void ResetParams();
  void SetBackgroundColor();
  void SetPolygonColor();
  void SolidPolygonType();
  void DashedPolygonType();
  void SetPolygonThickness(int value);
  void SetNoneVertice();
  void SetCircleVertice();
  void SetSquareVertice();
  void SetVerticeSize(int value);
  void SetVerticeColor();
  void FilePathChange(int idx);
  void PolygonThicknessSliderReleased();
  void VerticeSizeSliderReleased();
  void SaveAffine();

 private:
  Ui::View* ui_;
  Controller* controller_;
  s21::GifCreator* gifCreator_;
  QSettings* settings_;
  CommandStack* undo_stack_;
  int history_max_list_ = 10;
  bool file_changed_ = true;

  void CreateCommandStack();
  void SaveSettings();
  void LoadSettings();
  void SetValuesOnButtons();
  void SetPolygonType(PolygonType type);
  void SetVerticeType(VerticeType type);
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_VIEW_H
