#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(Contract)
	ENTITY_NAME(contracts)

	ENTITY_FIELD(std::optional<QUuid>, client_id)
	ENTITY_FIELD(std::optional<QUuid>, branch_id)
	ENTITY_FIELD(QDateTime, signing_date)
	ENTITY_FIELD(qreal, prepayment)
	ENTITY_FIELD(std::optional<QDateTime>, completion_date)

	ENTITY_FIELD_DATA_BEGIN(Contract)
		ENTITY_FIELD_DATA(Contract, 
			client_id,			
			ValidatorsFactory::nullable(ValidatorsFactory::uuid()),
			false
		)

		ENTITY_FIELD_DATA(Contract, 
			branch_id,			
			ValidatorsFactory::nullable(ValidatorsFactory::uuid()),
			false
		)

		ENTITY_FIELD_DATA(Contract, 
			signing_date,		
			ValidatorsFactory::date(Field<QDateTime>::format),
			false
		)

		ENTITY_FIELD_DATA(Contract,
			prepayment,		
			ValidatorsFactory::real_range(0, 10000, 3),		
			false
		)

		ENTITY_FIELD_DATA(Contract, 
			completion_date,	
			ValidatorsFactory::nullable(ValidatorsFactory::date(Field<QDateTime>::format)),
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop
