/*
 *  Copyright 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_API_MEDIASTREAMTRACK_H_
#define WEBRTC_API_MEDIASTREAMTRACK_H_

#include <string>

#include "webrtc/api/mediastreaminterface.h"
#include "webrtc/api/notifier.h"

namespace webrtc {

// MediaTrack implements the interface common to AudioTrackInterface and
// VideoTrackInterface.
template <typename T>
class MediaStreamTrack : public Notifier<T> {
 public:
  typedef typename T::TrackState TypedTrackState;

  virtual std::string id() const { return id_; }
  virtual MediaStreamTrackInterface::TrackState state() const {
    return state_;
  }
  virtual bool enabled() const { return enabled_; }
  virtual bool set_enabled(bool enable) {
    bool fire_on_change = (enable != enabled_);
    enabled_ = enable;
    if (fire_on_change) {
      Notifier<T>::FireOnChanged();
    }
    return fire_on_change;
  }
  virtual bool set_state(MediaStreamTrackInterface::TrackState new_state) {
    bool fire_on_change = (state_ != new_state);
    state_ = new_state;
    if (fire_on_change)
      Notifier<T>::FireOnChanged();
    return true;
  }

 protected:
  explicit MediaStreamTrack(const std::string& id)
      : enabled_(true),
        id_(id),
        state_(MediaStreamTrackInterface::kInitializing) {
  }

 private:
  bool enabled_;
  std::string id_;
  MediaStreamTrackInterface::TrackState state_;
};

}  // namespace webrtc

#endif  // WEBRTC_API_MEDIASTREAMTRACK_H_