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
  void CreateGif();
  void EndGif();
  ~GifCreator();

 private slots:
  void CaptureFrame();

 private:
  QOpenGLWidget *widget_;
  QString output_gif_path_;
  QTimer timer_;
  GifAnim gif_anim_;
  GifWriter gif_writer_;
  int frame_count_;
  int frame_max_;
  int frame_delay_;
  uint32_t width_, height_;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_GIFCREATOR_H
