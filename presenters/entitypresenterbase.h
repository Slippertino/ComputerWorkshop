#pragma once

#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QString>
#include <QHash>
#include <views/datainputs/datainputbase.h>

namespace ComputerWorkshop {

class IEntityPresenter : public QObject {

	Q_OBJECT

public:
	inline static const QString pk_display_name = "Идентификатор";

public:
	IEntityPresenter() = delete;
	IEntityPresenter(const QString& tname) : table_name_(tname) 
	{ }
	
	static const QHash<QString, IEntityPresenter*>& get_entity_presenters() {
		return presenters_;
	}

	IEntityPresenter* get_presenter_by_name(const QString& name) {
		return presenters_.value(name);
	}

	virtual void setup() {
		presenters_.insert(table_name_, this);
		presenters_.insert(get_entity_display_name(), this);
	}

	virtual QString get_entity_display_name() const = 0;
	virtual QString get_name(const QString& name) const = 0;
	virtual const QList<QString>& get_alias_names() const = 0;

	virtual ~IEntityPresenter() = default;

private:
	inline static QHash<QString, IEntityPresenter*> presenters_;
	QString table_name_;
};

} // namespace ComputerWorkshop
