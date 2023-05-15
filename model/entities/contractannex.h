#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(ContractAnnex)
	ENTITY_NAME(contract_annexes)

	ENTITY_FIELD(QUuid, contract_id)
	ENTITY_FIELD(std::optional<QDateTime>, issue_date)

	ENTITY_FIELD_DATA_BEGIN(ContractAnnex)
		ENTITY_FIELD_DATA(ContractAnnex, 
			contract_id,	
			ValidatorsFactory::uuid(),				
			false
		)

		ENTITY_FIELD_DATA(ContractAnnex, 
			issue_date,	
			ValidatorsFactory::nullable(ValidatorsFactory::date(Field<QDateTime>::format)),	
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop