#pragma once

#include <optional>
#include <type_traits>
#include <QString>

namespace ComputerWorkshop {

class EditPlaceholdersFactory {
public:
	inline static const QString email			= "yourmail@domain.com";
	inline static const QString phone			= "+7 999 777 22 33";
	inline static const QString working_hours	= "10:00 - 18:00";
	inline static const QString date			= "2010-02-23 10:11";

	static QString string_size(std::optional<quint32> min, std::optional<quint32> max) {
		QString res;
		if (min.has_value()) res += QString("oт %1 ").arg(min.value());
		if (max.has_value()) res += QString("до %2 ").arg(max.value());
		
		if (!res.isEmpty()) {
			res += "символов";
		}

		return res;
	}

	template<class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
	static QString number_range(std::optional<T> min, std::optional<T> max) {
		QString res;
		if (min.has_value()) res += QString("oт %1 ").arg(QString::number(min.value()));
		if (max.has_value()) res += QString("до %2 ").arg(QString::number(max.value()));

		return res;
	}
};

} // namespace ComputerWorkshop