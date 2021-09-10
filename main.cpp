#include "test_timer.h"

int main() {

	UnitTest::TestTimer test;

	test.addData();
	test.waitEmpty();

	return 0;
}
