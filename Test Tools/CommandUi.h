#ifndef LFTUBRLA_TESTTOOLS_UI_COMMANDUI_H_
#define LFTUBRLA_TESTTOOLS_UI_COMMANDUI_H_

#include "FirstIncludeUi.h"
#include <string>

typedef const unsigned long long CmdId;

namespace UI {
	CmdId ID_CHANGE_THEME = 1;
	struct CHANGE_THEME {
		std::string theme_color;
	};

	CmdId ID_CHANGE_FONT = 2;
	struct CHANGE_FONT {
		int font_type;
		std::string family;
		bool bold;
		int size;
	};
}


#endif