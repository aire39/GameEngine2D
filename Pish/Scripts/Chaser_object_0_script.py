#A script that shows how to move your objects
#through scripting

mms = pshGE.SceneManage(0)
obj1 = mms.getSceneObject("object_1")
obj2 = mms.getSceneObject("object_2")
obj3 = mms.getSceneObject("object_3")

#print(FrameEvent.keypress())

if FrameEvent.keypress() == 'r':
 obj2.setPosition(15.0,15.0,1.0)
 obj3.setText("Game Start!")
 object_0.setRenderable(1)
 FrameEvent.keyset(0)

if FrameEvent.keypress() == 'a':
 object_0.setPosition(object_0.getPosition().getx()-0.5, object_0.getPosition().gety(), object_0.getPosition().getz())
 FrameEvent.keyset(0)

if FrameEvent.keypress() == 'd':
 object_0.setPosition(object_0.getPosition().getx()+0.5, object_0.getPosition().gety(), object_0.getPosition().getz())
 FrameEvent.keyset(0)

if FrameEvent.keypress() == 'w':
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()+0.5, object_0.getPosition().getz())
 FrameEvent.keyset(0)

if FrameEvent.keypress() == 's':
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()+0.2, object_0.getPosition().getz())
 FrameEvent.keyset(0)

if FrameEvent.keypress() == '+':
 object_0.setScale(object_0.getScale().getx()+0.1, object_0.getScale().gety()+0.1, 1.0)
 FrameEvent.keyset(0)

if FrameEvent.keypress() == '-':
 object_0.setScale(object_0.getScale().getx()-0.1, object_0.getScale().gety()-0.1, 1.0)
 FrameEvent.keyset(0)

object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()-0.01, object_0.getPosition().getz())

if pshObjectTests.object_intersect_test(object_0, obj1) == True:
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()+0.01, object_0.getPosition().getz())
 object_0.setColor(0.0, 1.0, 0.0, 1.0)
else:
 object_0.setColor(1.0, 1.0, 1.0, 1.0)