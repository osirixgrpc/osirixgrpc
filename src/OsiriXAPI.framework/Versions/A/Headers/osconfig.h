/* include/osconfig.h.  Generated from osconfig.h.in by configure.  */
/* include/osconfig.h.in.  Generated from configure.in by autoheader.  */

#include "cfunix.h"

#ifndef OSCONFIG_H
#define OSCONFIG_H

/*
 ** Define enclosures for include files with C linkage (mostly system headers)
 */
#ifdef __cplusplus
#define BEGIN_EXTERN_C extern "C" {
#define END_EXTERN_C }
#else
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif

/* MinGW needs some special handling because it is a mixture of WIN32 and Posix.
 * The following settings are not tested by configure but need to be set for MinGW.
 */
#ifdef __MINGW32__
#define HAVE_WINDOWS_H 1
#define HAVE_WINSOCK_H 1
#define NO_IOS_BASE_ASSIGN 1
#define ENVIRONMENT_PATH_SEPARATOR ';'
#endif

/* Define if alignas supports typedefs */
/* #undef ALIGNAS_SUPPORTS_TYPEDEFS */

/* Define if __attribute__((aligned)) supports templates */
#define ATTRIBUTE_ALIGNED_SUPPORTS_TEMPLATES 1

/* Define the canonical host system type as a string constant. */
#define CANONICAL_HOST_TYPE "x86_64-apple-darwin16.3.0"

/* Define if char is unsigned on the C compiler */
/* #undef C_CHAR_UNSIGNED */

/* Define to the inline keyword supported by the C compiler, if any, or to the
 empty string */
#define C_INLINE inline

/* Define if >> is unsigned on the C compiler */
/* #undef C_RIGHTSHIFT_UNSIGNED */

/* Define the DCMTK default path. */
#define DCMTK_PREFIX "/usr/local"

/* Enable or disable C++11 while building DCMTK. */
/* #undef DCMTK_USE_CXX11_STL */

/* Empty default data dictionary path for the dcmdata library package. */
#define DCM_DICT_DEFAULT_PATH "/usr/local/share/dcmtk/dicom.dic"

/* Define the default directory where configuration files reside. */
#define DEFAULT_CONFIGURATION_DIR "/usr/local/etc/dcmtk/"

/* Define the default directory where support data files reside. */
#define DEFAULT_SUPPORT_DATA_DIR "/usr/local/share/dcmtk/"

/* Define if we are compiling with built-in (compiled-in) dictionary enabled.
 */
/* #undef ENABLE_BUILTIN_DICTIONARY */

/* Define if we are compiling for loading external dictionary from default
 path. */
#define ENABLE_EXTERNAL_DICTIONARY /**/

/* Define if we are compiling for enabling external private tag dictionary. */
/* #undef ENABLE_PRIVATE_TAGS */

/* Define the environment variable path separator. */
#ifndef ENVIRONMENT_PATH_SEPARATOR
#define ENVIRONMENT_PATH_SEPARATOR ':'
#endif

/* Define to 1 if you have the `accept' function. */
#define HAVE_ACCEPT 1

/* Define to 1 if you have the `access' function. */
#define HAVE_ACCESS 1

/* Define to 1 if you have the <alloca.h> header file. */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the <assert.h> header file. */
#define HAVE_ASSERT_H 1

/* Define if __attribute__((aligned)) is available */
#define HAVE_ATTRIBUTE_ALIGNED 1

/* Define to 1 if you have the `bcmp' function. */
#define HAVE_BCMP 1

/* Define to 1 if you have the `bcopy' function. */
#define HAVE_BCOPY 1

/* Define to 1 if you have the `bind' function. */
#define HAVE_BIND 1

/* Define to 1 if you have the `bzero' function. */
#define HAVE_BZERO 1

/* Define if your system declares the return type of strerror_r as char *
 instead of int */
/* #undef HAVE_CHARP_STRERROR_R */

/* Define if your C++ compiler can work with class templates */
#define HAVE_CLASS_TEMPLATE 1

/* Define to 1 if you have the <climits> header file. */
#define HAVE_CLIMITS 1

/* Define to 1 if you have the <cmath> header file. */
#define HAVE_CMATH 1

/* Define to 1 if you have the `connect' function. */
#define HAVE_CONNECT 1

