#ifndef SCP_3DVIEWER_V2_ENUMS_H
#define SCP_3DVIEWER_V2_ENUMS_H

namespace scp {

enum ProjectionType { kParallel, kCentral };
enum LineType { kSolid, kDashed };
enum VerticeType { kNone, kCircle, kSquare };
enum EventType {
  kRenderFile,
  kSetAffine,
  kAppearanceChange,
  kSetProjectionType,
  kLoadSettings
};

}  // namespace scp
#endif  // SCP_3DVIEWER_V2_ENUMS_H
