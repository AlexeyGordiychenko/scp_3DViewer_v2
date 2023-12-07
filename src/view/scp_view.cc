#include "scp_view.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "command/scp_affinesavecmd.h"
#include "command/scp_projectiontypechangecmd.h"
#include "command/scp_setbackgroundcolorcmd.h"
#include "command/scp_setlinecolorcmd.h"
#include "command/scp_setlinethicknesscmd.h"
#include "command/scp_setlinetypecmd.h"
#include "command/scp_setverticecolorcmd.h"
#include "command/scp_setverticesizecmd.h"
#include "command/scp_setverticetypecmd.h"
#include "scp_gifcreator.h"

scp::View::View(Controller* controller, QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::View),
      controller_(controller),
      settings_("21school", "3DViewer_v2.0") {
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

  LoadSettings();

  CreateCommandStack();
}

scp::View::~View() {
  emit die();
  SaveSettings();
  delete ui_;
  delete undo_stack_;
  GifCreator::ResetInstance();
}

void scp::View::AddObserver(Observer* observer) {
  observers.push_back(observer);
}

void scp::View::RemoveObserver(Observer* observer) {
  observers.remove(observer);
}

void scp::View::Notify(EventType event) {
  for (auto observer : observers) observer->UpdateObserver(event);
}

void scp::View::SetBackgroundColor(QColor color) {
  bg_color_ = color;
  SetButtonBackground(ui_->bgColor, bg_color_);
  Notify(EventType::kAppearanceChange);
}

QColor scp::View::GetBackgroundColor() { return bg_color_; }

void scp::View::SetLineColor(QColor color) {
  line_color_ = color;
  SetButtonBackground(ui_->lineColor, line_color_);
  Notify(EventType::kAppearanceChange);
}

QColor scp::View::GetLineColor() { return line_color_; }

void scp::View::SetVerticeColor(QColor color) {
  vertice_color_ = color;
  SetButtonBackground(ui_->verticeColor, vertice_color_);
  Notify(EventType::kAppearanceChange);
}

QColor scp::View::GetVerticeColor() { return vertice_color_; }

void scp::View::SetProjectionType(ProjectionType type) {
  projection_type_ = type;
  ui_->projectionType->setCurrentIndex(projection_type_);
  Notify(EventType::kSetProjectionType);
}

scp::ProjectionType scp::View::GetProjectionType() { return projection_type_; }

void scp::View::SetLineType(LineType type) {
  line_type_ = type;
  SetLineTypeUI(type);
  Notify(EventType::kAppearanceChange);
}

scp::LineType scp::View::GetLineType() { return line_type_; }

void scp::View::SetVerticeType(VerticeType type) {
  vertice_type_ = type;
  SetVerticeTypeUI(type);
  Notify(EventType::kAppearanceChange);
}

scp::VerticeType scp::View::GetVerticeType() { return vertice_type_; }

void scp::View::SetVerticeSize(double value) {
  vertice_size_ = value / kVertexSizeCoeff;
  ui_->verticeSize->setValue(value);
  Notify(EventType::kAppearanceChange);
}

double scp::View::GetVerticeSize() { return vertice_size_; }

void scp::View::SetLineThickness(double value) {
  line_thickness_ = value / kLineThicknessCoeff;
  ui_->lineThickness->setValue(value);
  Notify(EventType::kAppearanceChange);
}

double scp::View::GetLineThickness() { return line_thickness_; }

void scp::View::SetButtonBackground(QPushButton* button, QColor color) {
  button->setStyleSheet(QString("background-color: %1").arg(color.name()));
}

void scp::View::OpenFile() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
  if (filename.isEmpty()) return;
  auto index = ui_->filePath->findText(filename);
  auto count = ui_->filePath->count();
  if (index == -1) {
    if (count >= history_max_list_) {
      ui_->filePath->removeItem(0);
      count--;
    }
    ui_->filePath->addItem(filename);
    index = count;
  }
  FilePathChange(index);
}

void scp::View::RenderFile() {
  if (file_changed_) {
    std::string filename = ui_->filePath->currentText().toStdString();
    try {
      controller_->Initialize(filename);
      file_changed_ = false;
    } catch (const std::exception& e) {
      QMessageBox err_msg;
      err_msg.information(0, "", e.what());
    }
    ui_->numVertices->setText(QString::number(controller_->GetVerticesCount()));
    ui_->numEdges->setText(
        QString::number(controller_->GetPolygonsEdgesCount()));
  } else {
    controller_->RestoreVertices();
  }
  Notify(EventType::kRenderFile);
}

void scp::View::ProjectionTypeChange(int idx) {
  if (projection_type_ != idx) {
    undo_stack_->Push(new ProjectionTypeChangeCommand(
        projection_type_, static_cast<ProjectionType>(idx), this));
  }
}

void scp::View::TakeScreenshot() {
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
    QMessageBox ss_saved_msg;
    ss_saved_msg.information(0, "", "Screenshot saved successfully.");
  }
}

void scp::View::GetGIF() {
  const QString gifExt = ".gif";
  QFileInfo fileInfo(ui_->filePath->currentText());
  QFileDialog saveGifDialog(this);
  QString saveFilename =
      fileInfo.baseName() + " anim " +
      QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss") + gifExt;
  QString gifName =
      saveGifDialog.getSaveFileName(this, "GIF saving", saveFilename, gifExt);
  if (gifName.length() > 0) {
    scp::GifCreator* gifCreator =
        scp::GifCreator::GetInstance(ui_->openGLWidget);
    gifCreator->CreateGif(gifName);
  }
}

