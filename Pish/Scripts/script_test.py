mms = pshGE.SceneManage(0)

mobj = mms.getSceneObject("object_0")

mobj2 = mms.getSceneObject("object_2")


mobj.setPosition(-5.0, 0.0, 0.0)

mobj.setColor(mobj2.getPosition().getx()/10.0,mobj2.getPosition().gety()/10.0, mobj2.getPosition().getz()/10.0, 1.0)

#print(mobj2.getPosition().getx()/10.0, mobj2.getPosition().gety()/10.0, mobj2.getPosition().getz())

#print(mobj.getPosition().getx()/10.0, mobj.getPosition().gety()/10.0, mobj.getPosition().getz())