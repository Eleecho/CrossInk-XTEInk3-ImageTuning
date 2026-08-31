#pragma once

#include <functional>
#include <string>

#include "MappedInputManager.h"
#include "activities/Activity.h"

class BmpViewerActivity final : public Activity {
 public:
  BmpViewerActivity(GfxRenderer& renderer, MappedInputManager& mappedInput, std::string filePath);

  void onEnter() override;
  void onExit() override;
  void loop() override;

 private:
  void loadSiblingImages();
  // Redecodes the PNG once per grayscale bit plane (BW/LSB/MSB) rather than
  // holding extra plane buffers, since C3 targets (X3/X4) have no PSRAM
  // headroom to spare. TODO: on PSRAM-equipped boards (X4 Pro), a single
  // decode that writes all 3 planes at once would trade ~100KB of scratch
  // RAM for avoiding the 3x re-inflate cost - gate behind the board's PSRAM
  // capability macro if this becomes a real complaint, after checking actual
  // heap headroom.
  bool renderPngImage();
  void doSetSleepCover();

  std::string filePath;
  std::vector<std::string> siblingImages;
  int currentImageIndex = -1;
};
