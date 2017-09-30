/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_SENSORS_CAMERA_CAMERASENSOR_HH_
#define IGNITION_SENSORS_CAMERA_CAMERASENSOR_HH_

#include <memory>

#include <ignition/common/Time.hh>
#include <ignition/math/Pose3.hh>
#include <ignition/rendering/Camera.hh>
#include <ignition/sensors/camera/Export.hh>
#include <ignition/sensors/Sensor.hh>
#include <ignition/msgs.hh>
#include <sdf/sdf.hh>

namespace ignition
{
  namespace sensors
  {
    /// \brief forward declarations
    class CameraSensorPrivate;

    /// \brief Camera Sensor Class
    ///
    ///   This class creates images from an ignition rendering scene. The scene
    ///   must be created in advance and given to Manager::Init().
    ///   It offers both an ignition-transport interface and a direct C++ API
    ///   to access the image data. The API works by setting a callback to be
    ///   called with image data.
    class IGNITION_SENSORS_CAMERA_VISIBLE CameraSensor : public Sensor
    {
      /// \brief constructor
      public: CameraSensor();

      /// \brief destructor
      public: virtual ~CameraSensor();

      /// \brief Force the sensor to generate data
      /// \param[in] _now The current time
      /// \return true if the update was successfull
      public: virtual bool Update(const common::Time &_now) override;

      /// \brief Load the sensor with SDF parameters.
      /// \param[in] _sdf SDF Sensor parameters.
      /// \return true if loading was successful
      public: virtual bool Load(sdf::ElementPtr _sdf) override;

      /// \brief Set a callback to be called when frame data is received
      ///
      ///   This callback will be called every time the camera produces image
      ///   data, but before that data is published to ignition transport.
      ///   Update() function will be blocked while the callback is running.
      /// \remark Do not block inside of the callback.
      /// \return true if the callback could be set
      public: bool SetImageCallback(std::function<
                  void(const ignition::msgs::ImageStamped &)> _callback);

      /// \brief Data pointer for private data
      /// \internal
      private: std::unique_ptr<CameraSensorPrivate> dataPtr;
    };
  }
}

#endif