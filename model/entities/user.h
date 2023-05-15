#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(User)
	ENTITY_NAME(users)

	ENTITY_FIELD(QString, login)
	ENTITY_FIELD(std::optional<QUuid>, employee_id)
	ENTITY_FIELD(QString, password)

	ENTITY_FIELD_DATA_BEGIN(User)
		ENTITY_FIELD_DATA(User, 
			login,			
			ValidatorsFactory::string_size(5, 30),					
			false
		)

		ENTITY_FIELD_DATA(User, 
			employee_id,	
			ValidatorsFactory::nullable(ValidatorsFactory::uuid()),	
			false
		)

		ENTITY_FIELD_DATA(User, 
			password,		
			std::nullopt,											
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop