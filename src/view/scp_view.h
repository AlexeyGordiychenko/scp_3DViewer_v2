#ifndef SCP_3DVIEWER_V2_VIEW_H
#define SCP_3DVIEWER_V2_VIEW_H

#include <QMainWindow>
#include <QSettings>
#include <list>

#include "../controller/scp_controller.h"
#include "../utils/scp_enums.h"
#include "../utils/scp_observer.h"
#include "command/scp_commandstack.h"
#include "ui_scp_view.h"

namespace Ui {
class View;
}

namespace scp {

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

 signals:
  void die();

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
  QSettings settings_;
  CommandStack* undo_stack_;
  int history_max_list_ = 10;
  bool file_changed_ = true;
  std::list<scp::Observer*> observers;
  QColor bg_color_ = QColor(0, 0, 0);
  QColor line_color_ = QColor(0, 255, 0);
  QColor vertice_color_ = QColor(0, 0, 255);
  ProjectionType projection_type_ = kParallel;
  LineType line_type_ = kSolid;
  VerticeType vertice_type_ = kNone;
  double vertice_size_ = 1, line_thickness_ = 1, kVertexSizeCoeff = 5,
         kLineThicknessCoeff = 10;

  void CreateCommandStack();
  void SaveSettings();
  void LoadSettings();
  void SetValuesOnButtons();
  void SetLineTypeUI(LineType type);
  void SetVerticeTypeUI(VerticeType type);
  void LineTypeChange(LineType type);
  void VerticeTypeChange(VerticeType type);
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_VIEW_H
