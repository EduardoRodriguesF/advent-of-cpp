#include <gtest/gtest.h>
#include "coords/coords.h"

TEST(CoordsTest, Add) {
	Pos a = Pos(2, 1);
	Pos b = Pos(1, 0);

	EXPECT_EQ(Pos(3, 1), a + b);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
