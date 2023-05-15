#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(EmbeddedService)
	ENTITY_NAME(embedded_services)

	ENTITY_FIELD(QString, service_name)
	ENTITY_FIELD(qreal, cost)

	ENTITY_FIELD_DATA_BEGIN(EmbeddedService)
		ENTITY_FIELD_DATA(EmbeddedService, 
			service_name,	
			ValidatorsFactory::string_size(10, 100),	
			false
		)

		ENTITY_FIELD_DATA(EmbeddedService, 
			cost,			
			ValidatorsFactory::real_range(0, 10000, 3), 
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop