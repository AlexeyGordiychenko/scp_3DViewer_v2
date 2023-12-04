#include "s21_view.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "command/s21_affinesavecmd.h"
#include "command/s21_projectiontypechangecmd.h"
#include "command/s21_setbackgroundcolorcmd.h"
#include "command/s21_setlinecolorcmd.h"
#include "command/s21_setlinethicknesscmd.h"
#include "command/s21_setlinetypecmd.h"
#include "command/s21_setverticecolorcmd.h"
#include "command/s21_setverticesizecmd.h"
#include "command/s21_setverticetypecmd.h"
#include "s21_gifcreator.h"

s21::View::View(Controller* controller, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::View), controller_(controller) {
  ui_->setupUi(this);

  // Main menu
  connect(ui_->openFile, &QPushButton::clicked, this, &View::OpenFile);
  connect(ui_->renderFile, &QPushButton::clicked, this, &View::RenderFile);
  connect(ui_->projectionType, qOverload<int>(&QComboBox::currentIndexChanged),
          this, &View::ProjectionTypeChange);
  connect(ui_->takeScreenshot, &QPushButton::clicked, this,
          &View::TakeScreenshot);
  connect(ui_->getGIF, &QPushButton::clicked, this, &View::GetGIF);

  // Affine buttons
  connect(ui_->applyAffine, &QPushButton::clicked, this, &View::ApplyAffine);
  connect(ui_->resetAffine, &QPushButton::clicked, this, &View::ResetAffine);

  // Background color
  connect(ui_->bgColor, &QPushButton::clicked, this,
          &View::BackgroundColorChange);

  // Line
  connect(ui_->lineColor, &QPushButton::clicked, this, &View::LineColorChange);
  connect(ui_->solidLineType, &QPushButton::clicked, this,
          &View::SolidLineTypeChange);
  connect(ui_->dashedLineType, &QPushButton::clicked, this,
          &View::DashedLineTypeChange);
  connect(ui_->lineThickness, qOverload<int>(&QSlider::valueChanged), this,
          &View::LineThicknessChange);

  // Vertice
  connect(ui_->verticeColor, &QPushButton::clicked, this,
          &View::VerticeColorChange);
  connect(ui_->noneVerticeType, &QPushButton::clicked, this,
          &View::NoneVerticeTypeChange);
  connect(ui_->circleVerticeType, &QPushButton::clicked, this,
          &View::CircleVerticeTypeChange);
  connect(ui_->squareVerticeType, &QPushButton::clicked, this,
          &View::SquareVerticeTypeChange);
  connect(ui_->verticeSize, qOverload<int>(&QSlider::valueChanged), this,
          &View::VerticeSizeChange);

  connect(ui_->filePath, qOverload<int>(&QComboBox::currentIndexChanged), this,
          &View::FilePathChange);

  ui_->projectionType->addItem("Parallel", kParallel);
  ui_->projectionType->addItem("Central", kCentral);

  ui_->openGLWidget->SetController(controller);
  ui_->openGLWidget->SetView(this);

  settings_ = new QSettings("21school", "3DViewer_v2.0", this);
  LoadSettings();

  CreateCommandStack();
}

s21::View::~View() {
  SaveSettings();
  delete settings_;
  delete ui_;
  delete undo_stack_;
}

void s21::View::AddObserver(Observer* observer) {
  observers.push_back(observer);
}

void s21::View::RemoveObserver(Observer* observer) {
  observers.remove(observer);
}

void s21::View::Notify(EventType event) {
  for (auto observer : observers) observer->UpdateObserver(event);
}

void s21::View::SetBackgroundColor(QColor color) {
  bg_color_ = color;
  SetButtonBackground(ui_->bgColor, bg_color_);
  Notify(EventType::kAppearanceChange);
}

QColor s21::View::GetBackgroundColor() { return bg_color_; }

void s21::View::SetLineColor(QColor color) {
  line_color_ = color;
  SetButtonBackground(ui_->lineColor, line_color_);
  Notify(EventType::kAppearanceChange);
}

QColor s21::View::GetLineColor() { return line_color_; }

void s21::View::SetVerticeColor(QColor color) {
  vertice_color_ = color;
  SetButtonBackground(ui_->verticeColor, vertice_color_);
  Notify(EventType::kAppearanceChange);
}

QColor s21::View::GetVerticeColor() { return vertice_color_; }

void s21::View::SetProjectionType(ProjectionType type) {
  projection_type_ = type;
  ui_->projectionType->setCurrentIndex(projection_type_);
  Notify(EventType::kSetProjectionType);
}

s21::ProjectionType s21::View::GetProjectionType() { return projection_type_; }

void s21::View::SetLineType(LineType type) {
  line_type_ = type;
  SetLineTypeUI(type);
  Notify(EventType::kAppearanceChange);
}

s21::LineType s21::View::GetLineType() { return line_type_; }

void s21::View::SetVerticeType(VerticeType type) {
  vertice_type_ = type;
  SetVerticeTypeUI(type);
  Notify(EventType::kAppearanceChange);
}

s21::VerticeType s21::View::GetVerticeType() { return vertice_type_; }

void s21::View::SetVerticeSize(double value) {
  vertice_size_ = value / 5;
  ui_->verticeSize->setValue(value);
  Notify(EventType::kAppearanceChange);
}

double s21::View::GetVerticeSize() { return vertice_size_; }

void s21::View::SetLineThickness(double value) {
  line_thickness_ = value / 10;
  ui_->lineThickness->setValue(value);
  Notify(EventType::kAppearanceChange);
}

double s21::View::GetLineThickness() { return line_thickness_; }

void s21::View::SetButtonBackground(QPushButton* button, QColor color) {
  button->setStyleSheet(QString("background-color: %1").arg(color.name()));
}

void s21::View::OpenFile() {
  QString QString_filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
  auto index = ui_->filePath->findText(QString_filename);
  auto count = ui_->filePath->count();
  if (index == -1) {
    if (count >= history_max_list_) {
      ui_->filePath->removeItem(0);
      count--;
    }
    ui_->filePath->addItem(QString_filename);
    index = count;
  }
  FilePathChange(index);
}

void s21::View::RenderFile() {
  if (file_changed_) {
    std::string filename = ui_->filePath->currentText().toStdString();
    try {
      controller_->Initialize(filename);
      file_changed_ = false;
    } catch (const std::exception& e) {
      QMessageBox err_message;
      err_message.information(0, "", e.what());
    }
    ui_->numVertices->setText(QString::number(controller_->GetVerticesCount()));
    ui_->numEdges->setText(
        QString::number(controller_->GetPolygonsEdgesCount()));
  } else {
    controller_->RestoreVertices();
  }
  Notify(EventType::kRenderFile);
}

void s21::View::ProjectionTypeChange(int idx) {
  if (projection_type_ != idx) {
    undo_stack_->Push(new ProjectionTypeChangeCommand(
        projection_type_, static_cast<ProjectionType>(idx), this));
  }
}

void s21::View::TakeScreenshot() {
  const QString suffixJpeg = ".jpeg", suffixBmp = ".bmp",
                filterJpeg = "JPEG Image (*." + suffixJpeg + ")",
                filterBmp = "Bitmap Image (*." + suffixBmp + ")";
  QFileInfo fileInfo(ui_->filePath->currentText());
  QFileDialog saveImageDialog(this);
  QString saveFilename =
      fileInfo.baseName() + " render " +
      QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss") + suffixJpeg;
  QString selectedFilter;
  QString image_name = saveImageDialog.getSaveFileName(
      this, "Screenshot saving", saveFilename, filterJpeg + ";;" + filterBmp,
      &selectedFilter);
  if (image_name.length() > 0) {
    if (!image_name.endsWith(suffixJpeg, Qt::CaseInsensitive) &&
        !image_name.endsWith(suffixBmp, Qt::CaseInsensitive)) {
      if (selectedFilter == filterJpeg) {
        image_name += suffixJpeg;
      } else {
        image_name += suffixBmp;
      }
    }
    QImage img = ui_->openGLWidget->grabFramebuffer();
    img.save(image_name);
    QMessageBox messageBoxImage;
    messageBoxImage.information(0, "", "Screenshot saved successfully.");
  }
}

