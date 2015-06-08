import time
from math import *

##Get Scene

mms = pshGE.SceneManage(0)

##Get Scene Objects

object_2 = mms.getSceneObject("object_2")
object_1 = mms.getSceneObject("object_1")
object_0_bound = mms.getSceneObject("object_0")

##Set Object that is to act as a boundary

object_0_bound.setPosition(-17.5, object_0_bound.getPosition().gety(), 1.0)
object_0_bound.setScale(1.0, 2.5, 1.0)
tmp_vec = object_0_bound.getPosition()

object_0_bound.setPosition(0.0,0.0,0.0)
object_0_bound.setScale(15.0,15.0,1.0)

##ballvec had to be defined once and then comented out to act like a global variable. I need to ome up with something to avoid this.
#ballvec = pshvec3 
#ballvec.setx(0.01)
#ballvec.sety(0.01)

##Set Default Movement
object_2.setPosition(14.0, object_1.getPosition().gety(), 1.0)
object_2.setScale(1.0, 2.5, 1.0)

##Set conditions

#had if (time.clock()%1.0) < 0.002 but it runs slow since I update once a second

object_1.setPosition( object_1.getPosition().getx()+ballvec.getx(), object_1.getPosition().gety()+ballvec.gety(), 1.0  )
if pshObjectTests.object_intersect_test(object_1, object_0_bound) == True:
 print("object is in court")
 object_1.setColor(abs(object_1.getPosition().getx())/15.0, abs(object_1.getPosition().gety())/15.0, 1.0, 1.0)
else:
 print("object is out of court!")
 #object_1.setPosition(0.0, 0.0, 0.0)
 ballvec.setx(-ballvec.getx())
 ballvec.sety(-ballvec.gety())
 object_1.setPosition( object_1.getPosition().getx()+ballvec.getx(), object_1.getPosition().gety()+ballvec.gety(), 1.0  )
 

##Return Object used for boundary back to normal

object_0_bound.setPosition(tmp_vec.getx(), tmp_vec.gety(), tmp_vec.getz())
object_0_bound.setScale(1.0, 2.5, 1.0)