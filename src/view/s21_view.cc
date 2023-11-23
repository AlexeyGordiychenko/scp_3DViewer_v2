#include "s21_view.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "../controller/s21_controller.h"
#include "s21_gifcreator.h"
#include "s21_glwidget.h"
#include "ui_s21_view.h"

s21::View::View(s21::Controller *controller, QWidget *parent)
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

  ui_->projectionType->addItem("Parallel", PARALLEL);
  ui_->projectionType->addItem("Central", CENTRAL);

  ui_->filePath->setReadOnly(true);

  ui_->openGLWidget->setController(controller);

  settings_ = new QSettings("21school", "3DViewer_v1.0", this);
  LoadSettings();
  SetValuesOnButtons();
}

s21::View::~View() {
  SaveSettings();
  delete settings_;
  delete ui_;
}

Ui::View *s21::View::getUI()
{

}

void s21::View::OpenFile() {
  QString QString_filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
  ui_->filePath->setText(QString_filename);
  ui_->openGLWidget->fileChanged = true;
}

void s21::View::Reset() {
  if (ui_->openGLWidget->isParsed && !ui_->openGLWidget->fileChanged) {
    ui_->openGLWidget->clearTransformations();
    ui_->openGLWidget->RestoreVertices();
    ui_->openGLWidget->update();
  }
}

void s21::View::RenderFile() {
  if (ui_->openGLWidget->fileChanged) {
    std::string std_filename = ui_->filePath->text().toStdString();
    ui_->openGLWidget->setFilename((char *)std_filename.c_str());
    try {
      ui_->openGLWidget->parseFile();
    } catch (const std::exception &e) {
      QMessageBox messageBoxImage;
      messageBoxImage.information(0, "", e.what());
    }

    ui_->openGLWidget->fileChanged = false;
  } else {
    ui_->openGLWidget->clearTransformations();
    ui_->openGLWidget->RestoreVertices();
    ui_->openGLWidget->update();
  }
}

void s21::View::ProjectionTypeChange(int idx) {
  ui_->openGLWidget->setProjectionType(idx);
  ui_->openGLWidget->update();
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
    s21::GifCreator *gifCreator =
        new s21::GifCreator(ui_->openGLWidget, gifName);
    gifCreator->createGif();
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
}

void s21::View::Affine() {
  if (ui_->openGLWidget->isParsed && !ui_->openGLWidget->fileChanged) {
    double move_x = (ui_->move_on_x->value());
    double move_y = (ui_->move_on_y->value());
    double move_z = (ui_->move_on_z->value());
    double scale_k = (ui_->scale_on_k->value());
    double rotate_x = (ui_->rotate_x->value());
    double rotate_y = (ui_->rotate_y->value());
    double rotate_z = (ui_->rotate_z->value());
    if (scale_k == 0) scale_k = 1;
    ui_->openGLWidget->clearTransformations();
    ui_->openGLWidget->RestoreVertices();
    ui_->openGLWidget->scale(scale_k);
    ui_->openGLWidget->move(move_x, move_y, move_z);
    ui_->openGLWidget->rotate((rotate_x)*M_PI / 180, (rotate_y)*M_PI / 180,
                              (rotate_z)*M_PI / 180);
    ui_->openGLWidget->update();
  }
}

void s21::View::SetBackgroundColor() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui_->openGLWidget->bg_red = color.redF();
    ui_->openGLWidget->bg_green = color.greenF();
    ui_->openGLWidget->bg_blue = color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
            color.green(), color.blue());
    ui_->setBgColor->setStyleSheet(rgba_color);
    ui_->openGLWidget->update();
  }
}

void s21::View::SetPolygonColor() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui_->openGLWidget->pol_red = color.redF();
    ui_->openGLWidget->pol_green = color.greenF();
    ui_->openGLWidget->pol_blue = color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
            color.green(), color.blue());
    ui_->setPolygonColor->setStyleSheet(rgba_color);
    ui_->openGLWidget->update();
  }
}

void s21::View::SolidPolygonType() {
  ui_->openGLWidget->edges_type = SOLID;
  ui_->openGLWidget->update();
}

void s21::View::DashedPolygonType() {
  ui_->openGLWidget->edges_type = DASHED;
  ui_->openGLWidget->update();
}

void s21::View::SetPolygonThickness(int value) {
  ui_->openGLWidget->edges_thickness = value / 10;
  ui_->openGLWidget->update();
}

void s21::View::SetNoneVertice() {
  ui_->openGLWidget->vertice_type = NONE;
  ui_->openGLWidget->update();
}

void s21::View::SetCircleVertice() {
  ui_->openGLWidget->vertice_type = CIRCLE;
  ui_->openGLWidget->update();
}

void s21::View::SetSquareVertice() {
  ui_->openGLWidget->vertice_type = SQUARE;
  ui_->openGLWidget->update();
}

void s21::View::SetVerticeSize(int value) {
  ui_->openGLWidget->vertice_size = value / 5;
  ui_->openGLWidget->update();
}

