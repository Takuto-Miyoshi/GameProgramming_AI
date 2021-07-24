#include "Enemy.h"

#include <string>

#include "DxLib.h"
#include "ItemManager.h"

using utility::Direction1D;

namespace actor {
    Enemy::Enemy() :
        position( window::WIDTH / 2, 200 ), state( AIState::Wait ), progress( 0.0f ), destination( 0, 0 ), angle( 0.0f ) {
        handle = LoadGraph( PATH.c_str() );

        timeManager = times::TimeManager::Instance();
        itemManager = item::ItemManager::Instance();
    }

    void Enemy::Control() {
        switch ( SelectRule() ) {
            case AIState::Wait: Wait(); break;
            case AIState::Rove: Rove(); break;
            case AIState::GoToItem: GoToDestination(); break;
            default: break;
        }

        // 画面外に移動しないようにする
        if ( position.X() < 0 ) {
            position.SetX( 0 );
            state = AIState::Rove;
        }
        else if ( position.X() > 600 ) {
            position.SetX( 600 );
            state = AIState::Rove;
        }
        if ( position.Y() < 0 ) {
            position.SetY( 0 );
            state = AIState::Rove;
        }
        else if ( position.Y() > 400 ) {
            position.SetY( 400 );
            state = AIState::Rove;
        }
    }

    void Enemy::Draw() {
        // 円形の当たり判定
        DrawCircle( position.X(), position.Y(), SEARCH_AREA_CIRCLE_RADIUS, GetColor( 255, 0, 0 ), FALSE );

        DrawRotaGraphFastF( position.X(), position.Y(), 1.0f, angle, handle, TRUE );
    }

    Enemy::AIState Enemy::SelectRule() {
        if ( state == AIState::Wait ) return state;

        auto item = itemManager.lock()->GetNearItemPosition( position );
        if ( HitTo( CollisionType::Me, item->Position(), item->RADIUS ) ) {
            // 接触しているアイテムを削除してもらう
            itemManager.lock()->EraseTo( item );
            state = AIState::Wait;
        }
        else if ( HitTo( CollisionType::FanShapeArea, item->Position(), item->RADIUS )
                  || HitTo( CollisionType::CircleArea, item->Position(), item->RADIUS )
                         && state != AIState::GoToItem ) {
            // アイテムへ向かう
            destination = item->Position();
            state = AIState::GoToItem;
        }

        return state;
    }

    void Enemy::Wait() {
        // 一定時間後にうろうろする
        progress += timeManager.lock()->DeltaTime();
        if ( progress > WAIT_TIME ) state = AIState::Rove;
    }

    void Enemy::Rove() {
        // 適当に回転
        if ( rand() % 30 == 0 ) angle += 0.5f;
        angle += ( rand() % 2 == 0 ) ? 0.1f : -0.1f;
        // 移動
        position += utility::Vector2::ToAzimuthVector( angle ) * SPEED * timeManager.lock()->DeltaTime();
    }

    void Enemy::GoToDestination() {
        angle = position.Radian( destination );
        position += utility::Vector2::ToAzimuthVector( angle ) * SPEED * timeManager.lock()->DeltaTime();
    }

    bool Enemy::HitTo( CollisionType type, utility::Vector2 target, float targetRadius ) {
        switch ( type ) {
            case CollisionType::Me: return RADIUS >= position.Distance( target ) - targetRadius;
            case CollisionType::CircleArea: return SEARCH_AREA_CIRCLE_RADIUS >= position.Distance( target ) - targetRadius;
            case CollisionType::FanShapeArea:
                auto toTarget = target - position;  // 二点間のベクトル
                if ( toTarget.Length() < SEARCH_AREA_FAN_RADIUS ) return false;
                auto arcDir = utility::Vector2( 1.0f, 0.0f );
                auto rotateArcDir = utility::Vector2(  // 回転させたベクトル
                    arcDir.X() * cosf( angle ) + arcDir.Y() * -sinf( angle ),
                    arcDir.X() * sinf( angle ) + arcDir.Y() * cosf( angle ) );
                auto dot = toTarget.Normalized().X() * rotateArcDir.X() + toTarget.Normalized().Y() + rotateArcDir.Y();  // 内積
                return cosf( utility::Vector2::ToRadian( SEARCH_AREA_FAN_DEGREE / 2.0f ) ) <= dot;
        }

        return false;
    }

}  // namespace actor