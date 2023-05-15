#pragma once

#include <QHash>
#include <QString>
#include "staticlookup.h"
#include "../entitypresenterbase.h"

namespace ComputerWorkshop {

class EntitiesLookup final : public IStaticLookup<EntitiesLookup> {
public:
	QList<QString> get_alias_values() const override final {
		return entities_forward_map_.keys();
	}

	QString get_source_by_alias(const QString& alias) override final {
		return entities_forward_map_.value(alias);
	}

	QString get_alias_by_source(const QString& src) override final {
		return entities_reversed_map_.value(src);
	}

private:
	void setup_once() override final {
		const auto& presenters = IEntityPresenter::get_entity_presenters();

		for (auto& ent : presenters.keys()) {
			auto display_name = presenters.value(ent)->get_entity_display_name();

			if (ent == display_name) continue;
			
			entities_forward_map_.insert(display_name, ent);
			entities_reversed_map_.insert(ent, display_name);
		}
	}

private:
	inline static QHash<QString, QString> entities_forward_map_;
	inline static QHash<QString, QString> entities_reversed_map_;
};

} // namespace ComputerWorkshop