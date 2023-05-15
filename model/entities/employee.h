#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(Employee)
	ENTITY_NAME(employees)

	ENTITY_FIELD(std::optional<QUuid>, branch_id)
	ENTITY_FIELD(QString, full_name)
	ENTITY_FIELD(QString, phone)
	ENTITY_FIELD(QString, position)
	ENTITY_FIELD(qint16, week_working_rate)
	ENTITY_FIELD(qreal, salary)
	ENTITY_FIELD(std::optional<QString>, email)
	ENTITY_FIELD(std::optional<QString>, working_hours)
	ENTITY_FIELD(std::optional<QString>, link_to_contract)

	ENTITY_FIELD_DATA_BEGIN(Employee)
		ENTITY_FIELD_DATA(Employee, 
			branch_id,			
			ValidatorsFactory::nullable(ValidatorsFactory::uuid()),					
			false
		)

		ENTITY_FIELD_DATA(Employee, 
			full_name,			
			ValidatorsFactory::string_size(10, 100),								
			false
		)

		ENTITY_FIELD_DATA(Employee, 
			phone,				
			ValidatorsFactory::phone(),												
			false
		)

		ENTITY_FIELD_DATA(Employee, 
			position,			
			ValidatorsFactory::string_size(7, 20),									
			false
		)

		ENTITY_FIELD_DATA(Employee, 
			week_working_rate,	
			ValidatorsFactory::int_range(1, 51),									
			false
		)

		ENTITY_FIELD_DATA(Employee, 
			salary,				
			ValidatorsFactory::real_range(0, 50000, 3),								
			false
		)

		ENTITY_FIELD_DATA(Employee, 
			email,				
			ValidatorsFactory::nullable(ValidatorsFactory::email()),				
			false
		)

		ENTITY_FIELD_DATA(Employee, 
			working_hours,		
			ValidatorsFactory::nullable(ValidatorsFactory::working_hours()),		
			false
		)

		ENTITY_FIELD_DATA(Employee, 
			link_to_contract,	
			ValidatorsFactory::nullable(ValidatorsFactory::string_size(10, 255)),	
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop
