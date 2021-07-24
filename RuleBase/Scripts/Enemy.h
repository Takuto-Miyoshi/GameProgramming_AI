#ifndef ENEMY_H
#define ENEMY_H

#include <memory>

#include "Definiton.h"
#include "ItemManager.h"

namespace actor {
    class Enemy {
       private:
        enum class AIState
        {
            Wait,
            Rove,
            GoToItem,
        };

        enum class CollisionType
        {
            Me,  // 自分自身
            CircleArea,  // 円形の捜索範囲
            FanShapeArea,  // 扇形の捜索範囲
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

        // ルールを取得
        AIState SelectRule();

        // 待機
        void Wait();

        // うろうろする
        void Rove();

        // 目的地へ向かう
        void GoToDestination();

        // ターゲットと当たっているか取得する
        bool HitTo( CollisionType type, utility::Vector2 target, float targetRadius );

       private:
        std::weak_ptr<times::TimeManager> timeManager;
        std::weak_ptr<item::ItemManager> itemManager;

        std::int32_t handle;
        const std::string PATH = "Sprites/Enemy.png";
        utility::Vector2 position;
        float angle;
        const float SPEED = 300.0f;
        const float RADIUS = 64.0f;
        float progress;

        const float SEARCH_AREA_CIRCLE_RADIUS = 130.0f;  // 円形の捜索範囲
        const float SEARCH_AREA_FAN_RADIUS = 200.0f;  // 扇形の捜索範囲
        const float SEARCH_AREA_FAN_DEGREE = 100.0f;  // 扇の角度

        AIState state;
        const float WAIT_TIME = 3.0f;  // 待機時間

        utility::Vector2 destination;
    };
}  // namespace actor

#endif  // !ENEMY_H
