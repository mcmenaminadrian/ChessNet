#include "sys/types.h"
#include "innerfilterlayer.hpp"

using namespace std;

static const uint secondSpan = 1;
static const uint secondField = 3;

InnerFilterLayer::InnerFilterLayer(const FilterNet& topLayer)
{
	for (uint i = 0; i < topLayer.size(); i++) {
		uint layerSize = calculateSecondLayerSize(secondSpan,
			secondField);
	}
}

