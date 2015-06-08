#A script that shows how to move your objects
#through scripting

#print this_script.GetVarBool(0)
#print FrameEvent.iskeydown(306)
#print FrameEvent.iskeydown(314)

modscpt_stillmario = pshSE.GetScript("stage_wait")
modscpt_stillmario.GetVarTimer(0).Restart()

walkrun_speed = 0.0

#print this_script.GetVarFloat(0)

if (this_script.GetVarFloat(0) >= 0.0) and (this_script.GetVarBool(1) == False):
 this_script.SetVarFloat(0, this_script.GetVarFloat(0) -0.01)

if (FrameEvent.iskeydown(306) == False)and(FrameEvent.iskeydown(314) == True):
 this.setPosition(this.getPosition().getx()-0.08, this.getPosition().gety(), this.getPosition().getz())
 if (this.getPosition().gety() <= -7.0):
  this.PlayAnimation(1)
  this.SetAnimIndex(0)
  this.SetAnimFPS(0, 15)
  walkrun_speed = 0.08
  this_script.SetVarFloat(0, this_script.GetVarFloat(0)+0.01)
  this_script.SetVarBool(1, 1)
  if (this_script.GetVarFloat(0) > 0.5):
   this_script.SetVarFloat(0, 0.5)
 else:
  this.PlayAnimation(0)
 if (this.isSpriteHFlip() == 1):
  this.flipSpriteH()
elif (FrameEvent.iskeydown(306) == True)and(FrameEvent.iskeydown(314) == True):
 this.setPosition(this.getPosition().getx()-0.25, this.getPosition().gety(), this.getPosition().getz())
 if (this.getPosition().gety() <= -7.0):
  this.PlayAnimation(1)
  this.SetAnimIndex(0)
  this.SetAnimFPS(0, 30)
  walkrun_speed = 0.25
  this_script.SetVarFloat(0, this_script.GetVarFloat(0)+0.01)
  this_script.SetVarBool(1, 1)
  if (this_script.GetVarFloat(0) > 0.5):
   this_script.SetVarFloat(0, 0.5)
 else:
  this.PlayAnimation(0)
 if (this.isSpriteHFlip() == 1):
  this.flipSpriteH()
elif (FrameEvent.iskeydown(306) == False)and(FrameEvent.iskeydown(316) == True): 
 this.setPosition(this.getPosition().getx()+0.08, this.getPosition().gety(), this.getPosition().getz())
 if (this.getPosition().gety() <= -7.0):
  this.SetAnimIndex(0)
  this.PlayAnimation(1)
  this.SetAnimFPS(0, 15)
  walkrun_speed = 0.08
  this_script.SetVarFloat(0, this_script.GetVarFloat(0)+0.01)
  this_script.SetVarBool(1, 1)
  if (this_script.GetVarFloat(0) > 0.5):
   this_script.SetVarFloat(0, 0.5)
 else:
  this.PlayAnimation(0)
 if (this.isSpriteHFlip() == 0):
  this.flipSpriteH()
elif (FrameEvent.iskeydown(306) == True)and(FrameEvent.iskeydown(316) == True): 
 this.setPosition(this.getPosition().getx()+0.25, this.getPosition().gety(), this.getPosition().getz())
 if (this.getPosition().gety() <= -7.0):
  this.SetAnimIndex(0)
  this.PlayAnimation(1)
  this.SetAnimFPS(0, 30)
  walkrun_speed = 0.25
  this_script.SetVarFloat(0, this_script.GetVarFloat(0)+0.01)
  this_script.SetVarBool(1, 1)
  if (this_script.GetVarFloat(0) > 0.5):
   this_script.SetVarFloat(0, 0.5)
 else:
  this.PlayAnimation(0)
 if (this.isSpriteHFlip() == 0):
  this.flipSpriteH()
else:
 this.PlayAnimation(0)
 this_script.SetVarBool(1, 0)

if (FrameEvent.iskeydown(32) == True)and(this_script.GetVarBool(0) == False): 
 if( (this.getPosition().gety() >= 3.0) and (this_script.GetVarBool(0) == False) ):
  this.setPosition(this.getPosition().getx(), this.getPosition().gety()+1.0, this.getPosition().getz())
  this.setTexture("mario_jump")
  this_script.SetVarBool(0, 1)
 if ( (this_script.GetVarBool(0) == False) ):
  this.setPosition(this.getPosition().getx(), this.getPosition().gety()+1.0, this.getPosition().getz())
  this.setTexture("mario_jump")



if ((this_script.GetVarBool(0)) == True) and (this.getPosition().gety() < -6.9999):
 this_script.SetVarBool(0, 0)

scene_camera.pan(-this.getPosition().getx()*10.0, -6.6)
scene_camera.zoom(0.8)



























