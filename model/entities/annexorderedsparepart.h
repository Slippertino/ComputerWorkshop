#pragma once

#include "entity.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_BEGIN(AnnexOrderedSparePart)
	ENTITY_NAME(annex_ordered_spare_parts)

	ENTITY_FIELD(QUuid, annex_id)
	ENTITY_FIELD(QString, name)
	ENTITY_FIELD(qreal, cost)
	ENTITY_FIELD(QDateTime, order_date)
	ENTITY_FIELD(std::optional<QDateTime>, order_receipt_date)
	ENTITY_FIELD(qint32, warranty_days)
	ENTITY_FIELD(qreal, discount)
	ENTITY_FIELD(qint32, count)
	ENTITY_FIELD(std::optional<qreal>, amount)

	ENTITY_FIELD_DATA_BEGIN(AnnexOrderedSparePart)
		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			annex_id,				
			ValidatorsFactory::uuid(),											
			false
		)

		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			name,					
			ValidatorsFactory::string_size(0, 50),								
			false
		)

		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			cost,					
			ValidatorsFactory::real_range(0.001, std::nullopt, 3),				
			false
		)

		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			order_date,			
			ValidatorsFactory::date(Field<QDateTime>::format),
			false
		)

		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			order_receipt_date,
			ValidatorsFactory::nullable(ValidatorsFactory::date(Field<QDateTime>::format)),
			false
		)

		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			warranty_days,			
			ValidatorsFactory::int_range(0, 120),								
			false
		)

		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			discount,				
			ValidatorsFactory::real_range(0, 50, 2),							
			false
		)

		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			count,					
			ValidatorsFactory::int_range(1, std::nullopt),						
			false
		)

		ENTITY_FIELD_DATA(AnnexOrderedSparePart, 
			amount,				
			ValidatorsFactory::nullable(ValidatorsFactory::real_range(0.001, std::nullopt, 3)),
			false
		)

	ENTITY_FIELD_DATA_END()

DECLARE_ENTITY_END()

} // namespace ComputerWorkshop