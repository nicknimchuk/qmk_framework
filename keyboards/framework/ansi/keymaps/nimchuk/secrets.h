#pragma once

#if (__has_include("secrets_real.h") && !defined(NO_SECRETS))
#   include "secrets_real.h"
#else
#   define SECRET_WMAIL     ""
#   define SECRET_ADSTR     ""
#   define SECRET_ADCIT     ""
#   define SECRET_ADZIP     ""
#   define SECRET_NAMES     ""
#   define SECRET_NAMEL     ""
#   define SECRET_HMAIL     ""
#   define SECRET_REGRD     ""
#endif