/* define if the compiler supports const_cast<> */
#define HAVE_CONST_CAST /**/

/* Define to 1 if you have the <cstdarg> header file. */
#define HAVE_CSTDARG 1

/* Define to 1 if you have the <cstddef> header file. */
#define HAVE_CSTDDEF 1

/* Define to 1 if you have the <cstdint> header file. */
/* #undef HAVE_CSTDINT */

/* Define to 1 if you have the <cstdio> header file. */
#define HAVE_CSTDIO 1

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H 1

/* Define to 1 if you have the `cuserid' function. */
/* #undef HAVE_CUSERID */

/* Define if bool is a built-in type */
#define HAVE_CXX_BOOL 1

/* Define if volatile is a known keyword */
#define HAVE_CXX_VOLATILE /**/

/* Define if "const" is supported by the C compiler */
#define HAVE_C_CONST 1

/* Define if your system has a declaration for socklen_t in sys/types.h
 sys/socket.h */
#define HAVE_DECLARATION_SOCKLEN_T 1

/* Define if your system has a declaration for std::ios_base::openmode in
 iostream.h */
#define HAVE_DECLARATION_STD__IOS_BASE__OPENMODE 1

/* Define if your system has a declaration for struct utimbuf in sys/types.h
 utime.h sys/utime.h */
#define HAVE_DECLARATION_STRUCT_UTIMBUF 1

/* Define if the compiler supports default constructor detection via SFINAE */
#define HAVE_DEFAULT_CONSTRUCTOR_DETECTION_VIA_SFINAE 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
 */
#define HAVE_DIRENT_H 1

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* define if the compiler supports dynamic_cast<> */
#define HAVE_DYNAMIC_CAST /**/

/* Define if your system cannot pass command line arguments into main() (e.g. Macintosh). */
/* #undef HAVE_EMPTY_ARGC_ARGV */

/* Define if your system provides ENAMETOOLONG errno value. */
#define HAVE_ENAMETOOLONG /**/

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define if your C++ compiler supports the explicit template specialization
 syntax */
#define HAVE_EXPLICIT_TEMPLATE_SPECIALIZATION 1

/* Define to 1 if you have the `fcntl' function. */
#define HAVE_FCNTL 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <fenv.h> header file. */
#define HAVE_FENV_H 1

/* Define to 1 if you have the `finite' function. */
#define HAVE_FINITE 1

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the `flock' function. */
#define HAVE_FLOCK 1

/* Define to 1 if you have the <fnmatch.h> header file. */
#define HAVE_FNMATCH_H 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if the system has the type `fpos64_t'. */
/* #undef HAVE_FPOS64_T */

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#define HAVE_FSEEKO 1

/* Define to 1 if you have the <fstream> header file. */
#define HAVE_FSTREAM 1

/* Define to 1 if you have the <fstream.h> header file. */
/* #undef HAVE_FSTREAM_H */

/* Define to 1 if you have the `ftime' function. */
#define HAVE_FTIME 1

/* Define if your C++ compiler can work with function templates */
#define HAVE_FUNCTION_TEMPLATE 1

/* Define to 1 if you have the `getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getenv' function. */
#define HAVE_GETENV 1

/* Define to 1 if you have the `geteuid' function. */
#define HAVE_GETEUID 1

/* Define to 1 if you have the `getgrnam' function. */
#define HAVE_GETGRNAM 1

/* Define to 1 if you have the `getgrnam_r' function. */
#define HAVE_GETGRNAM_R 1

/* Define to 1 if you have the `gethostbyaddr_r' function. */
/* #undef HAVE_GETHOSTBYADDR_R */

/* Define to 1 if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define to 1 if you have the `gethostbyname_r' function. */
/* #undef HAVE_GETHOSTBYNAME_R */

/* Define to 1 if you have the `gethostid' function. */
#define HAVE_GETHOSTID 1

/* Define to 1 if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Define to 1 if you have the `getlogin' function. */
#define HAVE_GETLOGIN 1

/* Define to 1 if you have the `getpid' function. */
#define HAVE_GETPID 1

/* Define to 1 if you have the `getpwnam' function. */
#define HAVE_GETPWNAM 1

/* Define to 1 if you have the `getpwnam_r' function. */
#define HAVE_GETPWNAM_R 1

/* Define to 1 if you have the `getsockname' function. */
#define HAVE_GETSOCKNAME 1

/* Define to 1 if you have the `getsockopt' function. */
#define HAVE_GETSOCKOPT 1

/* Define to 1 if you have the `getuid' function. */
#define HAVE_GETUID 1

/* Define to 1 if you have the `gmtime_r' function. */
#define HAVE_GMTIME_R 1

/* Define if __alignof__ is available */
#define HAVE_GNU_ALIGNOF 1

/* Define to 1 if you have the <grp.h> header file. */
#define HAVE_GRP_H 1

/* Define to 1 if you have the `htonl' function. */
#define HAVE_HTONL 1

/* Define to 1 if you have the `htons' function. */
#define HAVE_HTONS 1

/* Define to 1 if you have the <ieeefp.h> header file. */
/* #undef HAVE_IEEEFP_H */

/* Define to 1 if you have the `index' function. */
#define HAVE_INDEX 1

/* Define to 1 if the system has the type `int64_t'. */
#define HAVE_INT64_T 1

/* Define if your system declares argument 3 of accept() as int * instead of
 size_t * or socklen_t * */
/* #undef HAVE_INTP_ACCEPT */

/* Define if your system declares argument 5 of getsockopt() as int * instead
 of size_t * or socklen_t */
/* #undef HAVE_INTP_GETSOCKOPT */

/* Define if your system declares argument 2-4 of select() as int * instead of
 struct fd_set * */
/* #undef HAVE_INTP_SELECT */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <iomanip> header file. */
#define HAVE_IOMANIP 1

/* Define to 1 if you have the <iomanip.h> header file. */
/* #undef HAVE_IOMANIP_H */

/* Define to 1 if you have the <iostream> header file. */
#define HAVE_IOSTREAM 1

/* Define to 1 if you have the <iostream.h> header file. */
/* #undef HAVE_IOSTREAM_H */

/* Define if your system defines ios::nocreate in iostream.h */
/* #undef HAVE_IOS_NOCREATE */

/* Define to 1 if you have the <io.h> header file. */
/* #undef HAVE_IO_H */

/* Define to 1 if you have the `isinf' function. */
#define HAVE_ISINF 1

/* Define to 1 if you have the `isnan' function. */
#define HAVE_ISNAN 1

/* Define to 1 if you have the <iso646.h> header file. */
#define HAVE_ISO646_H 1

/* Define to 1 if you have the `itoa' function. */
/* #undef HAVE_ITOA */

/* Define if LFS (large file support) is available */
#define HAVE_LFS_SUPPORT /**/

/* Define to 1 if you have the <libc.h> header file. */
#define HAVE_LIBC_H 1

/* Define to 1 if you have the `iostream' library (-liostream). */
/* #undef HAVE_LIBIOSTREAM */

/* Define to 1 if you have the `nsl' library (-lnsl). */
/* #undef HAVE_LIBNSL */

/* Define to 1 if you have the <libpng/png.h> header file. */
/* #undef HAVE_LIBPNG_PNG_H */

/* Define to 1 if you have the `socket' library (-lsocket). */
/* #undef HAVE_LIBSOCKET */

/* Define if libtiff supports LZW compression */
/* #undef HAVE_LIBTIFF_LZW_COMPRESSION */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `listen' function. */
#define HAVE_LISTEN 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* Define to 1 if you have the `lockf' function. */
#define HAVE_LOCKF 1

/* Define to 1 if the system has the type `longlong'. */
/* #undef HAVE_LONGLONG */

/* Define to 1 if you support file names longer than 14 characters. */
#define HAVE_LONG_FILE_NAMES 1

/* Define to 1 if the system has the type `long long'. */
#define HAVE_LONG_LONG 1

/* Define to 1 if you have the `lstat' function. */
#define HAVE_LSTAT 1

/* Define to 1 if you have the `malloc_debug' function. */
#define HAVE_MALLOC_DEBUG 1

/* Define to 1 if you have the <malloc.h> header file. */
/* #undef HAVE_MALLOC_H */

/* Define to 1 if you have the <math.h> header file. */
#define HAVE_MATH_H 1

/* Define to 1 if you have the `mbstowcs' function. */
#define HAVE_MBSTOWCS 1

/* Define to 1 if you have the `memcmp' function. */
#define HAVE_MEMCMP 1

