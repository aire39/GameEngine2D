#A script that shows how to move your objects
#through scripting

#print( FrameEvent.keypress() )

if FrameEvent.keypress() == 'A':
 object_0.setPosition(object_0.getPosition().getx()-0.01, object_0.getPosition().gety(), object_0.getPosition().getz())


if FrameEvent.keypress() == 'D':
 object_0.setPosition(object_0.getPosition().getx()+0.01, object_0.getPosition().gety(), object_0.getPosition().getz())


if FrameEvent.keypress() == 'W':
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()+0.01, object_0.getPosition().getz())


if FrameEvent.keypress() == 'S':
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()-0.01, object_0.getPosition().getz())


if FrameEvent.keypress() == '+':
 object_0.setScale(object_0.getScale().getx()+0.01, object_0.getScale().gety()+0.01, 1.0)


if chr(ord(FrameEvent.keypress())).lower() == '-':
 object_0.setScale(object_0.getScale().getx()-0.01, object_0.getScale().gety()-0.01, 1.0)

