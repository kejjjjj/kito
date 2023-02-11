#include "pch.h"


explicit SWheel::SWheel(std::list<WheelObj> _objects, float _radius) : objects(_objects), radius(_radius)
{


	items = objects.size();

	if (!items) {
		Com_Error(ERR_DROP, "SWheel::SWheel(): empty list of objects");
		return;
	}
	


}