/* Define to 1 if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkstemp' function. */
#define HAVE_MKSTEMP 1

/* Define to 1 if you have the `mktemp' function. */
#define HAVE_MKTEMP 1

/* Define to 1 if you have the `nanosleep' function. */
#define HAVE_NANOSLEEP 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <netinet/in_systm.h> header file. */
#define HAVE_NETINET_IN_SYSTM_H 1

/* Define to 1 if you have the <netinet/tcp.h> header file. */
#define HAVE_NETINET_TCP_H 1

/* Define to 1 if you have the <new> header file. */
#define HAVE_NEW 1

/* Define to 1 if you have the <new.h> header file. */
/* #undef HAVE_NEW_H */

/* Define if the compiler supports operator delete (std::nothrow) */
#define HAVE_NOTHROW_DELETE /**/

/* Define `pid_t' to `int' if <sys/types.h> does not define. */
/* #undef HAVE_NO_TYPEDEF_PID_T */

#ifdef HAVE_NO_TYPEDEF_PID_T
typedef int pid_t;
#endif

/* Define `size_t' to `unsigned' if <sys/types.h> does not define. */
/* #undef HAVE_NO_TYPEDEF_SIZE_T */

#ifdef HAVE_NO_TYPEDEF_SIZE_T
typedef unsigned size_t;
#endif

/* Define `ssize_t' to `long' if <sys/types.h> does not define. */
/* #undef HAVE_NO_TYPEDEF_SSIZE_T */

#ifdef HAVE_NO_TYPEDEF_SSIZE_T
typedef long ssize_t;
#endif

/* Define `uchar' to `unsigned char' if <sys/types.h> does not define. */
#define HAVE_NO_TYPEDEF_UCHAR 1

#ifdef HAVE_NO_TYPEDEF_UCHAR
typedef unsigned char uchar;
#endif

/* Define `uint' to `unsigned int' if <sys/types.h> does not define. */
/* #undef HAVE_NO_TYPEDEF_UINT */

#ifdef HAVE_NO_TYPEDEF_UINT
typedef unsigned int uint;
#endif

/* Define `ulong' to `unsigned long' if <sys/types.h> does not define. */
#define HAVE_NO_TYPEDEF_ULONG 1

#ifdef HAVE_NO_TYPEDEF_ULONG
typedef unsigned long ulong;
#endif

/* Define `ushort' to `unsigned short' if <sys/types.h> does not define. */
/* #undef HAVE_NO_TYPEDEF_USHORT */

#ifdef HAVE_NO_TYPEDEF_USHORT
typedef unsigned short ushort;
#endif

/* Define to 1 if you have the `ntohl' function. */
#define HAVE_NTOHL 1

/* Define to 1 if you have the `ntohs' function. */
#define HAVE_NTOHS 1

/* Define to 1 if the system has the type `off64_t'. */
/* #undef HAVE_OFF64_T */

/* Define if your system supports readdir_r with the obsolete Posix 1.c draft
 6 declaration (2 arguments) instead of the Posix 1.c declaration with 3
 arguments. */
/* #undef HAVE_OLD_READDIR_R */

/* Define if passwd::pw_gecos is available. */
#define HAVE_PASSWD_GECOS /**/

/* Define to 1 if you have the `pclose' function. */
#define HAVE_PCLOSE 1

/* Define if pthread_t is a pointer type on your system */
#define HAVE_POINTER_TYPE_PTHREAD_T 1

/* Define to 1 if you have the `popen' function. */
#define HAVE_POPEN 1

/* Define if your system has a prototype for accept in sys/types.h
 sys/socket.h */
#define HAVE_PROTOTYPE_ACCEPT 1

/* Define if your system has a prototype for bind in sys/types.h sys/socket.h
 */
#define HAVE_PROTOTYPE_BIND 1

/* Define if your system has a prototype for bzero in string.h strings.h
 libc.h unistd.h stdlib.h */
#define HAVE_PROTOTYPE_BZERO 1

/* Define if your system has a prototype for connect in sys/types.h
 sys/socket.h */
#define HAVE_PROTOTYPE_CONNECT 1

/* Define if your system has a prototype for finite in math.h */
#define HAVE_PROTOTYPE_FINITE 1

/* Define if your system has a prototype for flock in sys/file.h */
#define HAVE_PROTOTYPE_FLOCK 1

