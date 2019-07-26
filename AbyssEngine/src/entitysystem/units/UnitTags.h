#pragma once

namespace entitysystem
{
	/*
		UnitTags are used to give UnitTypes unique functionality per type.
	*/

	/*
		UnitTag_Untargeted means the Unit does not belong to and isn't targeted
		towards a specific entity.

		When systems request untargeted Units, they recieve all Units of that type.
	*/
	struct UnitTag_Untargeted { };
}