void scp::View::ApplyAffine() {
  AffineData data(ui_);
  controller_->RestoreVertices();
  controller_->ApplyAffine(data);
  Notify(EventType::kSetAffine);
}

void scp::View::ResetAffine() {
  ui_->scale_on_k->setValue(1);
  ui_->move_on_x->setValue(0);
  ui_->move_on_y->setValue(0);
  ui_->move_on_z->setValue(0);
  ui_->rotate_x->setValue(0);
  ui_->rotate_y->setValue(0);
  ui_->rotate_z->setValue(0);
  SaveAffine();
}

void scp::View::BackgroundColorChange() {
  QColor color =
      QColorDialog::getColor(bg_color_, this, "Choose background color");
  undo_stack_->Push(new SetBackgroundColorCmd(bg_color_, color, this));
}

void scp::View::LineColorChange() {
  QColor color = QColorDialog::getColor(line_color_, this, "Choose line color");
  undo_stack_->Push(new SetLineColorCmd(line_color_, color, this));
}

void scp::View::SolidLineTypeChange() { LineTypeChange(kSolid); }

void scp::View::DashedLineTypeChange() { LineTypeChange(kDashed); }

void scp::View::LineThicknessChange(int value) { SetLineThickness(value); }

void scp::View::NoneVerticeTypeChange() { VerticeTypeChange(kNone); }

void scp::View::CircleVerticeTypeChange() { VerticeTypeChange(kCircle); }

void scp::View::SquareVerticeTypeChange() { VerticeTypeChange(kSquare); }

void scp::View::VerticeSizeChange(int value) { SetVerticeSize(value); }

void scp::View::VerticeColorChange() {
  QColor color =
      QColorDialog::getColor(vertice_color_, this, "Choose vertice color");
  undo_stack_->Push(new SetVerticeColorCmd(vertice_color_, color, this));
}

void scp::View::FilePathChange(int idx) {
  ui_->filePath->setCurrentIndex(idx);
  file_changed_ = true;
}

void scp::View::LineThicknessSliderReleased() {
  double old = SetLineThicknessCmd::get_old();
  double value = ui_->lineThickness->value();
  undo_stack_->Push(new scp::SetLineThicknessCmd(old, value, this));
}

void scp::View::VerticeSizeSliderReleased() {
  double old = SetVerticeSizeCmd::get_old();
  double value = ui_->verticeSize->value();
  undo_stack_->Push(new SetVerticeSizeCmd(old, value, this));
}

void scp::View::SaveAffine() {
  AffineData old_data = AffineSaveCmd::get_old();
  AffineData new_data = AffineData(ui_);
  if (old_data != new_data) {
    undo_stack_->Push(new AffineSaveCmd(old_data, new_data, ui_));
  }
}

void scp::View::CreateCommandStack() {
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
  SetLineThicknessCmd::init_old(line_thickness_ * kLineThicknessCoeff);
  SetVerticeSizeCmd::init_old(vertice_size_ * kVertexSizeCoeff);
}

void scp::View::SaveSettings() {
  settings_.setValue("bg_color", bg_color_);
  settings_.setValue("line_color", line_color_);
  settings_.setValue("vertice_color", vertice_color_);
  settings_.setValue("line_type", line_type_);
  settings_.setValue("line_thickness", line_thickness_);
  settings_.setValue("vertice_type", vertice_type_);
  settings_.setValue("vertice_size", vertice_size_);
  settings_.setValue("projectionType", projection_type_);
}

void scp::View::LoadSettings() {
  bg_color_ = settings_.value("bg_color", bg_color_).value<QColor>();
  line_color_ = settings_.value("line_color", line_color_).value<QColor>();
  vertice_color_ =
      settings_.value("vertice_color", vertice_color_).value<QColor>();
  line_type_ = settings_.value("line_type").value<LineType>();
  line_thickness_ = settings_.value("line_thickness").toDouble();
  vertice_type_ = settings_.value("vertice_type").value<VerticeType>();
  vertice_size_ = settings_.value("vertice_size").toDouble();
  projection_type_ = settings_.value("projectionType").value<ProjectionType>();
  SetValuesOnButtons();
  Notify(EventType::kLoadSettings);
}

void scp::View::SetValuesOnButtons() {
  SetButtonBackground(ui_->bgColor, bg_color_);
  SetButtonBackground(ui_->lineColor, line_color_);
  SetButtonBackground(ui_->verticeColor, vertice_color_);
  SetLineTypeUI(line_type_);
  SetVerticeTypeUI(vertice_type_);
  ui_->lineThickness->setValue(line_thickness_ * kLineThicknessCoeff);
  ui_->verticeSize->setValue(vertice_size_ * kVertexSizeCoeff);
  ui_->projectionType->setCurrentIndex(projection_type_);
}

void scp::View::SetLineTypeUI(LineType type) {
  ui_->solidLineType->setChecked(type == LineType::kSolid);
  ui_->dashedLineType->setChecked(type == LineType::kDashed);
}

void scp::View::SetVerticeTypeUI(VerticeType type) {
  ui_->noneVerticeType->setChecked(type == VerticeType::kNone);
  ui_->circleVerticeType->setChecked(type == VerticeType::kCircle);
  ui_->squareVerticeType->setChecked(type == VerticeType::kSquare);
}

void scp::View::LineTypeChange(LineType type) {
  undo_stack_->Push(new SetLineTypeCmd(line_type_, type, this));
}

void scp::View::VerticeTypeChange(VerticeType type) {
  undo_stack_->Push(new SetVerticeTypeCmd(vertice_type_, type, this));
}
