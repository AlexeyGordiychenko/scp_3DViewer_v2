#include "s21_view.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "../controller/s21_controller.h"
#include "command/s21_affinecmd.h"
#include "command/s21_affinesave.h"
#include "command/s21_projectiontypechangecmd.h"
#include "command/s21_setbackgroundcolorcmd.h"
#include "command/s21_setpolygoncolorcmd.h"
#include "command/s21_setpolygonthicknesscmd.h"
#include "command/s21_setpolygontypecmd.h"
#include "command/s21_setverticecolorcmd.h"
#include "command/s21_setverticesizecmd.h"
#include "command/s21_setverticetypecmd.h"
#include "s21_gifcreator.h"
#include "s21_glwidget.h"
#include "s21_proxycontroller.h"
#include "ui_s21_view.h"

s21::View::View(AbstractController* controller, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::View) {
  ui_->setupUi(this);
  connect(ui_->openFile, SIGNAL(clicked()), this, SLOT(OpenFile()));
  connect(ui_->renderFile, SIGNAL(clicked()), this, SLOT(RenderFile()));
  connect(ui_->projectionType, SIGNAL(currentIndexChanged(int)), this,
          SLOT(ProjectionTypeChange(int)));
  connect(ui_->getScreenshot, SIGNAL(clicked()), this, SLOT(TakeScreenshot()));
  connect(ui_->getGIF, SIGNAL(clicked()), this, SLOT(GetGIF()));
  connect(ui_->apply_params, SIGNAL(clicked()), this, SLOT(Affine()));
  connect(ui_->reset_model, SIGNAL(clicked()), this, SLOT(Reset()));
  connect(ui_->reset_params, SIGNAL(clicked()), this, SLOT(ResetParams()));
  connect(ui_->setBgColor, SIGNAL(clicked()), this, SLOT(SetBackgroundColor()));
  connect(ui_->setPolygonColor, SIGNAL(clicked()), this,
          SLOT(SetPolygonColor()));
  connect(ui_->solidPolygonType, SIGNAL(clicked()), this,
          SLOT(SolidPolygonType()));
  connect(ui_->dashedPolygonType, SIGNAL(clicked()), this,
          SLOT(DashedPolygonType()));
  connect(ui_->polygonThickness, SIGNAL(valueChanged(int)), this,
          SLOT(SetPolygonThickness(int)));
  connect(ui_->noneVertice, SIGNAL(clicked()), this, SLOT(SetNoneVertice()));
  connect(ui_->circleVertice, SIGNAL(clicked()), this,
          SLOT(SetCircleVertice()));
  connect(ui_->squareVertice, SIGNAL(clicked()), this,
          SLOT(SetSquareVertice()));
  connect(ui_->sizeVertice, SIGNAL(valueChanged(int)), this,
          SLOT(SetVerticeSize(int)));
  connect(ui_->setVerticeColor, SIGNAL(clicked()), this,
          SLOT(SetVerticeColor()));

  ui_->projectionType->addItem("Parallel", kParallel);
  ui_->projectionType->addItem("Central", kCentral);

  ui_->filePath->setReadOnly(true);

  ui_->openGLWidget->SetController(new ProxyController(controller, this));

  settings_ = new QSettings("21school", "3DViewer_v2.0", this);
  LoadSettings();
  SetValuesOnButtons();

  CreateCommandStack();
}

s21::View::~View() {
  SaveSettings();
  delete settings_;
  delete ui_;
  delete undo_stack_;
}

Ui::View* s21::View::GetUI() { return ui_; }

void s21::View::OpenFile() {
  QString QString_filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
  ui_->filePath->setText(QString_filename);
  ui_->openGLWidget->fileChanged = true;
}

void s21::View::Reset() {
  if (ui_->openGLWidget->isParsed && !ui_->openGLWidget->fileChanged) {
    ui_->openGLWidget->ClearTransformations();
    ui_->openGLWidget->RestoreVertices();
    ui_->openGLWidget->update();
  }
}

