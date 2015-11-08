#define _VER "0.1"

#if _M_IX86_FP > 0
#define _VERSION _VER " (SSE" TOSTRING(_M_IX86_FP) ")"
#elif _M_IX86_FP == 1
#define _VERSION _VER " (SSE)"
#else
#define _VERSION _VER
#endif

#define VERSION _VERSION

#define COMPONENT_NAME "Custom lyrics source"

#define ABOUT "foo_lyricsource " VERSION "\n" \
 "A custom lyric source developed by The vern.\n" \
 "Build Date: " __DATE__ " " __TIME__ "\n"