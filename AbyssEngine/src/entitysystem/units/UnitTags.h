#pragma once

/*
	UnitTags are used to give UnitTypes unique functionality
	per type.
*/

/*
	UnitTag_Untargeted means the unit does not belong to and isnt targeted
	towards a specific entity.

	When systems request untargeted units, they recieve all units of that type.
*/
struct UnitTag_Untargeted
{

};