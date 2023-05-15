#pragma once

#include <optional>
#include <QUuid>
#include <QString>
#include <QDateTime>
#include <QVariant>

namespace ComputerWorkshop {

struct IField {
	virtual QVariant get() const = 0;
	virtual void set(const QVariant& val) = 0;
};

template<class T>
struct Field { };

template<>
struct Field<QString> final : public IField {
	QString value;

	QVariant get() const override final {
        return value.isEmpty() ? QVariant() : value;
	}

	void set(const QVariant& val) override final {
		value = val.toString();
	}
};

template<>
struct Field<QUuid> final : public IField {
	QUuid value;

	QVariant get() const override final {
		return value.toString(QUuid::WithoutBraces);
	}

	void set(const QVariant& val) override final {
		value = val.toUuid();
	}
};

template<>
struct Field<qint16> final : public IField {
    qint16 value;

    QVariant get() const override final {
        return value;
    }

    void set(const QVariant& val) override final {
        value = val.toInt();
    }
};

template<>
struct Field<qint32> final : public IField {
	qint32 value;

	QVariant get() const override final {
		return value;
	}

	void set(const QVariant& val) override final {
		value = val.toInt();
	}
};

template<>
struct Field<qreal> final : public IField {
    qreal value;

    QVariant get() const override final {
        return value;
    }

    void set(const QVariant& val) override final {
        value = val.toReal();
    }
};

template<>
struct Field<QDateTime> final : public IField {
	inline static const QString format = "yyyy-MM-dd hh:mm";

	QDateTime value;

	QVariant get() const override final {
		auto res = value.toString(format);
		return res;
	}

	void set(const QVariant& val) override final {
		value = (val.type() == val.String) 
			? QDateTime::fromString(val.toString(), format) 
			: val.toDateTime();
	}
};

template<class T>
struct Field<std::optional<T>> final : public IField {
	std::optional<T> value = std::nullopt;

	QVariant get() const override final {
		QVariant res;
		if (value.has_value()) {
			Field<T> temp;
			temp.value = value.value();
			res = temp.get();
		}

		return res;
	}

	void set(const QVariant& val) override final {
		if (val.isNull() || 
			!val.isValid() || 
			val.toString().isEmpty()) {
			value = std::nullopt;
		}

		Field<T> temp;
		temp.set(val);
		value = temp.value;
	}
};

} // namespace ComputerWorkshop
