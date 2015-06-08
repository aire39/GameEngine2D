#A script that shows how to move your objects
#through scripting


#print(FrameEvent.keypress())

if (FrameEvent.keypress() == 'A'):
 object_0.setPosition(object_0.getPosition().getx()-0.01, object_0.getPosition().gety(), object_0.getPosition().getz())
 if (object_0.isSpriteHFlip() == 1):
  object_0.flipSpriteH()


if FrameEvent.keypress() == 'D':
 object_0.setPosition(object_0.getPosition().getx()+0.01, object_0.getPosition().gety(), object_0.getPosition().getz())
 if (object_0.isSpriteHFlip() == 0):
  object_0.flipSpriteH()

if FrameEvent.keypress() == 'W':
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()+0.01, object_0.getPosition().getz())


if FrameEvent.keypress() == 'S':
 object_0.setPosition(object_0.getPosition().getx(), object_0.getPosition().gety()-0.01, object_0.getPosition().getz())


if FrameEvent.keypress() == '+':
 object_0.setScale(object_0.getScale().getx()+0.1, object_0.getScale().gety()+0.1, 1.0)
 FrameEvent.keyset(0)

if FrameEvent.keypress() == '-':
 object_0.setScale(object_0.getScale().getx()-0.1, object_0.getScale().gety()-0.1, 1.0)
 FrameEvent.keyset(0)