void s21::View::SetVerticeColor() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui_->openGLWidget->ver_red = color.redF();
    ui_->openGLWidget->ver_green = color.greenF();
    ui_->openGLWidget->ver_blue = color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", color.red(),
            color.green(), color.blue());
    ui_->setVerticeColor->setStyleSheet(rgba_color);
    ui_->openGLWidget->update();
  }
}

void s21::View::SaveSettings() {
  settings_->setValue("bg_red", ui_->openGLWidget->bg_red);
  settings_->setValue("bg_green", ui_->openGLWidget->bg_green);
  settings_->setValue("bg_blue", ui_->openGLWidget->bg_blue);
  settings_->setValue("pol_red", ui_->openGLWidget->pol_red);
  settings_->setValue("pol_green", ui_->openGLWidget->pol_green);
  settings_->setValue("pol_blue", ui_->openGLWidget->pol_blue);
  settings_->setValue("edges_type", ui_->openGLWidget->edges_type);
  settings_->setValue("edges_thickness", ui_->openGLWidget->edges_thickness);
  settings_->setValue("vertice_type", ui_->openGLWidget->vertice_type);
  settings_->setValue("vertice_size", ui_->openGLWidget->vertice_size);
  settings_->setValue("ver_red", ui_->openGLWidget->ver_red);
  settings_->setValue("ver_green", ui_->openGLWidget->ver_green);
  settings_->setValue("ver_blue", ui_->openGLWidget->ver_blue);
  settings_->setValue("projectionType", ui_->openGLWidget->projectionType);
}

void s21::View::LoadSettings() {
  ui_->openGLWidget->bg_red = settings_->value("bg_red").toDouble();
  ui_->openGLWidget->bg_green = settings_->value("bg_green").toDouble();
  ui_->openGLWidget->bg_blue = settings_->value("bg_blue").toDouble();
  ui_->openGLWidget->pol_red = settings_->value("pol_red").toDouble();
  if (settings_->contains("pol_green")) {
    ui_->openGLWidget->pol_green = settings_->value("pol_green").toDouble();
  } else {
    ui_->openGLWidget->pol_green = 1;
  }
  ui_->openGLWidget->pol_blue = settings_->value("pol_blue").toDouble();
  ui_->openGLWidget->edges_type = settings_->value("edges_type").toInt();
  ui_->openGLWidget->edges_thickness =
      settings_->value("edges_thickness").toDouble();
  ui_->openGLWidget->vertice_type = settings_->value("vertice_type").toInt();
  ui_->openGLWidget->vertice_size = settings_->value("vertice_size").toInt();
  ui_->openGLWidget->ver_red = settings_->value("ver_red").toDouble();
  ui_->openGLWidget->ver_green = settings_->value("ver_green").toDouble();
  if (settings_->contains("ver_blue")) {
    ui_->openGLWidget->ver_blue = settings_->value("ver_blue").toDouble();
  } else {
    ui_->openGLWidget->ver_blue = 1;
  }
  ui_->openGLWidget->projectionType =
      settings_->value("projectionType").toInt();
  ui_->openGLWidget->update();
}

void s21::View::SetValuesOnButtons() {
  char bg_color[40], pol_color[40], ver_color[40];
  sprintf(bg_color, "background-color: rgb(%d,%d,%d)",
          (int)(ui_->openGLWidget->bg_red * 255),
          (int)(ui_->openGLWidget->bg_green * 255),
          (int)(ui_->openGLWidget->bg_blue * 255));
  ui_->setBgColor->setStyleSheet(bg_color);
  sprintf(pol_color, "background-color: rgb(%d,%d,%d)",
          (int)(ui_->openGLWidget->pol_red * 255),
          (int)(ui_->openGLWidget->pol_green * 255),
          (int)(ui_->openGLWidget->pol_blue * 255));
  ui_->setPolygonColor->setStyleSheet(pol_color);
  sprintf(ver_color, "background-color: rgb(%d,%d,%d)",
          (int)(ui_->openGLWidget->ver_red * 255),
          (int)(ui_->openGLWidget->ver_green * 255),
          (int)(ui_->openGLWidget->ver_blue * 255));
  ui_->setVerticeColor->setStyleSheet(ver_color);
  if (ui_->openGLWidget->edges_type == SOLID) {
    ui_->solidPolygonType->setChecked(true);
  } else {
    ui_->dashedPolygonType->setChecked(true);
  }
  if (ui_->openGLWidget->vertice_type == NONE) {
    ui_->noneVertice->setChecked(true);
  } else if (ui_->openGLWidget->vertice_type == CIRCLE) {
    ui_->circleVertice->setChecked(true);
  } else {
    ui_->squareVertice->setChecked(true);
  }
  ui_->polygonThickness->setValue(settings_->value("edges_thickness").toInt() *
                                  10);
  ui_->sizeVertice->setValue(settings_->value("vertice_size").toInt() * 5);
  if (ui_->openGLWidget->projectionType == PARALLEL) {
    ui_->projectionType->setCurrentIndex(0);
  } else {
    ui_->projectionType->setCurrentIndex(1);
  }
}
