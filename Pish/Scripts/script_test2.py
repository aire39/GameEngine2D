from math import *
import time

mms = pshGE.SceneManage(0)

mobj = mms.getSceneObject("object_0")

mobj2 = mms.getSceneObject("object_2")

mobj1 = mms.getSceneObject("object_1")

mobj2.setScale(mobj1.getPosition().getx(), mobj1.getPosition().gety(), mobj1.getPosition().getx())

mobj.setScale(mobj1.getPosition().getx(), mobj1.getPosition().gety(), mobj1.getPosition().getx())

mobj2.setPosition(13.0, 10.0*sin(time.clock()*10.0), 0.0)

mobj.setPosition(5.0*cos(time.clock()*10.0)-5.0, mobj2.getPosition().gety()*sin(time.clock()*10.0), 0.0)

mobj.setColor(mobj2.getPosition().getx()/10.0,mobj2.getPosition().gety()/10.0, mobj2.getPosition().getz()/10.0, 1.0)

#print(mobj2.getPosition().getx()/10.0, mobj2.getPosition().gety()/10.0, mobj2.getPosition().getz())

#print(mobj.getPosition().getx()/10.0, mobj.getPosition().gety()/10.0, mobj.getPosition().getz())getx()/10.0, mobj.getPosition().gety()/10.0, mobj.getPosition().getz())