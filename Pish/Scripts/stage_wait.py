########
########

timer = this_script.GetVarTimer(0)
print timer.Time()

########
########

gameScene0 = pshGE.SceneManage(0)
gameScene1 = pshGE.SceneManage(1)
mario_object = gameScene0.getSceneObject("mario")

scene_camera.pan(0, 0)

########
########

if(gameScene1.IsRendering() == False):
 timer.Restart()

if( timer.Time() > 4.9 ):
 mario_object.setPosition(0.0, 0.0, 0.0)
 gameScene0.SceneRender(True)
 timer.Restart()
 print "Test"
 gameScene1.SceneRender(False)



