void s21::View::RenderFile() {
  if (ui_->openGLWidget->fileChanged) {
    std::string std_filename = ui_->filePath->text().toStdString();
    ui_->openGLWidget->SetFilename((char*)std_filename.c_str());
    try {
      ui_->openGLWidget->ParseFile();
    } catch (const std::exception& e) {
      QMessageBox messageBoxImage;
      messageBoxImage.information(0, "", e.what());
    }

    ui_->openGLWidget->fileChanged = false;
  } else {
    ui_->openGLWidget->ClearTransformations();
    ui_->openGLWidget->RestoreVertices();
    ui_->openGLWidget->update();
  }
}

void s21::View::ProjectionTypeChange(int idx) {
  int old = ui_->openGLWidget->projectionType_;
  if (old != idx)
    undo_stack_->Push(new ProjectionTypeChangeCommand(old, idx, this));
}

void s21::View::TakeScreenshot() {
  const QString suffixJpeg = ".jpeg", suffixBmp = ".bmp",
                filterJpeg = "JPEG Image (*." + suffixJpeg + ")",
                filterBmp = "Bitmap Image (*." + suffixBmp + ")";
  QFileInfo fileInfo(ui_->filePath->text());
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
  QFileInfo fileInfo(ui_->filePath->text());
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

void s21::View::ResetParams() {
  ui_->scale_on_k->setValue(1);
  ui_->move_on_x->setValue(0);
  ui_->move_on_y->setValue(0);
  ui_->move_on_z->setValue(0);
  ui_->rotate_x->setValue(0);
  ui_->rotate_y->setValue(0);
  ui_->rotate_z->setValue(0);
  SaveAffine();
}

void s21::View::Affine_old() {
  static AffineData old_data = AffineData();
  AffineData new_data = AffineData(ui_);
  undo_stack_->Push(new AffineCmd(old_data, new_data, this));
  old_data = std::move(new_data);
}

void s21::View::Affine() {
  AffineData data(ui_);
  if (data.scale_k == 0) data.scale_k = 1;
  ui_->openGLWidget->ClearTransformations();
  ui_->openGLWidget->RestoreVertices();
  ui_->openGLWidget->Scale(data.scale_k);
  ui_->openGLWidget->Move(data.move_x, data.move_y, data.move_z);
  ui_->openGLWidget->Rotate((data.rotate_x) * M_PI / 180,
                            (data.rotate_y) * M_PI / 180,
                            (data.rotate_z) * M_PI / 180);
  ui_->openGLWidget->update();

  ui_->move_on_x->setValue(data.move_x);
  ui_->move_on_y->setValue(data.move_y);
  ui_->move_on_z->setValue(data.move_z);
  ui_->scale_on_k->setValue(data.scale_k);
  ui_->rotate_x->setValue(data.rotate_x);
  ui_->rotate_y->setValue(data.rotate_y);
  ui_->rotate_z->setValue(data.rotate_z);
}

void s21::View::SetBackgroundColor() {
  QColor color = QColorDialog::getColor();
  QColor old_color = QColor(ui_->openGLWidget->bg_red_ * 255,
                            ui_->openGLWidget->bg_green_ * 255,
                            ui_->openGLWidget->bg_blue_ * 255);
  undo_stack_->Push(new SetBackgroundColorCmd(old_color, color, this));
}

void s21::View::SetPolygonColor() {
  QColor color = QColorDialog::getColor();
  QColor old_color = QColor(ui_->openGLWidget->pol_red_ * 255,
                            ui_->openGLWidget->pol_green * 255,
                            ui_->openGLWidget->pol_blue_ * 255);
  undo_stack_->Push(new SetPolygonColorCmd(old_color, color, this));
}

void s21::View::SolidPolygonType() { SetPolygonType(kSolid); }

void s21::View::DashedPolygonType() { SetPolygonType(kDashed); }

void s21::View::SetPolygonType(PolygonType type) {
  PolygonType old = type == kDashed ? kSolid : kDashed;
  undo_stack_->Push(new SetPolygonTypeCmd(old, type, this));
}

void s21::View::SetPolygonThickness(int value) {
  ui_->openGLWidget->edges_thickness_ = value / 10;
  ui_->openGLWidget->update();
}

void s21::View::SetNoneVertice() { SetVerticeType(kNone); }

void s21::View::SetCircleVertice() { SetVerticeType(kCircle); }

void s21::View::SetSquareVertice() { SetVerticeType(kSquare); }

void s21::View::SetVerticeType(VerticeType type) {
  VerticeType old = (VerticeType)(ui_->openGLWidget->vertice_type_);
  undo_stack_->Push(new SetVerticeTypeCmd(old, type, this));
}

void s21::View::SaveAffine() {
  static AffineData old_data = AffineData();
  AffineData new_data = AffineData(ui_);
  if (old_data != new_data) {
    undo_stack_->Push(new AffineSave(old_data, new_data, this));
    old_data = std::move(new_data);
  }
}

void s21::View::SetVerticeSize(int value) {
  ui_->openGLWidget->vertice_size_ = value / 5;
  ui_->openGLWidget->update();
}

void s21::View::SetVerticeColor() {
  QColor color = QColorDialog::getColor();
  QColor old_color = QColor(ui_->openGLWidget->ver_red_ * 255,
                            ui_->openGLWidget->ver_green_ * 255,
                            ui_->openGLWidget->ver_blue_ * 255);
  undo_stack_->Push(new SetVerticeColorCmd(old_color, color, this));
}

void s21::View::SaveSettings() {
  settings_->setValue("bg_red", ui_->openGLWidget->bg_red_);
  settings_->setValue("bg_green", ui_->openGLWidget->bg_green_);
  settings_->setValue("bg_blue", ui_->openGLWidget->bg_blue_);
  settings_->setValue("pol_red", ui_->openGLWidget->pol_red_);
  settings_->setValue("pol_green", ui_->openGLWidget->pol_green);
  settings_->setValue("pol_blue", ui_->openGLWidget->pol_blue_);
  settings_->setValue("edges_type", ui_->openGLWidget->edges_type_);
  settings_->setValue("edges_thickness", ui_->openGLWidget->edges_thickness_);
  settings_->setValue("vertice_type", ui_->openGLWidget->vertice_type_);
  settings_->setValue("vertice_size", ui_->openGLWidget->vertice_size_);
  settings_->setValue("ver_red", ui_->openGLWidget->ver_red_);
  settings_->setValue("ver_green", ui_->openGLWidget->ver_green_);
  settings_->setValue("ver_blue", ui_->openGLWidget->ver_blue_);
  settings_->setValue("projectionType", ui_->openGLWidget->projectionType_);
}

void s21::View::LoadSettings() {
  ui_->openGLWidget->bg_red_ = settings_->value("bg_red").toDouble();
  ui_->openGLWidget->bg_green_ = settings_->value("bg_green").toDouble();
  ui_->openGLWidget->bg_blue_ = settings_->value("bg_blue").toDouble();
  ui_->openGLWidget->pol_red_ = settings_->value("pol_red").toDouble();
  if (settings_->contains("pol_green")) {
    ui_->openGLWidget->pol_green = settings_->value("pol_green").toDouble();
  } else {
    ui_->openGLWidget->pol_green = 1;
  }
  ui_->openGLWidget->pol_blue_ = settings_->value("pol_blue").toDouble();
  ui_->openGLWidget->edges_type_ = settings_->value("edges_type").toInt();
  ui_->openGLWidget->edges_thickness_ =
      settings_->value("edges_thickness").toDouble();
  ui_->openGLWidget->vertice_type_ = settings_->value("vertice_type").toInt();
  ui_->openGLWidget->vertice_size_ = settings_->value("vertice_size").toInt();
  ui_->openGLWidget->ver_red_ = settings_->value("ver_red").toDouble();
  ui_->openGLWidget->ver_green_ = settings_->value("ver_green").toDouble();
  if (settings_->contains("ver_blue")) {
    ui_->openGLWidget->ver_blue_ = settings_->value("ver_blue").toDouble();
  } else {
    ui_->openGLWidget->ver_blue_ = 1;
  }
  ui_->openGLWidget->projectionType_ =
      settings_->value("projectionType").toInt();
  ui_->openGLWidget->update();
}

void s21::View::SetValuesOnButtons() {
  char bg_color[40], pol_color[40], ver_color[40];
  sprintf(bg_color, "background-color: rgb(%d,%d,%d)",
          (int)(ui_->openGLWidget->bg_red_ * 255),
          (int)(ui_->openGLWidget->bg_green_ * 255),
          (int)(ui_->openGLWidget->bg_blue_ * 255));
  ui_->setBgColor->setStyleSheet(bg_color);
  sprintf(pol_color, "background-color: rgb(%d,%d,%d)",
          (int)(ui_->openGLWidget->pol_red_ * 255),
          (int)(ui_->openGLWidget->pol_green * 255),
          (int)(ui_->openGLWidget->pol_blue_ * 255));
  ui_->setPolygonColor->setStyleSheet(pol_color);
  sprintf(ver_color, "background-color: rgb(%d,%d,%d)",
          (int)(ui_->openGLWidget->ver_red_ * 255),
          (int)(ui_->openGLWidget->ver_green_ * 255),
          (int)(ui_->openGLWidget->ver_blue_ * 255));
  ui_->setVerticeColor->setStyleSheet(ver_color);
  if (ui_->openGLWidget->edges_type_ == kSolid) {
    ui_->solidPolygonType->setChecked(true);
  } else {
    ui_->dashedPolygonType->setChecked(true);
  }
  if (ui_->openGLWidget->vertice_type_ == kNone) {
    ui_->noneVertice->setChecked(true);
  } else if (ui_->openGLWidget->vertice_type_ == kCircle) {
    ui_->circleVertice->setChecked(true);
  } else {
    ui_->squareVertice->setChecked(true);
  }
  ui_->polygonThickness->setValue(
      settings_->value("edges_thickness").toDouble() * 10);
  ui_->sizeVertice->setValue(settings_->value("vertice_size").toDouble() * 5);
  if (ui_->openGLWidget->projectionType_ == kParallel) {
    ui_->projectionType->setCurrentIndex(0);
  } else {
    ui_->projectionType->setCurrentIndex(1);
  }
}

void s21::View::CreateCommandStack() {
  undo_stack_ = new CommandStack();
  connect(ui_->undo_button, &QPushButton::clicked, undo_stack_,
          &CommandStack::Undo);
  connect(ui_->redo_button, &QPushButton::clicked, undo_stack_,
          &CommandStack::Redo);
  connect(ui_->polygonThickness, &QSlider::sliderReleased, this,
          &View::PolygonThicknessSliderReleased);
  connect(ui_->sizeVertice, &QSlider::sliderReleased, this,
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
}

void s21::View::PolygonThicknessSliderReleased() {
  static double old = settings_->value("edges_thickness").toDouble() * 10;
  double value = ui_->polygonThickness->value();
  undo_stack_->Push(new s21::SetPolygonThicknessCmd(old, value, this));
  old = value;
}

void s21::View::VerticeSizeSliderReleased() {
  static double old = settings_->value("vertice_size").toDouble() * 5;
  double value = ui_->sizeVertice->value();
  undo_stack_->Push(new SetVerticeSizeCmd(old, value, this));
  old = value;
}
