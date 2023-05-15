#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(Client)
	ENTITY_NAME(clients)

	ENTITY_FIELD(QString, full_name)
	ENTITY_FIELD(QString, phone)
	ENTITY_FIELD(std::optional<QString>, email)

	ENTITY_FIELD_DATA_BEGIN(Client)
		ENTITY_FIELD_DATA(Client, 
			full_name,	
			ValidatorsFactory::string_size(10, 100),	
			false
		)

		ENTITY_FIELD_DATA(Client, 
			phone,		
			ValidatorsFactory::phone(),					
			false
		)

		ENTITY_FIELD_DATA(Client, 
			email,		
			ValidatorsFactory::nullable(ValidatorsFactory::email()),
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop