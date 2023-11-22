#include "s21_gifcreator.h"

s21::GifCreator::~GifCreator() {}

s21::GifCreator::GifCreator(QOpenGLWidget *widget, const QString &outputGifPath,
                       int width, int height, int fps, int duration_sec,
                       QObject *parent)
    : QObject(parent),
      widget(widget),
      outputGifPath(outputGifPath),
      frameCount(0),
      frameMax(fps * duration_sec),
      frameDelay(1000 / fps),
      width(width),
      height(height) {
  connect(&timer, &QTimer::timeout, this, &s21::GifCreator::captureFrame);
}

void s21::GifCreator::createGif() {
  gifAnim.GifBegin(&gifWriter, outputGifPath.toStdString().c_str(), this->width,
                   this->height, frameDelay);
  timer.start(frameDelay);
}

void s21::GifCreator::captureFrame() {
  if (frameCount >= frameMax) {
    endGif();
    return;
  }

  QImage frame = widget->grabFramebuffer()
                     .scaled(this->width, this->height, Qt::IgnoreAspectRatio,
                             Qt::FastTransformation)
                     .convertToFormat(QImage::Format_RGBA8888);
  gifAnim.GifWriteFrame(&gifWriter, frame.bits(), this->width, this->height,
                        frameDelay / 10);
  frameCount++;
}

void s21::GifCreator::endGif() {
  timer.stop();
  gifAnim.GifEnd(&gifWriter);
  delete this;
  QMessageBox messageBoxImage;
  messageBoxImage.information(0, "", "GIF animation saved successfully.");
}