/* Define if your system has a prototype for gethostbyname in libc.h unistd.h
 stdlib.h netdb.h */
#define HAVE_PROTOTYPE_GETHOSTBYNAME 1

/* Define if your system has a prototype for gethostbyname_r in libc.h
 unistd.h stdlib.h netdb.h */
/* #undef HAVE_PROTOTYPE_GETHOSTBYNAME_R */

/* Define if your system has a prototype for gethostid in libc.h unistd.h
 stdlib.h netdb.h */
#define HAVE_PROTOTYPE_GETHOSTID 1

/* Define if your system has a prototype for gethostname in unistd.h libc.h
 stdlib.h netdb.h */
#define HAVE_PROTOTYPE_GETHOSTNAME 1

/* Define if your system has a prototype for getsockname in sys/types.h
 sys/socket.h */
#define HAVE_PROTOTYPE_GETSOCKNAME 1

/* Define if your system has a prototype for getsockopt in sys/types.h
 sys/socket.h */
#define HAVE_PROTOTYPE_GETSOCKOPT 1

/* Define if your system has a prototype for gettimeofday in sys/time.h
 unistd.h */
#define HAVE_PROTOTYPE_GETTIMEOFDAY 1

/* Define if your system has a prototype for isinf in math.h */
#define HAVE_PROTOTYPE_ISINF 1

/* Define if your system has a prototype for isnan in math.h */
#define HAVE_PROTOTYPE_ISNAN 1

/* Define if your system has a prototype for listen in sys/types.h
 sys/socket.h */
#define HAVE_PROTOTYPE_LISTEN 1

/* Define if your system has a prototype for mkstemp in libc.h unistd.h
 stdlib.h */
#define HAVE_PROTOTYPE_MKSTEMP 1

/* Define if your system has a prototype for mktemp in libc.h unistd.h
 stdlib.h */
#define HAVE_PROTOTYPE_MKTEMP 1

/* Define if your system has a prototype for select in sys/select.h
 sys/types.h sys/socket.h sys/time.h */
#define HAVE_PROTOTYPE_SELECT 1

/* Define if your system has a prototype for setsockopt in sys/types.h
 sys/socket.h */
#define HAVE_PROTOTYPE_SETSOCKOPT 1

/* Define if your system has a prototype for socket in sys/types.h
 sys/socket.h */
#define HAVE_PROTOTYPE_SOCKET 1

/* Define if your system has a prototype for std::finite in cmath */
#define HAVE_PROTOTYPE_STD__FINITE 1

/* Define if your system has a prototype for std::isinf in cmath */
#define HAVE_PROTOTYPE_STD__ISINF 1

/* Define if your system has a prototype for std::isnan in cmath */
#define HAVE_PROTOTYPE_STD__ISNAN 1

/* Define if your system has a prototype for std::vfprintf in stdarg.h stdio.h
 */
#define HAVE_PROTOTYPE_STD__VFPRINTF 1

/* Define if your system has a prototype for std::vsnprintf in stdarg.h
 stdio.h */
#define HAVE_PROTOTYPE_STD__VSNPRINTF 1

/* Define if your system has a prototype for strcasecmp in string.h */
#define HAVE_PROTOTYPE_STRCASECMP 1

/* Define if your system has a prototype for strerror_r in string.h */
#define HAVE_PROTOTYPE_STRERROR_R 1

/* Define if your system has a prototype for strncasecmp in string.h */
#define HAVE_PROTOTYPE_STRNCASECMP 1

/* Define if your system has a prototype for usleep in libc.h unistd.h
 stdlib.h */
#define HAVE_PROTOTYPE_USLEEP 1

/* Define if your system has a prototype for vsnprintf in stdio.h stdarg.h */
#define HAVE_PROTOTYPE_VSNPRINTF 1

/* Define if your system has a prototype for wait3 in libc.h sys/wait.h
 sys/time.h sys/resource.h */
#define HAVE_PROTOTYPE_WAIT3 1

/* Define if your system has a prototype for waitpid in sys/wait.h sys/time.h
 sys/resource.h */
#define HAVE_PROTOTYPE_WAITPID 1

/* Define if your system has a prototype for _stricmp in string.h */
/* #undef HAVE_PROTOTYPE__STRICMP */

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Define if your system supports POSIX read/write locks. */
#define HAVE_PTHREAD_RWLOCK /**/

