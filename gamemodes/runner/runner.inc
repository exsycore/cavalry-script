#if defined _inc_runner
#undef _inc_runner
#endif

#if !defined RUNNER_@@@@_HEADER
    #include "util\header"
    #include "core\header"
    #include "db\callape"
    #include "server\header"
    #include "fixed\header"
    #include "player\header"
    #include "cmd\header"
    #include "system\header"
    #include "variables\header"

    #define RUNNER_@@@@_HEADER

#elseif !defined RUNNER_@@@@_IMPL
    #include "util\impl"
    #include "core\impl"
    #include "server\impl"
    #include "fixed\impl"
    #include "player\impl"
    #include "cmd\impl"
    #include "system\impl"
    #include "variables\impl"

    #include "db\exit"

    #define RUNNER_@@@@_IMPL
#else
    #error Runner already set up
#endif
