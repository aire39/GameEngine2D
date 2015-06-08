########
#Blink Text#
########
timer = this_script.GetVarTimer(0)
bool = this_script.GetVarBool(0)

if(timer.Time() > 0.25):
 bool ^= True
 this_script.SetVarBool(0, bool)
 timer.Restart()

if( bool == True):
 this.setRenderable(True)
else:
 this.setRenderable(False)

#######
#Any Key#
#######

scene_menu = pshGE.SceneManage(0)
scene_scene = pshGE.SceneManage(1)

if(FrameEvent.keypress() > 0):
 print "Test"
 scene_scene.SceneRender(1)
 scene_menu.SceneRender(0)
 



