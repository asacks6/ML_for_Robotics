
#ifndef CV_BRIDGE2_EXPORT_H
#define CV_BRIDGE2_EXPORT_H

#ifdef CV_BRIDGE2_STATIC_DEFINE
#  define CV_BRIDGE2_EXPORT
#  define CV_BRIDGE2_NO_EXPORT
#else
#  ifndef CV_BRIDGE2_EXPORT
#    ifdef cv_bridge2_EXPORTS
        /* We are building this library */
#      define CV_BRIDGE2_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CV_BRIDGE2_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef CV_BRIDGE2_NO_EXPORT
#    define CV_BRIDGE2_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef CV_BRIDGE2_DEPRECATED
#  define CV_BRIDGE2_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef CV_BRIDGE2_DEPRECATED_EXPORT
#  define CV_BRIDGE2_DEPRECATED_EXPORT CV_BRIDGE2_EXPORT CV_BRIDGE2_DEPRECATED
#endif

#ifndef CV_BRIDGE2_DEPRECATED_NO_EXPORT
#  define CV_BRIDGE2_DEPRECATED_NO_EXPORT CV_BRIDGE2_NO_EXPORT CV_BRIDGE2_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CV_BRIDGE2_NO_DEPRECATED
#    define CV_BRIDGE2_NO_DEPRECATED
#  endif
#endif

#endif /* CV_BRIDGE2_EXPORT_H */
