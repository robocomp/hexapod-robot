/*
 *    Copyright (C) 2016 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GENERICWORKER_H
#define GENERICWORKER_H

#include "config.h"
#include <QtGui>
#include <stdint.h>
#include <qlog/qlog.h>

#include <qt4/QtCore/qstatemachine.h>
#include <qt4/QtCore/qstate.h>
#include <CommonBehavior.h>

#include <JointMotor.h>
#include <LegController.h>
#include <FootPreassureSensor.h>
#include <IMU.h>

#define CHECK_PERIOD 5000
#define BASIC_PERIOD 100

typedef map <string,::IceProxy::Ice::Object*> MapPrx;

using namespace std;

using namespace RoboCompLegController;
using namespace RoboCompIMU;
using namespace RoboCompJointMotor;
using namespace RoboCompFootPreassureSensor;




class GenericWorker : 
public QObject
{
Q_OBJECT
public:
	GenericWorker(MapPrx& mprx);
	virtual ~GenericWorker();
	virtual void killYourSelf();
	virtual void setPeriod(int p);
	
	virtual bool setParams(RoboCompCommonBehavior::ParameterList params) = 0;
	QMutex *mutex;
	

	IMUPrx imu_proxy;
	FootPreassureSensorPrx footpreassuresensor_proxy;
	JointMotorPrx jointmotor_proxy;

	virtual StateLeg getStateLeg() = 0;
	virtual void move(const float x, const float y, const string &state) = 0;
	virtual bool setListIKLeg(const ListPoseLeg &ps, const bool &simu) = 0;
	virtual bool setIKLeg(const PoseLeg &p, const bool &simu) = 0;
	virtual bool setIKBody(const PoseBody &p, const bool &simu) = 0;
	virtual bool setFKLeg(const AnglesLeg &al, const bool &simu) = 0;

protected:
//State Machine
	QStateMachine hexapod;

	QState *empujar = new QState();
	QState *paso = new QState();

//-------------------------

	QTimer timer;
	int Period;

private:


public slots:
//Slots funtion State Machine
	virtual void fun_empujar() = 0;
	virtual void fun_paso() = 0;

//-------------------------
signals:
	void kill();
//Signals for State Machine
	void pasotopaso();
	void pasotoempujar();
	void empujartoempujar();
	void empujartopaso();

//-------------------------
};

#endif