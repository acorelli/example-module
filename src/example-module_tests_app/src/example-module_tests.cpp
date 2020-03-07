#include <gtest/gtest.h>
#include <QApplication>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);

	return RUN_ALL_TESTS();
}