void s21::View::GetGIF() {
  const QString gifExt = ".gif";
  QFileInfo fileInfo(ui_->filePath->currentText());
  QFileDialog saveGifDialog(this);
  QString saveFilename =
      fileInfo.baseName() + " anim " +
      QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss") + gifExt;
  QString gifName =
      saveGifDialog.getSaveFileName(this, "GIF saving", saveFilename, gifExt);
  if (gifName.length() > 0) {
    s21::GifCreator* gifCreator =
        s21::GifCreator::GetInstance(ui_->openGLWidget);
    gifCreator->CreateGif(gifName);
  }
}

void s21::View::ApplyAffine() {
  AffineData data(ui_);
  controller_->RestoreVertices();
  controller_->ApplyAffine(data);
  Notify(EventType::kSetAffine);
}

void s21::View::ResetAffine() {
  ui_->scale_on_k->setValue(1);
  ui_->move_on_x->setValue(0);
  ui_->move_on_y->setValue(0);
  ui_->move_on_z->setValue(0);
  ui_->rotate_x->setValue(0);
  ui_->rotate_y->setValue(0);
  ui_->rotate_z->setValue(0);
  SaveAffine();
}

void s21::View::BackgroundColorChange() {
  QColor color = QColorDialog::getColor();
  undo_stack_->Push(new SetBackgroundColorCmd(bg_color_, color, this));
}

void s21::View::LineColorChange() {
  QColor color = QColorDialog::getColor();
  undo_stack_->Push(new SetLineColorCmd(line_color_, color, this));
}

void s21::View::SolidLineTypeChange() { LineTypeChange(kSolid); }

void s21::View::DashedLineTypeChange() { LineTypeChange(kDashed); }

void s21::View::LineThicknessChange(int value) { SetLineThickness(value); }

void s21::View::NoneVerticeTypeChange() { VerticeTypeChange(kNone); }

void s21::View::CircleVerticeTypeChange() { VerticeTypeChange(kCircle); }

void s21::View::SquareVerticeTypeChange() { VerticeTypeChange(kSquare); }

void s21::View::VerticeSizeChange(int value) { SetVerticeSize(value); }

void s21::View::VerticeColorChange() {
  QColor color = QColorDialog::getColor();
  undo_stack_->Push(new SetVerticeColorCmd(vertice_color_, color, this));
}

void s21::View::FilePathChange(int idx) {
  ui_->filePath->setCurrentIndex(idx);
  file_changed_ = true;
}

void s21::View::LineThicknessSliderReleased() {
  double old = SetLineThicknessCmd::get_old();
  double value = ui_->lineThickness->value();
  undo_stack_->Push(new s21::SetLineThicknessCmd(old, value, this));
}

void s21::View::VerticeSizeSliderReleased() {
  double old = SetVerticeSizeCmd::get_old();
  double value = ui_->verticeSize->value();
  undo_stack_->Push(new SetVerticeSizeCmd(old, value, this));
}

void s21::View::SaveAffine() {
  AffineData old_data = AffineSaveCmd::get_old();
  AffineData new_data = AffineData(ui_);
  if (old_data != new_data) {
    undo_stack_->Push(new AffineSaveCmd(old_data, new_data, ui_));
  }
}

