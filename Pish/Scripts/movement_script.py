#A script that shows how to move your objects
#through scripting


#print(FrameEvent.keypress())

if FrameEvent.keypress() == 'a':
 object_0.setPosition(object_0.getPosition().getx()-0.2, object_0.getPosition().gety(), object_0.getPosition().getz())
 FrameEvent.keyset(0)

if FrameEvent.keypress() == 'd':
 object_0.setPosition(object_0.getPosition().getx()+0.2, object_0.getPosition().gety(), object_0.getPosition().getz())
 FrameEvent.keyset(0)

if FrameEvent.keypress() == 'w':
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()+0.2, object_0.getPosition().getz())
 FrameEvent.keyset(0)

if FrameEvent.keypress() == 's':
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()-0.2, object_0.getPosition().getz())
 FrameEvent.keyset(0)

if FrameEvent.keypress() == '+':
 object_0.setScale(object_0.getScale().getx()+0.1, object_0.getScale().gety()+0.1, 1.0)
 FrameEvent.keyset(0)

if FrameEvent.keypress() == '-':
 object_0.setScale(object_0.getScale().getx()-0.1, object_0.getScale().gety()-0.1, 1.0)
 FrameEvent.keyset(0)