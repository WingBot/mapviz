// *****************************************************************************
//
// Copyright (c) 2014, Southwest Research Institute® (SwRI®)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Southwest Research Institute® (SwRI®) nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *****************************************************************************

#ifndef MAPVIZ_PLUGINS_MULTIRES_IMAGE_PLUGIN_H_
#define MAPVIZ_PLUGINS_MULTIRES_IMAGE_PLUGIN_H_

// C++ standard libraries
#include <string>

// Boost libraries
#include <boost/filesystem.hpp>

#include <mapviz/mapviz_plugin.h>

// QT libraries
#include <QGLWidget>
#include <QObject>
#include <QWidget>

#include <mapviz/map_canvas.h>
#include <multires_image/tile_set.h>

#include <mapviz_plugins/multires_view.h>

// QT autogenerated files
#include "ui_multires_config.h"

namespace mapviz_plugins
{
  class MultiresImagePlugin : public mapviz::MapvizPlugin
  {
    Q_OBJECT

  public:
    MultiresImagePlugin();
    virtual ~MultiresImagePlugin();

    bool Initialize(QGLWidget* canvas);
    void Shutdown() {}

    void Draw(double x, double y, double scale);

    void Transform();

    void LoadConfig(const YAML::Node& node, const std::string& path);
    void SaveConfig(YAML::Emitter& emitter, const std::string& path);

    QWidget* GetConfigWidget(QWidget* parent);

  protected:
    void PrintError(const std::string& message);
    void PrintInfo(const std::string& message);
    void PrintWarning(const std::string& message);

  protected Q_SLOTS:
    void SelectFile();
    void AcceptConfiguration();

  private:
    bool     loaded_;
    double center_x_;
    double center_y_;

    multires_image::TileSet* tile_set_;
    MultiresView* tile_view_;

    Ui::multires_config ui_;
    QWidget* config_widget_;

    swri_transform_util::Transform transform_;
    swri_transform_util::Transform inverse_transform_;

    bool transformed_;

    void GetCenterPoint(double x, double y);

    boost::filesystem::path MakePathRelative(
      boost::filesystem::path path,
      boost::filesystem::path base);
  };
}

#endif  // MAPVIZ_PLUGINS_MULTIRES_IMAGE_PLUGIN_H_
