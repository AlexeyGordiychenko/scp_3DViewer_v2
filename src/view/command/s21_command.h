#ifndef S21_3DVIEWER_V2_COMMAND_COMMAND_H
#define S21_3DVIEWER_V2_COMMAND_COMMAND_H

namespace s21 {

class Command {
 public:
  Command() = default;
  Command(const Command&) = delete;
  Command& operator=(const Command&) = delete;
  Command(Command&&) = delete;
  Command& operator=(Command&&) = delete;
  //~Command() = default;
  virtual ~Command() = default;
  virtual void Redo() = 0;
  virtual void Undo() = 0;
};

}  // namespace s21

#endif
