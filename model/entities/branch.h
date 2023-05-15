#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(Branch)
	ENTITY_NAME(branches)

	ENTITY_FIELD(QString, email)
	ENTITY_FIELD(QString, city)
	ENTITY_FIELD(QString, address)
	ENTITY_FIELD(QString, working_hours)
	ENTITY_FIELD(std::optional<QString>, phone)

	ENTITY_FIELD_DATA_BEGIN(Branch)
		ENTITY_FIELD_DATA(Branch, 
			email,			
			ValidatorsFactory::email(),				
			false
		)

		ENTITY_FIELD_DATA(Branch, 
			city,				
			ValidatorsFactory::string_size(3, 20),	
			false
		)

		ENTITY_FIELD_DATA(Branch, 
			address,			
			ValidatorsFactory::string_size(5, 50),	
			false
		)

		ENTITY_FIELD_DATA(Branch, 
			working_hours,	
			ValidatorsFactory::working_hours(),		
			false
		)

		ENTITY_FIELD_DATA(Branch, 
			phone, 
			ValidatorsFactory::nullable(ValidatorsFactory::phone()),	
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop
