#ifndef ITEM_H
#define ITEM_H

#include "Definiton.h"
#include "DxLib.h"

namespace item {
    class Item {
       public:
        Item() :
            position( rand() % ( window::WIDTH - 50 ), rand() % ( window::HEIGHT - 50 ) ) {
            handle = LoadGraph( PATH.c_str() );
        }

        Item( utility::Vector2 setPosition ) :
            position( setPosition ) {
            handle = LoadGraph( PATH.c_str() );
        }

        ~Item() {}

       public:
        void Draw() {
            DrawCircle( position.X(), position.Y(), RADIUS, GetColor( 0, 0, 255 ), FALSE );
            DrawRotaGraphFastF( position.X(), position.Y(), 1.0f, 0.0f, handle, TRUE );
        }

        utility::Vector2 Position() const { return position; }

       public:
        const float RADIUS = 32.0f;

       private:
        utility::Vector2 position;
        int32_t handle;
        const std::string PATH = "Sprites/Item.png";
    };
}  // namespace item

#endif  // !ITEM_H
