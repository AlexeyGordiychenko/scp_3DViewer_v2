#ifndef S21_3DVIEWER_V2_VIEW_H
#define S21_3DVIEWER_V2_VIEW_H

#include <QMainWindow>
#include <QSettings>
#include <list>

#include "../controller/s21_controller.h"
#include "../utils/s21_enums.h"
#include "../utils/s21_observer.h"
#include "command/s21_commandstack.h"
#include "ui_s21_view.h"

namespace Ui {
class View;
}

namespace s21 {

class GifCreator;

class View : public QMainWindow, public Observable {
  Q_OBJECT

 public:
  // Constructors and the destructor
  View(Controller* controller, QWidget* parent = nullptr);
  View(const View&) = delete;
  View& operator=(const View&) = delete;
  View(View&&) = delete;
  View& operator=(View&&) = delete;
  ~View();

  // Observer functions
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);
  void Notify(EventType event);

  // Color functions
  void SetBackgroundColor(QColor color);
  QColor GetBackgroundColor();
  void SetLineColor(QColor color);
  QColor GetLineColor();
  void SetVerticeColor(QColor color);
  QColor GetVerticeColor();

  void SetProjectionType(ProjectionType type);
  ProjectionType GetProjectionType();
  void SetLineType(LineType type);
  LineType GetLineType();
  void SetVerticeType(VerticeType type);
  VerticeType GetVerticeType();
  void SetVerticeSize(double size);
  double GetVerticeSize();
  void SetLineThickness(double thickness);
  double GetLineThickness();

  // Misc functions
  void SetButtonBackground(QPushButton* button, QColor color);

 private slots:
  void OpenFile();
  void RenderFile();
  void ProjectionTypeChange(int idx);
  void TakeScreenshot();
  void GetGIF();
  void ApplyAffine();
  void ResetAffine();
  void BackgroundColorChange();
  void LineColorChange();
  void SolidLineTypeChange();
  void DashedLineTypeChange();
  void LineThicknessChange(int value);
  void NoneVerticeTypeChange();
  void CircleVerticeTypeChange();
  void SquareVerticeTypeChange();
  void VerticeSizeChange(int value);
  void VerticeColorChange();
  void FilePathChange(int idx);
  void LineThicknessSliderReleased();
  void VerticeSizeSliderReleased();
  void SaveAffine();

 private:
  // Variables
  Ui::View* ui_;
  Controller* controller_;
  s21::GifCreator* gifCreator_;
  QSettings* settings_;
  CommandStack* undo_stack_;
  int history_max_list_ = 10;
  bool file_changed_ = true;
  std::list<s21::Observer*> observers;
  QColor bg_color_ = QColor(0, 0, 0);
  QColor line_color_ = QColor(0, 255, 0);
  QColor vertice_color_ = QColor(0, 0, 255);
  ProjectionType projection_type_ = kParallel;
  LineType line_type_ = kSolid;
  VerticeType vertice_type_ = kNone;
  double vertice_size_ = 1, line_thickness_ = 1;

  void CreateCommandStack();
  void SaveSettings();
  void LoadSettings();
  void SetValuesOnButtons();
  void SetLineTypeUI(LineType type);
  void SetVerticeTypeUI(VerticeType type);
  void LineTypeChange(LineType type);
  void VerticeTypeChange(VerticeType type);
};

}  // namespace s21
#endif  // S21_3DVIEWER_V2_VIEW_H
