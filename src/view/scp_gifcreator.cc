#include "scp_gifcreator.h"

#include <QImage>
#include <QMessageBox>

scp::GifCreator *scp::GifCreator::gif_creator_ = nullptr;

scp::GifCreator *scp::GifCreator::GetInstance(QOpenGLWidget *widget) {
  if (gif_creator_ == nullptr) {
    gif_creator_ = new scp::GifCreator(widget);
  }
  return gif_creator_;
};

void scp::GifCreator::ResetInstance() {
  if (gif_creator_ != nullptr) {
    delete gif_creator_;
    gif_creator_ = nullptr;
  }
}

scp::GifCreator::GifCreator(QOpenGLWidget *widget, int width, int height,
                            int fps, int duration_sec)
    : QObject(widget),
      widget_(widget),
      frames_count_(0),
      frames_max_(fps * duration_sec),
      frame_delay_(1000 / fps),
      width_(width),
      height_(height) {
  connect(&timer_, &QTimer::timeout, this, &scp::GifCreator::CaptureFrame);
}

void scp::GifCreator::CreateGif(QString gif_path) {
  gif_anim_.GifBegin(&gif_writer_, gif_path.toStdString().c_str(), width_,
                     height_, frame_delay_);
  timer_.start(frame_delay_);
}

void scp::GifCreator::CaptureFrame() {
  if (frames_count_ >= frames_max_) {
    EndGif();
    return;
  }

  QImage frame = widget_->grabFramebuffer()
                     .scaled(width_, height_, Qt::IgnoreAspectRatio,
                             Qt::FastTransformation)
                     .convertToFormat(QImage::Format_RGBA8888);
  gif_anim_.GifWriteFrame(&gif_writer_, frame.bits(), width_, height_,
                          frame_delay_ / 10);
  frames_count_++;
}

void scp::GifCreator::EndGif() {
  timer_.stop();
  gif_anim_.GifEnd(&gif_writer_);
  frames_count_ = 0;
  QMessageBox gif_saved_msg;
  gif_saved_msg.information(0, "", "GIF animation saved successfully.");
}
