#This script makes attached object follow 
#another object around

mms = pshGE.SceneManage(0)
obj0 = mms.getSceneObject("object_0")

if object_2.getPosition().getx() > obj0.getPosition().getx()-3.0:
 object_2.setPosition(object_2.getPosition().getx()-0.01, object_2.getPosition().gety(), object_2.getPosition().getz())

if object_2.getPosition().getx() < obj0.getPosition().getx()+3.0:
 object_2.setPosition(object_2.getPosition().getx()+0.01, object_2.getPosition().gety(), object_2.getPosition().getz())

if object_2.getPosition().gety() > obj0.getPosition().gety()-3.0:
 object_2.setPosition(object_2.getPosition().getx(), object_2.getPosition().gety()-0.01, object_2.getPosition().getz())

if object_2.getPosition().gety() < obj0.getPosition().gety()+3.0:
 object_2.setPosition(object_2.getPosition().getx(), object_2.getPosition().gety()+0.01, object_2.getPosition().getz())
