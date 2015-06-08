#This script makes attached object follow 
#another object around

import time

mms = pshGE.SceneManage(0)
obj0 = mms.getSceneObject("object_0")

follow_vec = pshvec3
#follow_vec.setxyz(0.0, 0.0, 0.0)

if object_2.getPosition().getx() > obj0.getPosition().getx()-0.0:
 follow_vec.setxyz(follow_vec.getx()-0.0001, follow_vec.gety(), follow_vec.getz())
 object_2.setPosition(object_2.getPosition().getx()-0.001, object_2.getPosition().gety(), object_2.getPosition().getz())

if object_2.getPosition().getx() < obj0.getPosition().getx()+0.0:
 follow_vec.setxyz(follow_vec.getx()+0.0001, follow_vec.gety(), follow_vec.getz())
 object_2.setPosition(object_2.getPosition().getx()+0.001, object_2.getPosition().gety(), object_2.getPosition().getz())

if object_2.getPosition().gety() > obj0.getPosition().gety()-0.0:
 follow_vec.setxyz(follow_vec.getx(), follow_vec.gety()-0.0001, follow_vec.getz())
 object_2.setPosition(object_2.getPosition().getx(), object_2.getPosition().gety()-0.01, object_2.getPosition().getz())

if object_2.getPosition().gety() < obj0.getPosition().gety()+0.0:
 follow_vec.setxyz(follow_vec.getx(), follow_vec.gety()+0.0001, follow_vec.getz())
 object_2.setPosition(object_2.getPosition().getx(), object_2.getPosition().gety()+0.01, object_2.getPosition().getz())

object_2.setPosition(object_2.getPosition().getx()+follow_vec.getx(), object_2.getPosition().gety()+follow_vec.gety(), object_2.getPosition().getz()+follow_vec.getz())

object_2.setRotation(time.clock()*10000.0)

if pshObjectTests.object_intersect_test(object_2, obj0) == True:
 obj0.setColor(1.0, 0.0, 0.0, 1.0)
 obj0.setRenderable(False)
 print("YOU LOSE!")
else:
 obj0.setColor(1.0, 1.0, 1.0, 1.0)