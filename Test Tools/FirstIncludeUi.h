#ifndef ZS_TESTTOOLS_TESTTOOLSDEFINES_H_
#define ZS_TESTTOOLS_TESTTOOLSDEFINES_H_

#include <QtGlobal>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#define ZH_CN(x) QStringLiteral(x)
#else
#define ZH_CN(x) x
#endif

#include "CommandUi.h"

#ifndef GROUP_UI
#define GROUP_UI "ui"
#endif
#ifndef KEY_THEME_COLOR
#define KEY_THEME_COLOR "theme-color"
#endif

#ifndef UI_LANG_ZH_CN_TYPE
#define UI_LANG_ZH_CN_TYPE 1
#endif
#ifndef UI_LANG_EN_US_TYPE
#define UI_LANG_EN_US_TYPE 2
#endif

typedef unsigned long long id_t;
typedef unsigned long long type_t;

#endif