#ifndef JWDB_GLOBAL_H
#define JWDB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(JWDB_LIBRARY)
#  define JWDBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define JWDBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // JWDB_GLOBAL_H
