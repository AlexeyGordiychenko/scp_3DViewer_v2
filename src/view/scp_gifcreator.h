#ifndef SCP_3DVIEWER_V2_GIFCREATOR_H
#define SCP_3DVIEWER_V2_GIFCREATOR_H

#include <QObject>
#include <QOpenGLWidget>
#include <QTimer>

#include "../thirdparty/gifanim/gifanim.h"

namespace scp {

class GifCreator final : public QObject {
  Q_OBJECT

 public:
  // Constructors and the destructor
  GifCreator(const GifCreator &) = delete;
  GifCreator &operator=(const GifCreator &) = delete;
  GifCreator(GifCreator &&) = delete;
  GifCreator &operator=(GifCreator &&) = delete;
  ~GifCreator() = default;

  // Singleton functions
  static GifCreator *GetInstance(QOpenGLWidget *widget);
  static void ResetInstance();

  // Main functions
  void CreateGif(QString output_gif_path);
  void EndGif();

 private slots:
  void CaptureFrame();

 private:
  static GifCreator *gif_creator_;
  QOpenGLWidget *widget_;
  QTimer timer_;
  GifAnim gif_anim_;
  GifWriter gif_writer_;
  uint32_t frames_count_, frames_max_, frame_delay_, width_, height_;

  GifCreator(QOpenGLWidget *widget, int width = 640, int height = 480,
             int fps = 10, int duration_sec = 5);
};
}  // namespace scp
#endif  // SCP_3DVIEWER_V2_GIFCREATOR_H