void s21::View::CreateCommandStack() {
  undo_stack_ = new CommandStack();
  connect(ui_->undo_button, &QPushButton::clicked, undo_stack_,
          &CommandStack::Undo);
  connect(ui_->redo_button, &QPushButton::clicked, undo_stack_,
          &CommandStack::Redo);
  connect(ui_->lineThickness, &QSlider::sliderReleased, this,
          &View::LineThicknessSliderReleased);
  connect(ui_->verticeSize, &QSlider::sliderReleased, this,
          &View::VerticeSizeSliderReleased);
  connect(ui_->move_on_x, &QDoubleSpinBox::editingFinished, this,
          &View::SaveAffine);
  connect(ui_->move_on_y, &QDoubleSpinBox::editingFinished, this,
          &View::SaveAffine);
  connect(ui_->move_on_z, &QDoubleSpinBox::editingFinished, this,
          &View::SaveAffine);
  connect(ui_->scale_on_k, &QDoubleSpinBox::editingFinished, this,
          &View::SaveAffine);
  connect(ui_->rotate_x, &QDoubleSpinBox::editingFinished, this,
          &View::SaveAffine);
  connect(ui_->rotate_y, &QDoubleSpinBox::editingFinished, this,
          &View::SaveAffine);
  connect(ui_->rotate_z, &QDoubleSpinBox::editingFinished, this,
          &View::SaveAffine);
  SetLineThicknessCmd::init_old(line_thickness_ * 10);
  SetVerticeSizeCmd::init_old(vertice_size_ * 5);
}

void s21::View::SaveSettings() {
  settings_->setValue("bg_color", bg_color_);
  settings_->setValue("line_color", line_color_);
  settings_->setValue("vertice_color", vertice_color_);
  settings_->setValue("line_type", line_type_);
  settings_->setValue("line_thickness", line_thickness_);
  settings_->setValue("vertice_type", vertice_type_);
  settings_->setValue("vertice_size", vertice_size_);
  settings_->setValue("projectionType", projection_type_);
}

void s21::View::LoadSettings() {
  bg_color_ = settings_->value("bg_color", bg_color_).value<QColor>();
  line_color_ = settings_->value("line_color", line_color_).value<QColor>();
  vertice_color_ =
      settings_->value("vertice_color", vertice_color_).value<QColor>();
  line_type_ = settings_->value("line_type").value<LineType>();
  line_thickness_ = settings_->value("line_thickness").toDouble();
  vertice_type_ = settings_->value("vertice_type").value<VerticeType>();
  vertice_size_ = settings_->value("vertice_size").toDouble();
  projection_type_ = settings_->value("projectionType").value<ProjectionType>();
  SetValuesOnButtons();
  Notify(EventType::kLoadSettings);
}

void s21::View::SetValuesOnButtons() {
  SetButtonBackground(ui_->bgColor, bg_color_);
  SetButtonBackground(ui_->lineColor, line_color_);
  SetButtonBackground(ui_->verticeColor, vertice_color_);
  SetLineTypeUI(line_type_);
  SetVerticeTypeUI(vertice_type_);
  ui_->lineThickness->setValue(line_thickness_ * 10);
  ui_->verticeSize->setValue(vertice_size_ * 5);
  ui_->projectionType->setCurrentIndex(projection_type_);
}

void s21::View::SetLineTypeUI(LineType type) {
  ui_->solidLineType->setChecked(type == LineType::kSolid);
  ui_->dashedLineType->setChecked(type == LineType::kDashed);
}

void s21::View::SetVerticeTypeUI(VerticeType type) {
  ui_->noneVerticeType->setChecked(type == VerticeType::kNone);
  ui_->circleVerticeType->setChecked(type == VerticeType::kCircle);
  ui_->squareVerticeType->setChecked(type == VerticeType::kSquare);
}

void s21::View::LineTypeChange(LineType type) {
  undo_stack_->Push(new SetLineTypeCmd(line_type_, type, this));
}

void s21::View::VerticeTypeChange(VerticeType type) {
  undo_stack_->Push(new SetVerticeTypeCmd(vertice_type_, type, this));
}
