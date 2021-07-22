#ifndef DEFINITION_H
#define DEFINITION_H

#include <cstdint>

namespace window {
    constexpr std::int16_t WIDTH = 640;
    constexpr std::int16_t HEIGHT = 480;
}  // namespace window

struct Position {
   public:
    Position( float defaultX, float defaultY ) :
        x( defaultX ), y( defaultY ) {}

   public:
    float X() const { return x; }
    void SetX( float set ) { x = set; }
    float Y() const { return y; }
    void SetY( float set ) { y = set; }

   private:
    float x;
    float y;
};

#endif  // !DEFINITION_H
