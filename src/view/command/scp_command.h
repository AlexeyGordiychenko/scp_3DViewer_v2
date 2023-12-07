#ifndef SCP_3DVIEWER_V2_COMMAND_COMMAND_H
#define SCP_3DVIEWER_V2_COMMAND_COMMAND_H

namespace scp {

class Command {
 public:
  Command() = default;
  Command(const Command&) = delete;
  Command& operator=(const Command&) = delete;
  Command(Command&&) = delete;
  Command& operator=(Command&&) = delete;
  virtual ~Command() = default;
  virtual void Redo() = 0;
  virtual void Undo() = 0;
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_COMMAND_H
