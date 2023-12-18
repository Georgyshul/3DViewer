#ifndef DEFINES_H
#define DEFINES_H

#include <QString>

namespace Settings {
inline static const QString PROJECTION = "projection";
inline static const QString DISPLAY_METHOD = "displayMethod";
inline static const QString BACKGROUND_COLOR = "backgroundColor";
inline static const QString EDGES_COLOR = "edgesColor";
inline static const QString EDGES_TYPE = "edgesType";
inline static const QString EDGES_THICKNESS = "edgesThickness";
inline static const QString VERTICES_COLOR = "verticesColor";
inline static const QString VERTICES_SIZE = "verticesSize";
inline static const QString CURRENT_DIR = "currentDir";

enum Projection {
  central,
  parallel,
};

enum DisplayMethod { none, circle, square };

enum Color { white, black, red, blue, green };

enum EdgesType { solid, dashed };

enum EdgesThickness { thin, normal, thick };

enum VerticesSize { little, pepe, big };

namespace Default {
inline static const int PROJECTION = Projection::central;
inline static const int DISPLAY_METHOD = DisplayMethod::none;
inline static const int BACKGROUND_COLOR = Color::black;
inline static const int EDGES_COLOR = Color::red;
inline static const int EDGES_TYPE = EdgesType::solid;
inline static const int EDGES_THICKNESS = EdgesThickness::thin;
inline static const int VERTICES_COLOR = Color::red;
inline static const int VERTICES_SIZE = VerticesSize::little;
}  // namespace Default
}  // namespace Settings

#endif  // DEFINES_H
