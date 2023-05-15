#pragma once

#include "../model/entities/entities.h"
#include "entitypresenter.h"

namespace ComputerWorkshop {

DECLARE_ENTITY_PRESENTER_BEGIN(BranchesPresenter, Branch)
	ENTITY_DISPLAY_NAME(Филиалы)
	ENTITY_ALIASES(Электронная почта, Город)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(email,			Электронная почта,	new EditInput(EditPlaceholdersFactory::email))
		EP_FIELD_DATA(city,				Город,				new EditInput(EditPlaceholdersFactory::string_size(3, 20)))
		EP_FIELD_DATA(address,			Адрес,				new EditInput(EditPlaceholdersFactory::string_size(5, 50)))
		EP_FIELD_DATA(working_hours,	График работы,		new EditInput(EditPlaceholdersFactory::working_hours))
		EP_FIELD_DATA(phone,			Телефон,			new EditInput(EditPlaceholdersFactory::phone))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(EmployeesPresenter, Employee)
	ENTITY_DISPLAY_NAME(Работники)
	ENTITY_ALIASES(ФИО, Телефон)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(branch_id,			Филиал,				new LookupInput(new EntityIdAliasesLookup<Branch>()))
		EP_FIELD_DATA(full_name,			ФИО,				new EditInput(EditPlaceholdersFactory::string_size(10, 100)))
		EP_FIELD_DATA(phone,				Телефон,			new EditInput(EditPlaceholdersFactory::phone))
		EP_FIELD_DATA(position,				Должность,			new EditInput(EditPlaceholdersFactory::string_size(7, 20)))
		EP_FIELD_DATA(week_working_rate,	Рабочая нагрузка,	new EditInput(EditPlaceholdersFactory::number_range<quint16>(1, 51)))
		EP_FIELD_DATA(salary,				Зарплата,			new EditInput(EditPlaceholdersFactory::number_range<qreal>(0, 50000)))
		EP_FIELD_DATA(email,				Электронная почта,	new EditInput(EditPlaceholdersFactory::email))
		EP_FIELD_DATA(working_hours,		График работы,		new EditInput(EditPlaceholdersFactory::working_hours))
		EP_FIELD_DATA(link_to_contract,		Ссылка на договор,	new EditInput(EditPlaceholdersFactory::string_size(10, 255)))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(ClientsPresenter, Client)
	ENTITY_DISPLAY_NAME(Клиенты)
	ENTITY_ALIASES(ФИО, Телефон, Электронная почта)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(full_name,	ФИО,				new EditInput(EditPlaceholdersFactory::string_size(10, 100)))
		EP_FIELD_DATA(phone,		Телефон,			new EditInput(EditPlaceholdersFactory::phone))
		EP_FIELD_DATA(email,		Электронная почта,	new EditInput(EditPlaceholdersFactory::email))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(ContractsPresenter, Contract)
	ENTITY_DISPLAY_NAME(Договоры)
	ENTITY_ALIASES(Идентификатор)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(client_id,		Идентификатор клиента,	new LookupInput(new EntityIdAliasesLookup<Client>()))
		EP_FIELD_DATA(branch_id,		Идентификатор филиала,	new LookupInput(new EntityIdAliasesLookup<Branch>()))
		EP_FIELD_DATA(signing_date,		Дата заключения,		new EditInput(EditPlaceholdersFactory::date))
		EP_FIELD_DATA(prepayment,		Предоплата,				new EditInput(EditPlaceholdersFactory::number_range<qreal>(0, 10000)))
		EP_FIELD_DATA(completion_date,	Дата завершения,		new EditInput(EditPlaceholdersFactory::date))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(ContractAnnexesPresenter, ContractAnnex)
	ENTITY_DISPLAY_NAME(Приложения к договорам)
	ENTITY_ALIASES(Идентификатор)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(contract_id,	Идентификатор договора, new LookupInput(new EntityIdAliasesLookup<Contract>()))
		EP_FIELD_DATA(issue_date,	Дата получения,			new EditInput(EditPlaceholdersFactory::date))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(EmbeddedServicesPresenter, EmbeddedService)
	ENTITY_DISPLAY_NAME(Услуги)
	ENTITY_ALIASES(Название)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(name,	Название,	new EditInput(EditPlaceholdersFactory::string_size(10, 100)))
		EP_FIELD_DATA(cost,	Стоимость,	new EditInput(EditPlaceholdersFactory::number_range<qreal>(0, 10000)))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(AnnexEmbeddedServicesPresenter, AnnexEmbeddedService)
	ENTITY_DISPLAY_NAME(Услуги приложений)
	ENTITY_ALIASES(Идентификатор)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(annex_id,				Идентификатор приложения,	new LookupInput(new EntityIdAliasesLookup<ContractAnnex>()))
		EP_FIELD_DATA(embedded_service_id,	Идентификатор услуги,		new LookupInput(new EntityIdAliasesLookup<EmbeddedService>()))
		EP_FIELD_DATA(warranty_days,		Гарантия,					new EditInput(EditPlaceholdersFactory::number_range<quint32>(0, 120)))
		EP_FIELD_DATA(discount,				Скидка,						new EditInput(EditPlaceholdersFactory::number_range<qreal>(0.00, 0.50)))
		EP_FIELD_DATA(count,				Количество,					new EditInput(EditPlaceholdersFactory::number_range<quint32>(1, std::nullopt)))
		EP_FIELD_DATA(amount,				Итоговая цена,				new EditInput(EditPlaceholdersFactory::number_range<qreal>(0.001, std::nullopt)))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(AnnexOrderedSparePartsPresenter, AnnexOrderedSparePart)
	ENTITY_DISPLAY_NAME(Запчасти приложений)
	ENTITY_ALIASES(Идентификатор)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(annex_id,				Идентификатор приложения,	new LookupInput(new EntityIdAliasesLookup<ContractAnnex>()))
		EP_FIELD_DATA(name,					Название запчасти,			new EditInput(EditPlaceholdersFactory::string_size(0, 50)))
		EP_FIELD_DATA(cost,					Цена запчасти,				new EditInput(EditPlaceholdersFactory::number_range<qreal>(0.001, std::nullopt)))
		EP_FIELD_DATA(order_date,			Дата заказа,				new EditInput(EditPlaceholdersFactory::date))
		EP_FIELD_DATA(order_receipt_date,	Дата получения,				new EditInput(EditPlaceholdersFactory::date))
		EP_FIELD_DATA(warranty_days,		Гарантия,					new EditInput(EditPlaceholdersFactory::number_range<quint32>(0, 120)))
		EP_FIELD_DATA(discount,				Скидка,						new EditInput(EditPlaceholdersFactory::number_range<qreal>(0.00, 0.50)))
		EP_FIELD_DATA(count,				Количество,					new EditInput(EditPlaceholdersFactory::number_range<quint32>(1, std::nullopt)))
		EP_FIELD_DATA(amount,				Итоговая цена,				new EditInput(EditPlaceholdersFactory::number_range<qreal>(0.001, std::nullopt)))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(UsersPresenter, User)
	ENTITY_DISPLAY_NAME(Пользователи)
	ENTITY_ALIASES(Логин)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(login,		Логин,		new EditInput(EditPlaceholdersFactory::string_size(5, 30)))
		EP_FIELD_DATA(employee_id,	Работник,	new LookupInput(new EntityIdAliasesLookup<Employee>()))
		EP_FIELD_DATA(password,		Пароль,		new EditInput)
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()


DECLARE_ENTITY_PRESENTER_BEGIN(RightsPresenter, Right)
	ENTITY_DISPLAY_NAME(Права доступа)
	ENTITY_ALIASES(Идентификатор)
	DECLARE_EP_FIELDS_DATA_BEGIN()
		EP_FIELD_DATA(user_id,		Пользователь,		new LookupInput(new EntityIdAliasesLookup<User>()))
		EP_FIELD_DATA(entity,		Таблица,			new LookupInput(new EntitiesLookup()))
		EP_FIELD_DATA(op,			Доступные операции, new LookupInput(new OperationRightNamesLookup()))
	DECLARE_EP_FIELDS_DATA_END()
DECLARE_ENTITY_PRESENTER_END()

} // namespace ComputerWorkshop