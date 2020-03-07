#include <example-module/example-module.h>

#include <iostream>

namespace example_module {

ExampleClass::ExampleClass(QObject* const parent) : QObject(parent)
{
	std::cout << "TEST" << std::endl;
}
	
} // namespace module