/* Define to 1 if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define if OpenSSL provides the RAND_egd function. */
/* #undef HAVE_RAND_EGD */

/* define if the compiler supports reinterpret_cast<> */
#define HAVE_REINTERPRET_CAST /**/

/* Define to 1 if you have the `rindex' function. */
#define HAVE_RINDEX 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the <semaphore.h> header file. */
#define HAVE_SEMAPHORE_H 1

/* Define to 1 if you have the <setjmp.h> header file. */
#define HAVE_SETJMP_H 1

/* Define to 1 if you have the `setsockopt' function. */
#define HAVE_SETSOCKOPT 1

/* Define to 1 if you have the `setuid' function. */
#define HAVE_SETUID 1

/* Define to 1 if the system has the type `sigjmp_buf'. */
#define HAVE_SIGJMP_BUF 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the `sleep' function. */
#define HAVE_SLEEP 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define if OpenSSL provides the SSL_CTX_get0_param function. */
/* #undef HAVE_SSL_CTX_GET0_PARAM */

/* Define to 1 if you have the <sstream> header file. */
#define HAVE_SSTREAM 1

/* Define to 1 if you have the <sstream.h> header file. */
/* #undef HAVE_SSTREAM_H */

/* Define to 1 if you have the `stat' function. */
#define HAVE_STAT 1

/* define if the compiler supports static_cast<> */
#define HAVE_STATIC_CAST /**/

/* Define if your C++ compiler can work with static methods in class templates
 */
#define HAVE_STATIC_TEMPLATE_METHOD 1

/* Define to 1 if you have the <stat.h> header file. */
/* #undef HAVE_STAT_H */

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdbool.h> header file. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define if ANSI standard C++ includes use std namespace */
#define HAVE_STD_NAMESPACE 1

/* Define if the compiler supports std::nothrow */
#define HAVE_STD__NOTHROW /**/

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcat' function. */
#define HAVE_STRLCAT 1

/* Define to 1 if you have the `strlcpy' function. */
#define HAVE_STRLCPY 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the <strstream> header file. */
#define HAVE_STRSTREAM 1

/* Define to 1 if you have the <strstream.h> header file. */
/* #undef HAVE_STRSTREAM_H */

/* Define to 1 if you have the <strstrea.h> header file. */
/* #undef HAVE_STRSTREA_H */

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if you have the <synch.h> header file. */
/* #undef HAVE_SYNCH_H */

/* Define if __sync_add_and_fetch is available */
#define HAVE_SYNC_ADD_AND_FETCH 1

/* Define if __sync_sub_and_fetch is available */
#define HAVE_SYNC_SUB_AND_FETCH 1

/* Define to 1 if you have the `sysinfo' function. */
/* #undef HAVE_SYSINFO */

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
 */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/errno.h> header file. */
#define HAVE_SYS_ERRNO_H 1

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define if your system has a prototype for gettid. */
#define HAVE_SYS_GETTID /**/

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
 */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/syscall.h> header file. */
#define HAVE_SYS_SYSCALL_H 1

/* Define to 1 if you have the <sys/systeminfo.h> header file. */
/* #undef HAVE_SYS_SYSTEMINFO_H */

/* Define to 1 if you have the <sys/timeb.h> header file. */
#define HAVE_SYS_TIMEB_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/utime.h> header file. */
/* #undef HAVE_SYS_UTIME_H */

/* Define to 1 if you have the <sys/utsname.h> header file. */
#define HAVE_SYS_UTSNAME_H 1

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the `tempnam' function. */
#define HAVE_TEMPNAM 1

/* Define to 1 if you have the <thread.h> header file. */
/* #undef HAVE_THREAD_H */

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if you have the `tmpnam' function. */
#define HAVE_TMPNAM 1

/* define if the compiler recognizes typename */
#define HAVE_TYPENAME /**/

/* Define to 1 if the system has the type `uint64_t'. */
#define HAVE_UINT64_T 1

/* Define to 1 if the system has the type `ulonglong'. */
/* #undef HAVE_ULONGLONG */

/* Define to 1 if you have the `uname' function. */
#define HAVE_UNAME 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <unix.h> header file. */
/* #undef HAVE_UNIX_H */

/* Define to 1 if the system has the type `unsigned long long'. */
#define HAVE_UNSIGNED_LONG_LONG 1

