#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(AnnexEmbeddedService)
	ENTITY_NAME(annex_embedded_services)

	ENTITY_FIELD(QUuid, annex_id)
	ENTITY_FIELD(std::optional<QUuid>, embedded_service_id)
	ENTITY_FIELD(qint32, warranty_days)
	ENTITY_FIELD(qreal, discount)
	ENTITY_FIELD(qint32, count)
	ENTITY_FIELD(std::optional<qreal>, amount)

	ENTITY_FIELD_DATA_BEGIN(AnnexEmbeddedService)
		ENTITY_FIELD_DATA(AnnexEmbeddedService, 
			annex_id,				
			ValidatorsFactory::uuid(),											
			false
		)

		ENTITY_FIELD_DATA(AnnexEmbeddedService, 
			embedded_service_id,	
			ValidatorsFactory::nullable(ValidatorsFactory::uuid()),
			false
		)

		ENTITY_FIELD_DATA(AnnexEmbeddedService, 
			warranty_days,			
			ValidatorsFactory::int_range(0, 120),								
			false
		)

		ENTITY_FIELD_DATA(AnnexEmbeddedService, 
			discount,				
			ValidatorsFactory::real_range(0, 50, 2),							
			false
		)

		ENTITY_FIELD_DATA(AnnexEmbeddedService, 
			count,					
			ValidatorsFactory::int_range(1, std::nullopt),						
			false
		)

		ENTITY_FIELD_DATA(AnnexEmbeddedService, 
			amount,					
			ValidatorsFactory::nullable(ValidatorsFactory::real_range(0.001, std::nullopt, 3)),
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop
