#include "Enemy.h"

#include <string>

#include "DxLib.h"

using utility::Direction1D;

namespace actor {
    Enemy::Enemy() :
        position( window::WIDTH / 2, 200 ), progress( 0.0f ), beginPosition( position.X() ), state( AIState::Wait ), previousState( AIState::MoveLeft ) {
        handle = LoadGraph( enemy::PATH.c_str() );

        timeManager = times::TimeManager::Instance();
    }

    void Enemy::Control() {
        switch ( state ) {
            case AIState::Wait:
                if ( Wait( 3.0f ) ) {
                    beginPosition = position.X();
                    ChangeAIState( ( previousState == AIState::MoveRight ) ? AIState::MoveLeft : AIState::MoveRight );
                }
                break;
            case AIState::MoveLeft:
                if ( MoveTo( Direction1D::Left, 100 ) ) ChangeAIState( AIState::Return, true );
                break;
            case AIState::MoveRight:
                if ( MoveTo( Direction1D::Right, 100 ) ) ChangeAIState( AIState::Return, true );
                break;
            case AIState::Return:
                if ( Return() ) ChangeAIState( AIState::Wait );
                break;
            default: break;
        }
    }

    void Enemy::Draw() {
        // 現在の行動を表示
        switch ( state ) {
            case AIState::Wait: printfDx( "state : Wait" ); break;
            case AIState::MoveLeft: printfDx( "state : MoveLeft" ); break;
            case AIState::MoveRight: printfDx( "state : MoveRight" ); break;
            case AIState::Return: printfDx( "state : Return " ); break;
            default: break;
        }

        DrawGraphF( position.X(), position.Y(), handle, true );
    }

    bool Enemy::Wait( auto period ) {
        // progressに待機時間を加算
        progress += timeManager.lock()->DeltaTime();

        return progress >= period;
    }

    bool Enemy::MoveTo( Direction1D moveDir, auto distance ) {
        auto moveAmount = SPEED * timeManager.lock()->DeltaTime();
        position.AddX( ( moveDir == Direction1D::Left ) ? -moveAmount : moveAmount );
        // progressに移動距離を加算
        progress += moveAmount;

        return progress >= distance;
    }

    bool Enemy::Return() {
        auto moveAmount = SPEED * timeManager.lock()->DeltaTime();
        auto moveDir = ( position.X() > beginPosition ) ? Direction1D::Left : Direction1D::Right;
        // 平行移動のみなのでXだけ処理
        position.AddX( ( moveDir == Direction1D::Left ) ? -moveAmount : moveAmount );

        if ( ( moveDir == Direction1D::Left ) ? position.X() <= beginPosition : position.X() >= beginPosition ) {
            // 移動が完了したら位置を調整する
            position.SetX( beginPosition );
            return true;
        }

        return false;
    }
}  // namespace actor