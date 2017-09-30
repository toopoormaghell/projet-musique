#ifndef BDD_GLOBAL_H
#define BDD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BDD_LIBRARY)
#  define BDDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BDDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BDD_GLOBAL_H