/* Define to 1 if you have the `usleep' function. */
#define HAVE_USLEEP 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define if variable-length arrays are supported in C */
#define HAVE_VLA 1

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `wait3' system call. Deprecated, you should no
 longer depend upon `wait3'. */
#define HAVE_WAIT3 1

/* Define to 1 if you have the `waitpid' function. */
#define HAVE_WAITPID 1

/* Define to 1 if you have the <wchar.h> header file. */
#define HAVE_WCHAR_H 1

/* Define to 1 if you have the `wcstombs' function. */
#define HAVE_WCSTOMBS 1

/* Define to 1 if you have the <wctype.h> header file. */
#define HAVE_WCTYPE_H 1

/* Define to 1 if you have the `_findfirst' function. */
/* #undef HAVE__FINDFIRST */

/* Define if the compiler supports __FUNCTION__. */
#define HAVE___FUNCTION___MACRO 1

/* Define if the compiler supports __PRETTY_FUNCTION__. */
#define HAVE___PRETTY_FUNCTION___MACRO 1

/* Define if the compiler supports __func__. */
#define HAVE___func___MACRO 1

/* Define if libc.h should be treated as a C++ header */
/* #undef INCLUDE_LIBC_H_AS_CXX */

/* Define if <math.h> fails if included extern "C" */
/* #undef INCLUDE_MATH_H_AS_CXX */

/* Define if the second argument to iconv() is const. */
/* #undef LIBICONV_SECOND_ARGUMENT_CONST */

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "bugs@dcmtk.org"

/* Define to the release date of this package. */
#define PACKAGE_DATE "DEV"

/* Define to the full name of this package. */
#define PACKAGE_NAME "dcmtk"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "OsiriX dcmtk 3.6.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "OsiriX dcmtk-3.6.1"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://www.osirix-viewer.com/"

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.6.1"

/* Define to the version number of this package. */
#define PACKAGE_VERSION_NUMBER 361

/* Define to the version suffix of this package. */
#define PACKAGE_VERSION_SUFFIX ""

/* Define path separator. */
#define PATH_SEPARATOR '/'

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define if signal handlers need ellipse (...) parameters */
/* #undef SIGNAL_HANDLER_WITH_ELLIPSE */

/* The size of `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of `double', as computed by sizeof. */
#define SIZEOF_DOUBLE 8

/* The size of `float', as computed by sizeof. */
#define SIZEOF_FLOAT 4

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 8

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 8

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Namespace for ANSI C functions in standard C++ headers */
#define STDIO_NAMESPACE ::

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Define if ANSI standard C++ includes are used. */
#define USE_STD_CXX_INCLUDES /**/

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define if we are compiling with libiconv support. */
/* #undef WITH_LIBICONV */

/* Define if we are compiling with libpng support. */
/* #undef WITH_LIBPNG */

/* Define if we are compiling with libtiff support. */
/* #undef WITH_LIBTIFF */

/* Define if we are compiling with libxml support. */
//#define WITH_LIBXML /**/

/* Define if we are compiling with OpenSSL support. */
/* #undef WITH_OPENSSL */

/* Define if we are compiling with libsndfile support. */
/* #undef WITH_SNDFILE */

/* Define if we are compiling with libwrap (TCP wrapper) support. */
/* #undef WITH_TCPWRAPPER */

/* Define if we are compiling with any type of multi-thread support. */
#define WITH_THREADS /**/

/* Define if we are compiling with zlib support. */
#define WITH_ZLIB /**/

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to enable LFS64 (explicit large file support) if available */
/* #undef _LARGEFILE64_SOURCE */

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
 this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to 1 if type `char' is unsigned and you are not using gcc.  */
#ifndef __CHAR_UNSIGNED__
/* # undef __CHAR_UNSIGNED__ */
#endif

/* Define to int if undefined. */
/* #undef socklen_t */

#if defined(DCMTK_USE_CXX11_STL) && defined(__cplusplus) && __cplusplus < 201103L
#error\
DCMTK was configured to use the C++11 STL, but your compiler is not configured\
for building with C++11 features.
#endif

// an ISO 9660 format only allows 8 characters in file name
#define MAX_FNAME_COMPONENT_SIZE 24 // ANR 2017 Feb 16

#endif /* OSCONFIG_H */
