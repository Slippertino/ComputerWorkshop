#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(Right)
	ENTITY_NAME(rights)

	ENTITY_FIELD(QUuid, user_id)
	ENTITY_FIELD(QString, entity)
	ENTITY_FIELD(qint16, op)

	ENTITY_FIELD_DATA_BEGIN(Right)
		ENTITY_FIELD_DATA(Right, 
			user_id,	
			ValidatorsFactory::uuid(),				
			false
		)

		ENTITY_FIELD_DATA(Right, 
			entity,	
			ValidatorsFactory::string_size(1, 50),	
			false
		)

		ENTITY_FIELD_DATA(Right, 
			op,		
			ValidatorsFactory::int_range(1, 15),	
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop