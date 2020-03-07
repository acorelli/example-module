#ifndef EXAMPLE_MODULE_H
#define EXAMPLE_MODULE_H

#include <example-module/export.h>

#include <QObject>

namespace example_module{

class EXAMPLE_MODULE_EXPORT ExampleClass: public QObject {
	Q_OBJECT

public:
	/**
	 * Constructor
	 * @param parent a pointer to the object
	 */
	explicit ExampleClass(QObject* const parent = nullptr);
	
};

} // namespace example_module

#endif // EXAMPLE_MODULE_H
