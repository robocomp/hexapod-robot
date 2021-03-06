#
# Copyright (C) 2017 by YOUR NAME HERE
#
#    This file is part of RoboComp
#
#    RoboComp is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    RoboComp is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
#

import sys, os, traceback, time
from PySide import *
from genericworker import *

class SpecificWorker(GenericWorker):
	def __init__(self, proxy_map):
		super(SpecificWorker, self).__init__(proxy_map)
		self.timer.timeout.connect(self.compute)
		self.Period = 100
		self.timer.start(self.Period)

	def seParams(self, params):
		try:
			par = params["InnerModelPath"]
			innermodel_path=par.value
			innermodel = InnerModel(innermodel_path)
		except:
			traceback.print_exc()
			print "Error reading config params"
		return True

	@QtCore.Slot()
	def compute(self):
		print 'SpecificWorker.compute...'
		readMotors()
		try:
			stateTripod = tripodcontroller_proxy.getState()
			
		except Ice.Exception, e:
			traceback.print_exc()
			print e
			
		if self.newAction == "ROWING":
			pass
		if self.newAction == "PADDLING":
			pass
		if self.newAction == "STOP":
			pass
		if self.newAction == "HOME":
			pass
			
		return True


########################################################################

	def readMotors(self):
		motorsState = {}
		motorsState = self._proxy.jointmotor_proxy.getAllMotorsState()
			
		for motor in motorsState:
			print motor[""].pos
			innerModel.getNode(motor).set	

	
	def rowing(self):


########################################################################

	#
	# action
	#
	def action(self, act):
		#
		#implementCODE
		#
		pass


	#
	# getState
	#
	def getState(self):
		ret = State()
		#
		#implementCODE
		#
		return ret





