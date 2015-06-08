#Code to test objects 
#intersecting with each other

import time

mms = pshGE.SceneManage(0)

mobj1 = mms.getSceneObject("object_0")

mobj2 = mms.getSceneObject("object_2")

mobj4 = mms.getSceneObject("object_1")

mobj1.setPosition(mobj1.getPosition().getx(), mobj1.getPosition().gety()-0.1, mobj1.getPosition().getz())

#print(pshObjectTests.object_intersect_test(mobj1, mobj2))

if pshObjectTests.object_intersect_test(mobj1, mobj2) is True:
 mobj1.setColor(1.0, 0.0, 0.0, 1.0)
 mobj1.setPosition(mobj1.getPosition().getx(), mobj1.getPosition().gety()+0.1, mobj1.getPosition().getz())
else:
 mobj1.setColor(1.0, 1.0, 1.0, 1.0)

mobj4.setRotation(time.clock()*100000000.0)