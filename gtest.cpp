#include <gtest/gtest.h>
#include "lib/AgencyTable.hpp"
#include "lib/PublishingMedia.hpp"
#include "lib/RadioStation.hpp"
#include "lib/TVCompany.hpp"

// Тест для проверки добавления и поиска агентств
TEST(AgencyTableTest, AddAndFindAgency) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    RadioStation* rs = new RadioStation("Radio1", "Music", "456", "St. Petersburg", {{"FM", "101.5"}, {"AM", "800"}});
    TVCompany* tv = new TVCompany("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");

    // Добавляем агентства в таблицу
    table.add(pm);
    table.add(rs);
    table.add(tv);

    // Проверяем, что агентства можно найти
    EXPECT_EQ(table.find("Print1"), pm);
    EXPECT_EQ(table.find("Radio1"), rs);
    EXPECT_EQ(table.find("TV1"), tv);

    // Удаляем агентства
    delete pm;
    delete rs;
    delete tv;
}

// Тест для проверки удаления агентств
TEST(AgencyTableTest, RemoveAgency) {
    AgencyTable table;

    // Создаем агентство
    PublishingMedia* pm = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);

    // Добавляем агентство в таблицу
    table.add(pm);

    // Удаляем агентство
    EXPECT_TRUE(table.remove("Print1"));

    // Проверяем, что агентство удалено
    EXPECT_EQ(table.find("Print1"), nullptr);

    // Удаляем агентство
    delete pm;
}

// Тест для проверки подсчета агентств по регионам
TEST(AgencyTableTest, CountAgenciesByRegion) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm1 = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    PublishingMedia* pm2 = new PublishingMedia("Print2", "News", "124", "Moscow", {"Tuesday", "Thursday"}, 15000);
    RadioStation* rs = new RadioStation("Radio1", "Music", "456", "St. Petersburg", {{"FM", "101.5"}, {"AM", "800"}});
    TVCompany* tv = new TVCompany("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");

    // Добавляем агентства в таблицу
    table.add(pm1);
    table.add(pm2);
    table.add(rs);
    table.add(tv);

    // Подсчитываем агентства по регионам
    auto regionCount = table.countAgenciesByRegion();

    // Проверяем количество агентств в каждом регионе
    EXPECT_EQ(regionCount["Moscow"], 2);
    EXPECT_EQ(regionCount["St. Petersburg"], 1);
    EXPECT_EQ(regionCount["Novosibirsk"], 1);

    // Удаляем агентства
    delete pm1;
    delete pm2;
    delete rs;
    delete tv;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
