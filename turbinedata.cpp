#include "turbinedata.h"

TurbineData::TurbineData(QObject *parent)
    : QObject{parent}
{

}

TurbineData::~TurbineData()
{
    qDebug()<<Q_FUNC_INFO;
}

double TurbineData::pitchAngle() const
{
    return m_pitchAngle;
}

QString TurbineData::TurbineID() const
{
    return m_TurbineID;
}

void TurbineData::setTurbineID(const QString &newTurbineID)
{
    m_TurbineID = newTurbineID;
}

void TurbineData::setPitchAngle(double newPitchAngle)
{
    m_pitchAngle = newPitchAngle;
}

double TurbineData::bladeAngle() const
{
    return m_bladeAngle;
}

void TurbineData::setBladeAngle(double newBladeAngle)
{
    m_bladeAngle = newBladeAngle;
}

double TurbineData::yawDirection() const
{
    return m_yawDirection;
}

void TurbineData::setYawDirection(double newYawDirection)
{
    m_yawDirection = newYawDirection;
}

QString TurbineData::turbineName() const
{
    return m_turbineName;
}

void TurbineData::setTurbineName(const QString &newTurbineName)
{
    m_turbineName = newTurbineName;
}

double TurbineData::windSpeed() const
{
    return m_windSpeed;
}

void TurbineData::setWindSpeed(double newWindSpeed)
{
    m_windSpeed = newWindSpeed;
}

double TurbineData::windDirection() const
{
    return m_windDirection;
}

void TurbineData::setWindDirection(double newWindDirection)
{
    m_windDirection = newWindDirection;
}

double TurbineData::powerOutput() const
{
    return m_powerOutput;
}

void TurbineData::setPowerOutput(double newPowerOutput)
{
    m_powerOutput = newPowerOutput;
}

double TurbineData::temperature() const
{
    return m_temperature;
}

void TurbineData::setTemperature(double newTemperature)
{
    m_temperature = newTemperature;
}

double TurbineData::pressure() const
{
    return m_pressure;
}

QString TurbineData::country() const
{
    return m_country;
}

void TurbineData::setCountry(const QString &newCountry)
{
    m_country = newCountry;
}

QString TurbineData::powerplant() const
{
    return m_powerplant;
}

void TurbineData::setPowerplant(const QString &newPowerplant)
{
    m_powerplant = newPowerplant;
}

void TurbineData::setPressure(double newPressure)
{
    m_pressure = newPressure;
}

