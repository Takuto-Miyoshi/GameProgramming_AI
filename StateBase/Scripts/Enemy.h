#ifndef ENEMY_H
#define ENEMY_H

#include <memory>

#include "Definiton.h"
#include "TimeManager.h"

namespace actor {
    class Enemy {
       private:
        enum class AIState
        {
            Wait,  // 待機
            MoveLeft,  // 左へ移動
            MoveRight,  // 右へ移動
            Return,  // 元の位置に戻る
        };

       public:
        Enemy();

        ~Enemy() {}

       public:
        void Exec() {
            Control();
            Draw();
        }

       private:
        void Control();

        void Draw();

        /**
         * @brief 指定秒待つ
         * @param period 待つ秒数
         * @return 待機が終わったらtrue
         */
        bool Wait( auto period );

        /**
         * @brief 移動する
         * @param moveDir 移動する方向
         * @param distance 移動距離
         * @return 移動が完了したらtrue
         */
        bool MoveTo( utility::Direction1D moveDir, auto distance );

        /**
         * @brief beginPositionに戻る
         * @return 移動が完了したらtrue
         */
        bool Return();

        /**
         * @brief AIStateを変更する @n Stateが変わった時の処理も行う
         * @param next 次のAIState
         * @param updatePreviousState 前回のAIStateを更新するか
         */
        void ChangeAIState( AIState next, bool updatePreviousState = false ) {
            if ( updatePreviousState == true ) previousState = state;
            state = next;
            progress = 0.0f;
        }

       private:
        std::weak_ptr<times::TimeManager> timeManager;

        std::int32_t handle;
        utility::Position position;
        const std::int16_t SPEED = 150;  // 1秒でこれだけ進む

        float progress;  // AIの進行度
        float beginPosition;  // 前回の位置

        AIState state;
        AIState previousState;
    };
}  // namespace actor

#endif  // !ENEMY_H
