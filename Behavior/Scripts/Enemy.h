#ifndef ENEMY_H
#define ENEMY_H

#include <memory>

#include "Definiton.h"
#include "TimeManager.h"

namespace actor {
    class Enemy {
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

       private:
        std::weak_ptr<times::TimeManager> timeManager;

        std::int32_t handle;
        utility::Position position;
        const std::int16_t SPEED = 150;  // 1秒でこれだけ進む
    };
}  // namespace actor

#endif  // !ENEMY_H
