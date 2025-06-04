#include <gtest/gtest.h>

#include <anybotics_coding_challenge/ElevationMap.hpp>

using namespace anybotics_coding_challenge;

static ElevationMap& getFreshMap()
{
    // Create 5 cells
    ElevationMap& m = ElevationMap::getInstance(1.0, 0.2);
    m.clear();
    return m;
}

TEST(ElevationMapTest, BasicInsertAndClear)
{
    ElevationMap& m = getFreshMap();
    EXPECT_EQ(m.size(), 5);

    // All cells are -1
    for (int i = 0; i < m.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(m.getMap()[i], -1.0);
    }

    std::vector<double> v{0.5, -1.0, 1.5, 2.0, -1.0};
    m.updateHeights(v);

    EXPECT_DOUBLE_EQ(m.getMap()[0], 0.5);
    EXPECT_DOUBLE_EQ(m.getMap()[1], -1.0);
    EXPECT_DOUBLE_EQ(m.getMap()[2], 1.5);
    EXPECT_DOUBLE_EQ(m.getMap()[3], 2.0);
    EXPECT_DOUBLE_EQ(m.getMap()[4], -1.0);

    // Clear all
    m.clear();
    for (int i = 0; i < m.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(m.getMap()[i], -1.0);
    }
}

TEST(ElevationMapTest, MinMaxQueries)
{
    ElevationMap& m = getFreshMap();

    std::vector<double> v{0.5, 2.0, 1.0, -1.0, 3.0};
    m.updateHeights(v);

    EXPECT_DOUBLE_EQ(m.getMin(0, 2), 0.5);
    EXPECT_DOUBLE_EQ(m.getMax(0, 2), 2.0);

    EXPECT_DOUBLE_EQ(m.getMin(2, 4), 1.0);
    EXPECT_DOUBLE_EQ(m.getMax(2, 4), 3.0);

    // alls hould be -1
    m.clear();
    EXPECT_DOUBLE_EQ(m.getMin(1, 3), -1.0);
    EXPECT_DOUBLE_EQ(m.getMax(1, 3), -1.0);
}

TEST(ElevationMapTest, ShiftForwardAndInsert)
{
    ElevationMap& m = getFreshMap();

    std::vector<double> init{0.0, 0.5, 1.0, 1.5, 2.0};
    m.updateHeights(init);

    std::vector<double> dummyNew{-1.0, -1.0, -1.0, -1.0, -1.0};
    m.updateHeights(dummyNew, 2);

    EXPECT_DOUBLE_EQ(m.getMap()[0], 1.0);
    EXPECT_DOUBLE_EQ(m.getMap()[1], 1.5);
    EXPECT_DOUBLE_EQ(m.getMap()[2], 2.0);
    EXPECT_DOUBLE_EQ(m.getMap()[3], -1.0);
    EXPECT_DOUBLE_EQ(m.getMap()[4], -1.0);

    // only idx 3 and 4
    std::vector<double> newVals{-1.0, -1.0, -1.0, 0.2, 0.4};
    m.updateHeights(newVals, 0);

    EXPECT_DOUBLE_EQ(m.getMap()[3], 0.2);
    EXPECT_DOUBLE_EQ(m.getMap()[4], 0.4);
}

TEST(ElevationMapTest, ShiftBackward)
{
    ElevationMap& m = getFreshMap();
    std::vector<double> init{0.0, 0.5, 1.0, 1.5, 2.0};
    m.updateHeights(init);
    std::vector<double> dummyNew{-1.0, -1.0, -1.0, -1.0, -1.0};
    m.updateHeights(dummyNew, -2);

    EXPECT_DOUBLE_EQ(m.getMap()[0], -1.0);
    EXPECT_DOUBLE_EQ(m.getMap()[1], -1.0);
    EXPECT_DOUBLE_EQ(m.getMap()[2], 0.0);
    EXPECT_DOUBLE_EQ(m.getMap()[3], 0.5);
    EXPECT_DOUBLE_EQ(m.getMap()[4], 1.0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}