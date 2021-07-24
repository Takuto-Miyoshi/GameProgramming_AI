#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <algorithm>
#include <memory>
#include <vector>

#include "Definiton.h"
#include "Item.h"
#include "Singleton.h"
#include "TimeManager.h"

namespace item {
    class ItemManager : public utility::Singleton<ItemManager> {
       public:
        ItemManager() :
            itemList( std::vector<std::shared_ptr<Item>>() ), generateTimer( 0.0f ) {
            timeManager = times::TimeManager::Instance();
        }
        ~ItemManager() {}

       public:
        // 一番近いアイテムの位置と当たり判定の半径を取得
        std::shared_ptr<Item> GetNearItemPosition( utility::Vector2 from ) {
            if ( itemList.empty() ) return std::make_shared<Item>( utility::Vector2( -10000.0f, -10000.0f ) );

            std::weak_ptr<Item> result = std::make_shared<Item>();
            float minDistance = 10000.0f;

            std::for_each( itemList.begin(), itemList.end(), [&result, &minDistance, from]( auto element ) {
                auto distance = element->Position().Distance( from );
                if ( distance < minDistance ) {
                    result = element;
                    minDistance = distance;
                }
            } );
            return result.lock();
        }

        void Update() {
            Generate();
            std::for_each( itemList.begin(), itemList.end(), []( auto element ) { element->Draw(); } );
        }

        // アイテムリストから要素を探して削除する
        void EraseTo( std::weak_ptr<Item> target ) {
            itemList.erase( std::find( itemList.begin(), itemList.end(), target.lock() ) );
        }

       private:
        // 一定時間ごとにアイテムを生成
        void Generate() {
            if ( itemList.size() >= ITEM_MAX ) return;
            generateTimer += timeManager.lock()->DeltaTime();
            if ( generateTimer > GENERATE_INTERVAL ) {
                itemList.push_back( std::make_shared<Item>() );
                generateTimer = 0.0f;
            }
        }

       private:
        std::weak_ptr<times::TimeManager> timeManager;

        std::vector<std::shared_ptr<Item>> itemList;  // アイテムリスト
        float generateTimer;
        const float GENERATE_INTERVAL = 5.0f;
        const int32_t ITEM_MAX = 5;  // アイテムの最大数
    };
}  // namespace item

#endif  // !ITEM_MANAGER_H
