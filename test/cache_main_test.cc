#include "../src/include/cache_main.h"
#include <gtest/gtest.h>

TEST(CacheTest, GetNonExistentKeyReturnsEmptyString) {
    Cache cache(10);
    EXPECT_EQ(cache.get(1), "");
}

TEST(CacheTest, PutAndGet) {
    Cache cache(10);
    cache.put(1, "value1");
    cache.put(2, "value2");
    EXPECT_EQ(cache.get(1), "value1");
    EXPECT_EQ(cache.get(2), "value2");
}

TEST(CacheTest, PutWithSameKeyOverwritesValue) {
    Cache cache(10);
    cache.put(1, "value1");
    cache.put(1, "value2");
    EXPECT_EQ(cache.get(1), "value2");
}

TEST(CacheTest, PutMoreThanCapacityEvictsLeastRecentlyUsed) {
    Cache cache(2);
    cache.put(1, "value1");
    cache.put(2, "value2");
    cache.put(3, "value3");
    EXPECT_EQ(cache.get(1), "");
    EXPECT_EQ(cache.get(2), "value2");
    EXPECT_EQ(cache.get(3), "value3");
}

TEST(CacheTest, PutDirtyMarksKeyAsDirty) {
    Cache cache(10);
    cache.put(1, "value1", true);
    EXPECT_TRUE(cache.is_dirty(1));
}

TEST(CacheTest, PutCleanMarksKeyAsNotDirty) {
    Cache cache(10);
    cache.put(1, "value1", true);
    cache.put(1, "value1", false);
    EXPECT_FALSE(cache.is_dirty(1));
}