#ifndef HELPERS_GLOBAL_H
#define HELPERS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HELPERS_LIBRARY)
#  define HELPERSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HELPERSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HELPERS_GLOBAL_H
