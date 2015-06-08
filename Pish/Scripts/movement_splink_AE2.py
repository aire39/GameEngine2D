#A script that shows how to move your objects
#through scripting

#from AnimIndex import *
#print(FrameEvent.keypress())

if (FrameEvent.keypress() == 314):
 this.setPosition(this.getPosition().getx()-0.08, this.getPosition().gety(), this.getPosition().getz())
 this.PlayAnimation(1)
 this.SetAnimIndex(0)
 if (this.isSpriteHFlip() == 1):
  this.flipSpriteH()
elif FrameEvent.keypress() == 316: 
 this.setPosition(this.getPosition().getx()+0.08, this.getPosition().gety(), this.getPosition().getz())
 this.SetAnimIndex(0)
 this.PlayAnimation(1)
 if (this.isSpriteHFlip() == 0):
  this.flipSpriteH()
elif FrameEvent.keypress() == 315:
 this.setPosition(this.getPosition().getx(), this.getPosition().gety()+0.08, this.getPosition().getz())
 this.SetAnimIndex(2)
 this.PlayAnimation(1)
elif FrameEvent.keypress() == 317:
 this.setPosition(this.getPosition().getx(), this.getPosition().gety()-0.08, this.getPosition().getz())
 this.SetAnimIndex(1)
 this.PlayAnimation(1)
else:
 this.PlayAnimation(0)

if FrameEvent.keypress() == '+':
 this.setScale(this.getScale().getx()+0.1, this.getScale().gety()+0.1, 1.0)
 FrameEvent.keyset(0)

if FrameEvent.keypress() == '-':
 this.setScale(this.getScale().getx()-0.1, this.getScale().gety()-0.1, 1.0)
 FrameEvent.keyset(0)





























