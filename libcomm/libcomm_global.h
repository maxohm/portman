#ifndef LIBCOMM_GLOBAL_H
#define LIBCOMM_GLOBAL_H
//
#include <QtCore/qglobal.h>

#if defined(LIBCOMM_LIBRARY)
#  define LIBCOMMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBCOMMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif //LIBCOMM_GLOBAL_H
