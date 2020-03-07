#ifndef EXAMPLE_MODULE_VERSION_H
#define EXAMPLE_MODULE_VERSION_H

#include <example-module/export.h>

#include <sstream>
#include <string>

namespace example_module {

/// The format in which to return the project version.
enum VersionFormat {
	MajorMinorPatchTweak = 1, ///< Return as major.minor.patch.tweak
	MajorMinorPatch = 2,      ///< Return as major.minor.patch
	MajorMinor = 3,           ///< Return as major.minor
	Major = 4,                ///< Return as major
};

/**
 * Gets the project version.
 */
namespace Version {

/**
 * Constructs the default window title as a string
 * @param format the VersionFormat enum that specifies how much information should be displayed
 * @return the default window title
 */
EXAMPLE_MODULE_EXPORT std::string defaultWindowTitle( const VersionFormat format = VersionFormat::MajorMinorPatchTweak );


/**
 * Gets the major component of the version number.
 * @return the major component of the version number
 */
EXAMPLE_MODULE_EXPORT std::string major();

/**
 * Gets the minor component of the version number.
 * @return the minor component of the version number
 */
EXAMPLE_MODULE_EXPORT std::string minor();

/**
 * Gets the patch component of the version number.
 * @return the patch component of the version number
 */
EXAMPLE_MODULE_EXPORT std::string patch();

/**
 * Gets the tweak component of the version number.
 * @return the tweak component of the version number
 */
EXAMPLE_MODULE_EXPORT std::string tweak();

/**
 * Gets the version number in the format requested.
 * @param format the VersionFormat enum that specifies how much information should be displayed
 * @return the version number in the format requested
 */
EXAMPLE_MODULE_EXPORT std::string string(const VersionFormat format = VersionFormat::MajorMinorPatchTweak);


/**
 * Gets the long git commit hash of the current build's branch
 * @return the long git commit hash of the current build's branch
 */
EXAMPLE_MODULE_EXPORT std::string getCommitLongHash();

/**
 * Gets the abbreviated git commit hash of the current build's branch
 * @return the abbreviated git commit hash of the current build's branch
 */
EXAMPLE_MODULE_EXPORT std::string getCommitShortHash();

} // namespace Version
} // namespace example_module

#endif // EXAMPLE_MODULE_VERSION_H
