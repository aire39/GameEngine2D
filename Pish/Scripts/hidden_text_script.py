from math import *
import time

mms = pshGE.SceneManage(0)

mobj0 = mms.getSceneObject("object_0")

mobj1 = mms.getSceneObject("object_1")

mobj2 = mms.getSceneObject("object_2")

mobj1.setPosition(-10.0*cos(time.clock()*10.0), 10.0*sin(time.clock()*10.0), 1.0)

object_3.setText("Hidden Text Script")
object_3.setRenderable(False)

if pshObjectTests.object_intersect_test(mobj0, mobj2) == True:
 object_3.setRenderable(True)
 object_3.setColor(abs(mobj1.getPosition().getx()/10.0), abs(mobj1.getPosition().gety()/10.0), mobj1.getPosition().getz(), 1.0)
