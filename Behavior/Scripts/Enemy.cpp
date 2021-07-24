#include "Enemy.h"

#include <string>

#include "DxLib.h"

using utility::Direction1D;

namespace actor {
    Enemy::Enemy() :
        position( window::WIDTH / 2, 200 ) {
        handle = LoadGraph( enemy::PATH.c_str() );

        timeManager = times::TimeManager::Instance();
    }

    void Enemy::Control() {
    }

    void Enemy::Draw() {
        DrawGraphF( position.X(), position.Y(), handle, true );
    }
}  // namespace actor