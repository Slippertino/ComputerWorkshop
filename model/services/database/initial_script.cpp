#include "database.h"

const QList<QString> ComputerWorkshop::Database::initial_script_ = {
	"\nCREATE DATABASE %1"
	,

	"\nUSE %1"
	,

	"\nCREATE TABLE annex_embedded_services"
	"\n("
	"\n    id UNIQUEIDENTIFIER NOT NULL,"
	"\n    annex_id UNIQUEIDENTIFIER NOT NULL,"
	"\n    warranty_days INTEGER NOT NULL,"
	"\n    discount FLOAT NOT NULL,"
	"\n    count INTEGER NOT NULL,"
	"\n    amount MONEY,"
	"\n    embedded_service_id UNIQUEIDENTIFIER"
	"\n)"
	,

	"\nALTER TABLE annex_embedded_services "
	"\nADD "
	"\nCHECK(warranty_days BETWEEN 0 AND 120)"

	,

	"\nALTER TABLE annex_embedded_services"
	"\nADD"
	"\nCHECK(discount BETWEEN 0 AND 30)"
	,

	"\nALTER TABLE annex_embedded_services"
	"\nADD"
	"\nCHECK(count > 0)"
	,

	"\nALTER TABLE annex_embedded_services"
	"\nADD"
	"\nCHECK(amount > 0 OR amount IS NULL)"
	,

	"\nALTER TABLE annex_embedded_services ADD CONSTRAINT annex_embedded_service_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\nALLOW_PAGE_LOCKS = ON,"
	"\nALLOW_ROW_LOCKS = ON)"
	,

	"\nCREATE TABLE annex_ordered_spare_parts"
	"\n("
	"\n    id UNIQUEIDENTIFIER NOT NULL,"
	"\n    annex_id UNIQUEIDENTIFIER NOT NULL,"
	"\n    warranty_days INTEGER NOT NULL,"
	"\n    discount FLOAT NOT NULL,"
	"\n    count INTEGER NOT NULL,"
	"\n    amount MONEY,"
	"\n    name NVARCHAR(50) NOT NULL,"
	"\n    cost MONEY NOT NULL,"
	"\n    order_date DATETIME NOT NULL,"
	"\n    order_receipt_date DATETIME"
	"\n)"
	,

	"\nALTER TABLE annex_ordered_spare_parts "
	"\nADD "
	"\nCHECK(warranty_days BETWEEN 0 AND 120)"

	,

	"\nALTER TABLE annex_ordered_spare_parts"
	"\nADD"
	"\nCHECK(discount BETWEEN 0 AND 50)"
	,

	"\nALTER TABLE annex_ordered_spare_parts"
	"\nADD"
	"\nCHECK(count > 0)"
	,

	"\nALTER TABLE annex_ordered_spare_parts"
	"\nADD"
	"\nCHECK(amount > 0 OR amount IS NULL)"

	,

	"\nALTER TABLE annex_ordered_spare_parts"
	"\nADD"
	"\nCHECK(cost > 0)"
	,

	"\nALTER TABLE annex_ordered_spare_parts ADD CONSTRAINT annex_ordered_spare_part_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\n   ALLOW_PAGE_LOCKS = ON,"
	"\n   ALLOW_ROW_LOCKS = ON)"
	,

	"\nCREATE TABLE branches"
	"\n("
	"\n    id UNIQUEIDENTIFIER NOT NULL,"
	"\n    email NVARCHAR(50) NOT NULL,"
	"\n    city NVARCHAR(20) NOT NULL,"
	"\n    address NVARCHAR(50) NOT NULL,"
	"\n    working_hours NVARCHAR(15) NOT NULL,"
	"\n    phone NVARCHAR(20)"
	"\n)"
	,

	"\nALTER TABLE branches"
	"\nADD"
	"\nCHECK(email LIKE('_%@_%._%'))"
	,

	"\nALTER TABLE branches"
	"\nADD"
	"\nCHECK(working_hours LIKE('[0-9][0-9]:[0-9][0-9] - [0-9][0-9]:[0-9][0-9]'))"
	,

	"\nALTER TABLE branches"
	"\nADD"
	"\nCHECK(phone LIKE('+7 [0-9][0-9][0-9] [0-9][0-9][0-9] [0-9][0-9] [0-9][0-9]') OR phone IS NULL)"
	,

	"\nALTER TABLE branches ADD CONSTRAINT branch_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\nALLOW_PAGE_LOCKS = ON,"
	"\nALLOW_ROW_LOCKS = ON)"
	,
	"\nALTER TABLE branches ADD CONSTRAINT branch_email_un UNIQUE NONCLUSTERED(email)"
	,

	"\nCREATE TABLE clients"
	"\n("
	"\n    id UNIQUEIDENTIFIER NOT NULL,"
	"\n    full_name NVARCHAR(100) NOT NULL,"
	"\n    phone NVARCHAR(20) NOT NULL,"
	"\n    email NVARCHAR(50)"
	"\n)"
	,

	"\nALTER TABLE clients"
	"\nADD"
	"\nCHECK(phone LIKE('+7 [0-9][0-9][0-9] [0-9][0-9][0-9] [0-9][0-9] [0-9][0-9]'))"
	,

	"\nALTER TABLE clients"
	"\nADD"
	"\nCHECK(email LIKE('_%@_%._%') OR email IS NULL)"
	,

	"\nALTER TABLE clients ADD CONSTRAINT client_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\n   ALLOW_PAGE_LOCKS = ON,"
	"\n   ALLOW_ROW_LOCKS = ON)"
	,
	"\nALTER TABLE clients ADD CONSTRAINT client_full_name_phone_un UNIQUE NONCLUSTERED(full_name, phone)"
	,

	"\nCREATE TABLE contract_annexes"
	"\n("
	"\n   id UNIQUEIDENTIFIER NOT NULL,"
	"\n   contract_id UNIQUEIDENTIFIER NOT NULL,"
	"\n   issue_date DATETIME"
	"\n)"
	,

	"\nALTER TABLE contract_annexes ADD CONSTRAINT contract_annex_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\n   ALLOW_PAGE_LOCKS = ON,"
	"\n   ALLOW_ROW_LOCKS = ON)"
	,

	"\nCREATE TABLE contracts"
	"\n("
	"\n   id UNIQUEIDENTIFIER NOT NULL,"
	"\n   client_id UNIQUEIDENTIFIER,"
	"\n   branch_id UNIQUEIDENTIFIER,"
	"\n   signing_date DATETIME NOT NULL,"
	"\n   prepayment MONEY NOT NULL,"
	"\n   completion_date DATETIME"
	"\n)"
	,

	"\nALTER TABLE contracts"
	"\nADD"
	"\nCHECK(prepayment BETWEEN 0 AND 10000)"
	,

	"\nALTER TABLE contracts ADD CONSTRAINT contract_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\n   ALLOW_PAGE_LOCKS = ON,"
	"\n   ALLOW_ROW_LOCKS = ON)"
	,

	"\nCREATE TABLE embedded_services"
	"\n("
	"\n   id UNIQUEIDENTIFIER NOT NULL,"
	"\n   name NVARCHAR(100) NOT NULL,"
	"\n   cost MONEY NOT NULL"
	"\n)"
	,

	"\nALTER TABLE embedded_services"
	"\nADD"
	"\nCHECK(cost BETWEEN 0 AND 10000)"
	,

	"\nALTER TABLE embedded_services ADD CONSTRAINT embedded_service_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\n   ALLOW_PAGE_LOCKS = ON,"
	"\n   ALLOW_ROW_LOCKS = ON)"
	,

	"\nCREATE TABLE employees"
	"\n("
	"\n   id UNIQUEIDENTIFIER NOT NULL,"
	"\n   branch_id UNIQUEIDENTIFIER,"
	"\n   full_name NVARCHAR(100) NOT NULL,"
	"\n   phone NVARCHAR(20) NOT NULL,"
	"\n   position NVARCHAR(20) NOT NULL,"
	"\n   week_working_rate SMALLINT NOT NULL,"
	"\n   salary MONEY NOT NULL,"
	"\n   email NVARCHAR(50),"
	"\n   working_hours NVARCHAR(15),"
	"\n   link_to_contract NVARCHAR(255)"
	"\n)"
	,

	"\nALTER TABLE employees"
	"\nADD"
	"\nCHECK(phone LIKE('+7 [0-9][0-9][0-9] [0-9][0-9][0-9] [0-9][0-9] [0-9][0-9]'))"
	,

	"\nALTER TABLE employees"
	"\nADD"
	"\nCHECK(week_working_rate BETWEEN 1 AND 40)"
	,

	"\nALTER TABLE employees"
	"\nADD"
	"\nCHECK(salary BETWEEN 0 AND 500000)"
	,

	"\nALTER TABLE employees"
	"\nADD"
	"\nCHECK(email LIKE('_%@_%._%') OR email IS NULL)"
	,

	"\nALTER TABLE employees"
	"\nADD"
	"\nCHECK(working_hours LIKE('[0-9][0-9]:[0-9][0-9] - [0-9][0-9]:[0-9][0-9]') OR working_hours IS NULL)"
	,

	"\nALTER TABLE employees ADD CONSTRAINT employee_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\n   ALLOW_PAGE_LOCKS = ON,"
	"\n   ALLOW_ROW_LOCKS = ON)"
   
	,

	"\nALTER TABLE employees ADD CONSTRAINT employee_full_name_phone_un UNIQUE NONCLUSTERED(full_name, phone)"
	,

	"\nALTER TABLE annex_embedded_services"
	"\nADD CONSTRAINT annex_embedded_service_contract_annex_fk FOREIGN KEY"
	"\n("
	"\n   annex_id"
	"\n)"
	"\nREFERENCES contract_annexes"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE CASCADE"
	"\nON UPDATE CASCADE"
	,

	"\nALTER TABLE annex_embedded_services"
	"\nADD CONSTRAINT annex_embedded_service_embedded_service_fk FOREIGN KEY"
	"\n("
	"\n   embedded_service_id"
	"\n)"
	"\nREFERENCES embedded_services"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE SET NULL"
	"\nON UPDATE SET NULL"
	,

	"\nALTER TABLE annex_ordered_spare_parts"
	"\nADD CONSTRAINT annex_ordered_spare_part_contract_annex_fk FOREIGN KEY"
	"\n("
	"\n   annex_id"
	"\n)"
	"\nREFERENCES contract_annexes"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE CASCADE"
	"\nON UPDATE CASCADE"
	,

	"\nALTER TABLE contract_annexes"
	"\nADD CONSTRAINT contract_annex_contract_fk FOREIGN KEY"
	"\n("
	"\n   contract_id"
	"\n)"
	"\nREFERENCES contracts"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE CASCADE"
	"\nON UPDATE CASCADE"
	,

	"\nALTER TABLE contracts"
	"\nADD CONSTRAINT contract_branch_fk FOREIGN KEY"
	"\n("
	"\n   branch_id"
	"\n)"
	"\nREFERENCES branches"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE SET NULL"
	"\nON UPDATE CASCADE"
	,

	"\nALTER TABLE contracts"
	"\nADD CONSTRAINT contract_client_fk FOREIGN KEY"
	"\n("
	"\n    client_id"
	"\n)"
	"\nREFERENCES clients"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE SET NULL"
	"\nON UPDATE CASCADE"
	,

	"\nALTER TABLE employees"
	"\nADD CONSTRAINT employee_branch_fk FOREIGN KEY"
	"\n("
	"\n    branch_id"
	"\n)"
	"\nREFERENCES branches"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE NO ACTION"
	"\nON UPDATE CASCADE"
	,

	"\nCREATE TABLE users"
	"\n("
	"\n	id UNIQUEIDENTIFIER NOT NULL,"
	"\n	login NVARCHAR(30) NOT NULL,"
	"\n	employee_id UNIQUEIDENTIFIER,"
	"\n	password NVARCHAR(255) NOT NULL"
	"\n)"
	,

	"\nALTER TABLE users ADD CONSTRAINT user_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\n   ALLOW_PAGE_LOCKS = ON,"
	"\n   ALLOW_ROW_LOCKS = ON)"

	,

	"\nALTER TABLE users ADD CONSTRAINT user_login_un UNIQUE NONCLUSTERED(login)"
	
	,

	"\nALTER TABLE users"
	"\nADD CONSTRAINT user_employee_id_fk FOREIGN KEY"
	"\n("
	"\n   employee_id"
	"\n)"
	"\nREFERENCES employees"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE CASCADE"
	"\nON UPDATE CASCADE"

	,

	"\nINSERT INTO users VALUES(NEWID(), 'admin', NULL, '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918')"

	,

	"\nCREATE TABLE rights"
	"\n("
	"\n	id UNIQUEIDENTIFIER NOT NULL,"
	"\n user_id UNIQUEIDENTIFIER NOT NULL,"
	"\n entity NVARCHAR(50) NOT NULL,"
	"\n op SMALLINT NOT NULL"
	"\n)"

	,

	"\nALTER TABLE rights ADD CONSTRAINT right_pk PRIMARY KEY CLUSTERED(id)"
	"\nWITH("
	"\n   ALLOW_PAGE_LOCKS = ON,"
	"\n   ALLOW_ROW_LOCKS = ON)"

	,

	"\nALTER TABLE rights ADD CONSTRAINT right_user_id_entity_op UNIQUE NONCLUSTERED(user_id, entity)"

	,

	"\nALTER TABLE rights"
	"\nADD CONSTRAINT right_user_fk FOREIGN KEY"
	"\n("
	"\n   user_id"
	"\n)"
	"\nREFERENCES users"
	"\n("
	"\n   id"
	"\n)"
	"\nON DELETE CASCADE"
	"\nON UPDATE CASCADE"

	,

	"\nINSERT INTO rights VALUES(NEWID(), (SELECT id FROM users WHERE login = 'admin'), 'rights', 15)"
};