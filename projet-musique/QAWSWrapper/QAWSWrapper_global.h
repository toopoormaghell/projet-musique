#ifndef QAWSWRAPPER_GLOBAL_H
#define QAWSWRAPPER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QAWSWRAPPER_LIBRARY)
#  define QAWSWRAPPERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QAWSWRAPPERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QAWSWRAPPER_GLOBAL_H
