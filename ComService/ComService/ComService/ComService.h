#ifndef COMSERVICE_H
#define COMSERVICE_H

#include <QObject>
#include "ComConfig.h"
#include "ComShareMemory.h"


#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(ComServiceLog)


class ComService : public QObject
{
    Q_OBJECT
public:
    explicit ComService(QObject *parent = nullptr);
    ~ComService();
    bool Load(QString cfg_xml);
signals:

private:
    ComConfig      &m_ComConfig      = *ComConfig::instance();
    ComShareMemory &m_ComShareMemory = *ComShareMemory::instance();

};

#endif // COMSERVICE_H
