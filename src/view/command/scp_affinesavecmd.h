#ifndef SCP_3DVIEWER_V2_COMMAND_AFFINESAVECMD_H
#define SCP_3DVIEWER_V2_COMMAND_AFFINESAVECMD_H

#include "../../utils/scp_affinedata.h"
#include "scp_command.h"

namespace scp {

class AffineSaveCmd : public Command {
 public:
  AffineSaveCmd() = delete;
  AffineSaveCmd(AffineData old_data, AffineData new_data, Ui::View* ui);
  AffineSaveCmd(const AffineSaveCmd&) = delete;
  AffineSaveCmd& operator=(const AffineSaveCmd&) = delete;
  AffineSaveCmd(AffineSaveCmd&&) = delete;
  AffineSaveCmd& operator=(AffineSaveCmd&&) = delete;
  ~AffineSaveCmd() = default;
  void Undo() override;
  void Redo() override;
  static AffineData get_old();

 private:
  Ui::View* ui_;
  inline static AffineData prev_old = AffineData();
  AffineData new_data_, old_data_;
  void Transform(AffineData& data);
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_COMMAND_AFFINESAVECMD_H
