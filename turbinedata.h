#ifndef TURBINEDATA_H
#define TURBINEDATA_H

#include <QObject>
#include <QDebug>

class TurbineData : public QObject
{
    Q_OBJECT
public:
    explicit TurbineData(QObject *parent = nullptr);
    ~TurbineData();

    void setTurbineName(const QString &newTurbineName);
    void setWindSpeed(double newWindSpeed);
    void setPowerplant(const QString &newPowerplant);
    void setWindDirection(double newWindDirection);
    void setTemperature(double newTemperature);
    void setPressure(double newPressure);
    void setPowerOutput(double newPowerOutput);
    void setCountry(const QString &newCountry);
    void setPitchAngle(double newPitchAngle);
    void setBladeAngle(double newBladeAngle);
    void setYawDirection(double newYawDirection);


    QString country() const;
    QString turbineName() const;
    QString powerplant() const;
    double windSpeed() const;
    double powerOutput() const;
    double windDirection() const;
    double temperature() const;
    double pressure() const;
    double bladeAngle() const;
    double yawDirection() const;
    double pitchAngle() const;


    QString TurbineID() const;
    void setTurbineID(const QString &newTurbineID);

signals:

private:
    QString m_country = "";
    QString m_powerplant = "";
    QString m_turbineName = "";
    QString m_TurbineID = "";
    double m_windSpeed = 0.0;
    double m_windDirection = 0.0;
    double m_powerOutput = 0.0;
    double m_temperature = 0.0;
    double m_pressure = 0.0;
    double m_pitchAngle = 0.0;
    double m_bladeAngle = 0.0;
    double m_yawDirection = 0.0;

};


#endif // TURBINEDATA_H
