#ifndef S21_3DVIEWER_V2_VIEW_H
#define S21_3DVIEWER_V2_VIEW_H

#include <QMainWindow>
#include <QSettings>

#include "../controller/s21_controller.h"
#include "command/s21_commandstack.h"
#include "s21_glwidget.h"

namespace Ui {
class View;
}

namespace s21 {

class GifCreator;

class View : public QMainWindow {
  Q_OBJECT

 public:
  // Constructors and the destructor
  View(AbstractController* controller, QWidget* parent = nullptr);
  View(const View&) = delete;
  View& operator=(const View&) = delete;
  View(View&&) = delete;
  View& operator=(View&&) = delete;
  ~View();

  Ui::View* GetUI();

 private slots:
  void OpenFile();
  void RenderFile();
  void ProjectionTypeChange(int idx);
  void TakeScreenshot();
  void GetGIF();
  void Affine();
  void Affine_old();
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
  void SaveSettings();
  void LoadSettings();
  void SetValuesOnButtons();
  void PolygonThicknessSliderReleased();
  void VerticeSizeSliderReleased();
  void SetPolygonType(polygonType type);
  void SetVerticeType(verticeType type);
  void SaveAffine();

 private:
  Ui::View* ui_;
  s21::GifCreator* gifCreator_;
  QSettings* settings_;
  CommandStack* undo_stack_;
  void CreateCommandStack();
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_VIEW_H
