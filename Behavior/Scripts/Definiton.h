#ifndef DEFINITION_H
#define DEFINITION_H

#include <cstdint>
#include <string>

namespace window {
    constexpr std::int16_t WIDTH = 640;
    constexpr std::int16_t HEIGHT = 480;
}  // namespace window

namespace actor {
    namespace enemy {
        const std::string PATH = "Sprites/Enemy.png";
    }
}  // namespace actor

namespace utility {
    enum class Direction1D
    {
        Left,
        Right
    };

    struct Position {
       public:
        Position() :
            x( 0.0f ), y( 0.0f ) {}

        explicit Position( float defaultX, float defaultY ) :
            x( defaultX ), y( defaultY ) {}

       public:
        float X() const { return x; }
        void SetX( auto set ) { x = set; }
        void AddX( auto add ) { x += add; }
        float Y() const { return y; }
        void SetY( auto set ) { y = set; }
        void AddY( auto add ) { y += add; }

       private:
        float x;
        float y;
    };
}  // namespace utility

#endif  // !DEFINITION_H
