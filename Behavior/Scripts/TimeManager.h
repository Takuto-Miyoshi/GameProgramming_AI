#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <cstdint>

#include "DxLib.h"
#include "Singleton.h"

namespace times {
    class TimeManager : public utility::Singleton<TimeManager> {
       public:
        TimeManager() {}

        ~TimeManager() {}

       public:
        // 計測開始
        void Begin() { timeBegin = GetNowCount(); }

        // 時間系の処理
        void Update() {
            timeEnd = GetNowCount();
            deltaTime = ( timeEnd - timeBegin ) / 1000.0f;
        }

        // 前回の処理時間を取得
        float DeltaTime() const { return deltaTime; }

       private:
        std::int32_t timeBegin;
        std::int32_t timeEnd;
        float deltaTime;
    };
}  // namespace times

#endif  // !TIME_MANAGER_H
