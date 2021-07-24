#ifndef DEFINITION_H
#define DEFINITION_H

#include <cmath>
#include <cstdint>
#include <string>

constexpr float PI = 3.14159f;

namespace window {
    constexpr std::int16_t WIDTH = 640;
    constexpr std::int16_t HEIGHT = 480;
}  // namespace window

namespace utility {
    enum class Direction1D
    {
        Left,
        Right
    };

    struct Vector2 {
       public:
        Vector2() :
            x( 0.0f ), y( 0.0f ) {}

        explicit Vector2( float defaultX, float defaultY ) :
            x( defaultX ), y( defaultY ) {}

       public:
        float X() const { return x; }
        void SetX( auto set ) { x = set; }
        void AddX( auto add ) { x += add; }
        float Y() const { return y; }
        void SetY( auto set ) { y = set; }
        void AddY( auto add ) { y += add; }

        // 長さを取得
        float Length() const { return sqrtf( x * x + y * y ); }

        // 正規化したベクトルを取得
        Vector2 Normalized() const { return Vector2( x / Length(), y / Length() ); }

        // ターゲットとの距離を取得
        float Distance( Vector2 target ) const { return Vector2( target - Vector2( x, y ) ).Length(); }

        // ターゲットへの向きを取得
        float Radian( Vector2 target ) const {
            auto vector = Vector2( x, y ) - target;
            return atan2( vector.y, vector.x ) + PI;
        }

        // ラジアン角を角度へ変換
        static float ToDegree( float radian ) {
            return 180 / PI * radian;
        }

        // 角度をラジアン角へ変換
        static float ToRadian( float degree ) {
            return degree * ( PI / 180.0f );
        }

        // ラジアン角を方位ベクトルへ変換
        static Vector2 ToAzimuthVector( float radian ) {
            return Vector2( cosf( radian ), sin( radian ) ).Normalized();
        }

       public:
        Vector2 operator-( Vector2 vector ) const { return Vector2( x - vector.X(), y - vector.Y() ); }
        Vector2 operator*( auto value ) const { return Vector2( x * value, y * value ); }
        void operator+=( Vector2 position ) {
            x += position.X();
            y += position.Y();
        }

       private:
        float x;
        float y;
    };
}  // namespace utility

#endif  // !DEFINITION_H
