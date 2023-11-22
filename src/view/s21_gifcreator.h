#ifndef S21_3DVIEWER_V2_GIFCREATOR_H
#define S21_3DVIEWER_V2_GIFCREATOR_H

#include <QImage>
#include <QMessageBox>
#include <QObject>
#include <QOpenGLWidget>
#include <QTimer>

#include "../thirdparty/gifanim/gifanim.h"

namespace s21 {

class GifCreator : public QObject {
  Q_OBJECT

 public:
  GifCreator(QOpenGLWidget *widget, const QString &outputGifPath,
             int width = 640, int height = 480, int fps = 10,
             int duration_sec = 5, QObject *parent = nullptr);
  void createGif();
  void endGif();
  ~GifCreator();

 private slots:
  void captureFrame();

 private:
  QOpenGLWidget *widget;
  QString outputGifPath;
  QTimer timer;
  GifAnim gifAnim;
  GifWriter gifWriter;
  int frameCount;
  int frameMax;
  int frameDelay;
  uint32_t width, height;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_GIFCREATOR_H
