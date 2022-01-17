#ifndef LFTUBRLA_TESTTOOLS_UI_UISTRUCTS_H_
#define LFTUBRLA_TESTTOOLS_UI_UISTRUCTS_H_

#include "FirstIncludeUi.h"

namespace UI {
	struct WaitingSendTarget {
		id_t target_id;
		type_t target_type;
		double start_A;
		double end_A;
		double start_E;
		double end_E;
		double start_R;
		double end_R;
		double V;
		double RCS;
		bool is_indicate;
		bool is_random_pose;
		WaitingSendTarget():target_id(0),target_type(0),start_A(0), end_A(0)
			,start_E(0), end_E(0), start_R(0), end_R(0), V(0), RCS(0)
			,is_indicate(false), is_random_pose(false) {

		}
	};
}

#endif