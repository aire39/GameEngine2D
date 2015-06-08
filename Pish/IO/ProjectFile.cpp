#include "../IO/ProjectFile.h"

ProjectFile::ProjectFile()
{
    animation_resource = NULL;
    texture_manager = NULL;
    script_manager  = NULL;
    scene_manager   = NULL;
    tree_view       = NULL;
    anim_manager    = NULL;

    ProjectDirectory = "";

    texture_resource = NULL;

    FileModified = false;
	ProjectDirectoryFile = "";
}

ProjectFile::~ProjectFile()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting ProjectFile!" << std::endl;
    #endif

    wxXmlNode * detached = doc.DetachRoot();
    if(detached != NULL)
        delete detached;
    detached = NULL;

    tree_view = NULL;
    scene_manager = NULL;

}

std::string ProjectFile::localizepath(std::string dir_name)
{
    std::string pdir = ProjectDirectory;
	return pdir;
}

void ProjectFile::BindProjectTree(projectTreeView * tree_view)
{
    this->tree_view = tree_view;
}

void ProjectFile::BindSceneManager(std::vector<entityManager *> * scene_manager)
{
    this->scene_manager = scene_manager;
}

void ProjectFile::BindScriptManager(scriptMng * script_manager)
{
    this->script_manager = script_manager;
}

void ProjectFile::BindTextureManager(texMng * texture_manager)
{
    this->texture_manager = texture_manager;
}

void ProjectFile::BindAnimationManager(animationManager * anim_manager)
{
    this->anim_manager = anim_manager;
}

void ProjectFile::BindTextureResource(textureResource * texture_resource)
{
    this->texture_resource = texture_resource;
}

void ProjectFile::BindAnimationResource(animationResource * animation_resource)
{
    this->animation_resource = animation_resource;
}

void ProjectFile::Save()
{

    FileModified = true;

    wxXmlNode * detached = doc.DetachRoot();
    delete detached;
    detached = NULL;

    root = new wxXmlNode();
    root->SetType(wxXML_ELEMENT_NODE);
    root->SetName("Root");


    ////////////////////////////////
    //Saving Scene And Object Data//
    ////////////////////////////////
    char c_buffer[5];
    if( scene_manager->size() > 0 )
    for(int i=(int)tree_view->scenes_InTree.size()-1; i>=0; i--)
    {
        wxXmlNode * pshentity = NULL;
        bool status0 = false;
        wxXmlNode * top0 = root;

        //////////////////////////////////////////////
        //Check to see if scene already exis in file//
        //////////////////////////////////////////////

        while(top0)
        {
            if(top0->GetName().compare("Scene")==0)
                if( top0->GetAttributes()->GetValue().compare(scene_manager->at(i)->SceneName())==0 )
                {
                    status0 = true;
                    break;
                }

                if(top0->GetChildren() != NULL)
                    top0 = top0->GetChildren();
                else
                    top0 = top0->GetNext();

        }

        //////////////////////////////////////////////////////////////
        //If the scene does not exist in file then append it to file//
        //////////////////////////////////////////////////////////////
        if(!status0)
        {
            wxXmlNode * pshscenes = new wxXmlNode(root, wxXML_ELEMENT_NODE, "Scene");
            wxXmlAttribute * scene_render = new wxXmlAttribute("render", convertDouble(scene_manager->at(i)->IsRendering()));
            wxXmlAttribute * scene_name = new wxXmlAttribute("name", scene_manager->at(i)->SceneName(), scene_render);
            pshscenes->SetAttributes(scene_name);
            pshentity = new wxXmlNode(pshscenes, wxXML_ELEMENT_NODE, "Entity");
        }

        for(int j=(int)tree_view->entity_InScenesTree[i].size()-1; j>=0; j--)
        {
            wxXmlAttribute * editnode = NULL;
            wxXmlNode * top = root;
            Entity * entity = NULL;
            entity = scene_manager->at(i)->getEntity( tree_view->entity_InScenesTree[i][j].first );
            bool status = false;

            if( entity != NULL )
            {
                ////////////////////////////////////////////////
                //Check to see if object exist in file already//
                ////////////////////////////////////////////////
                while(top)
                {
                    if(top->GetName().compare("Entity")==0)
                        pshentity = top;

                    if(top->GetName().compare("Data")==0)
                        if( top->GetAttributes()->GetValue().compare(entity->getName())==0 )
                        {
                            editnode = top->GetAttributes();
                            status = true;
                            break;
                        }



                    if(top->GetChildren() != NULL)
                        top = top->GetChildren();
                    else
                        top = top->GetNext();
                }

                /////////////////////////////////////////////////////////////////////////////
                //If the object exists then change the paramters instead of appending onto.//
                //skip iteration/////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////////////////
                if(status)
                {
                    while(editnode)
                    {

                        if(editnode->GetName().compare("name")==0)
                            editnode->SetValue(entity->getName());
                        else if(editnode->GetName().compare("type")==0)
                        {
                            if(typeid(*entity) == typeid(Sprite))
                                editnode->SetValue("sprite");
                            else if(typeid(*entity) == typeid(Entity))
                                editnode->SetValue("empty");
                            else if(typeid(*entity) == typeid(Text))
                                editnode->SetValue("text");
                        }
                        else if(editnode->GetName().compare("color")==0)
                        {
                            wxColour temp_color((int)(entity->getColor().getX()*255.0f), (int)(entity->getColor().getY()*255.0f), (int)(entity->getColor().getZ()*255.0f), (int)(entity->getColor().getW()*255.0f));
                            editnode->SetValue(temp_color.GetAsString(wxC2S_CSS_SYNTAX));
                        }
                        else if(editnode->GetName().compare("x")==0)
                            editnode->SetValue( convertDouble( entity->getPosition().getX() ));
                        else if(editnode->GetName().compare("y")==0)
                            editnode->SetValue( convertDouble( entity->getPosition().getY() ));
                        else if(editnode->GetName().compare("z")==0)
                            editnode->SetValue( convertDouble( entity->getPosition().getZ() ));
                        else if(editnode->GetName().compare("sx")==0)
                            editnode->SetValue( convertDouble( entity->getScale().getX() ));
                        else if(editnode->GetName().compare("sy")==0)
                            editnode->SetValue( convertDouble( entity->getScale().getY() ));
                        else if(editnode->GetName().compare("sz")==0)
                            editnode->SetValue( convertDouble( entity->getScale().getZ() ));
                        else if(editnode->GetName().compare("texture")==0)
                            editnode->SetValue( entity->s_getTexture() );
                        else if(editnode->GetName().compare("repeatx")==0)
                        {
                            if(typeid(*entity) == typeid(Sprite))
                            {
                                editnode->SetValue( convertDouble( ((Sprite*)entity)->getTextureRepeatX() ));
                                editnode = editnode->GetNext();
                                editnode->SetValue( convertDouble( ((Sprite*)entity)->getTextureRepeatY() ));
                            }
                            else
                            {
                                editnode->SetValue("1");
                                editnode = editnode->GetNext();
                                editnode->SetValue("1");
                            }
                        }
                        else if(editnode->GetName().compare("flipx")==0)
                        {
                            if(typeid(*entity) == typeid(Sprite))
                            {
                                editnode->SetValue( convertDouble( ((Sprite*)entity)->isSpriteHFlip() ));
                                editnode = editnode->GetNext();
                                editnode->SetValue( convertDouble( ((Sprite*)entity)->isSpriteVFlip() ));
                            }
                            else
                            {
                                editnode->SetValue("0");
                                editnode = editnode->GetNext();
                                editnode->SetValue("0");
                            }
                        }


                        editnode = editnode->GetNext();
                    }

                    continue;
                }

                /////////////////////////////////////////////////////////////
                //Append object info into file if it does not exist in file//
                /////////////////////////////////////////////////////////////

                wxXmlNode * pshentity_data = new wxXmlNode(pshentity, wxXML_ELEMENT_NODE, "Data");

                    wxXmlAttribute * object_tail    = NULL;
                    wxXmlAttribute * object_texture = NULL;
                    wxXmlAttribute * object_text    = NULL;

                    ////////////////////////////////////////
                    //Saving Attached Scripts And Settings//
                    ////////////////////////////////////////

                    if( (script_manager != NULL) && (entity != NULL) )
                    {
                        LayerData * layer_data = NULL;
                        layer_data = scene_manager->at(i)->GetObjectLayerData(entity);

                        if( layer_data != NULL )
                            if( layer_data->scripts.size() > 0 )
                                for(int i=layer_data->scripts.size()-1; i>=0; i--)
                                {
                                    wxXmlNode * script_node = new wxXmlNode(pshentity_data, wxXML_ELEMENT_NODE, "Script");

                                    wxXmlAttribute * attrib_run = new wxXmlAttribute("run", convertDouble(layer_data->scripts[i]->isRunning()), NULL);
                                    wxXmlAttribute * attrib_script = new wxXmlAttribute("name", layer_data->scripts[i]->getName(), attrib_run);

                                    script_node->SetAttributes(attrib_script);

                                    if( layer_data->scripts.size() > 0 )
                                    if( layer_data->scripts[i]->HasVars() )
                                    {
                                        if( layer_data->scripts[i]->GetNumberOfVars("int") > 0 )
                                            for(int j=layer_data->scripts[i]->GetNumberOfVars("int")-1; j>=0; j--)
                                            {
                                                wxXmlNode * vars_node = new wxXmlNode(script_node, wxXML_ELEMENT_NODE, "Var" );
                                                wxXmlAttribute * var_value = new wxXmlAttribute("value", convertDouble(layer_data->scripts[i]->GetVarInt(j)), NULL);
                                                wxXmlAttribute * name = new wxXmlAttribute("name", layer_data->scripts[i]->GetNameOfVar(j, "int"), var_value);
                                                wxXmlAttribute * var_type = new wxXmlAttribute("type", "int", name);
                                                vars_node->SetAttributes(var_type);
                                            }

                                        if( layer_data->scripts[i]->GetNumberOfVars("bool") > 0 )
                                            for(int j=layer_data->scripts[i]->GetNumberOfVars("bool")-1; j>=0; j--)
                                            {
                                                wxXmlNode * vars_node = new wxXmlNode(script_node, wxXML_ELEMENT_NODE, "Var" );
                                                wxXmlAttribute * var_value = new wxXmlAttribute("value", convertDouble(layer_data->scripts[i]->GetVarBool(j)), NULL);
                                                wxXmlAttribute * name = new wxXmlAttribute("name", layer_data->scripts[i]->GetNameOfVar(j, "bool"), var_value);
                                                wxXmlAttribute * var_type = new wxXmlAttribute("type", "bool", name);
                                                vars_node->SetAttributes(var_type);
                                            }

                                        if( layer_data->scripts[i]->GetNumberOfVars("float") > 0 )
                                            for(int j=layer_data->scripts[i]->GetNumberOfVars("float")-1; j>=0; j--)
                                            {
                                                wxXmlNode * vars_node = new wxXmlNode(script_node, wxXML_ELEMENT_NODE, "Var" );
                                                wxXmlAttribute * var_value = new wxXmlAttribute("value", convertDouble(layer_data->scripts[i]->GetVarFloat(j)), NULL);
                                                wxXmlAttribute * name = new wxXmlAttribute("name", layer_data->scripts[i]->GetNameOfVar(j, "float"), var_value);
                                                wxXmlAttribute * var_type = new wxXmlAttribute("type", "float", name);
                                                vars_node->SetAttributes(var_type);
                                            }

                                        if( layer_data->scripts[i]->GetNumberOfVars("string") > 0 )
                                            for(int j=layer_data->scripts[i]->GetNumberOfVars("string")-1; j>=0; j--)
                                            {
                                                wxXmlNode * vars_node = new wxXmlNode(script_node, wxXML_ELEMENT_NODE, "Var" );
                                                wxXmlAttribute * var_value = new wxXmlAttribute("value", layer_data->scripts[i]->GetVarStr(j), NULL);
                                                wxXmlAttribute * name = new wxXmlAttribute("name", layer_data->scripts[i]->GetNameOfVar(j, "string"), var_value);
                                                wxXmlAttribute * var_type = new wxXmlAttribute("type", "string", name);
                                                vars_node->SetAttributes(var_type);
                                            }

                                        if( layer_data->scripts[i]->GetNumberOfVars("timer") > 0 )
                                            for(int j=layer_data->scripts[i]->GetNumberOfVars("timer")-1; j>=0; j--)
                                            {
                                                wxXmlNode * vars_node = new wxXmlNode(script_node, wxXML_ELEMENT_NODE, "Var" );
                                                wxXmlAttribute * name = new wxXmlAttribute("name", layer_data->scripts[i]->GetNameOfVar(j, "timer"), NULL);
                                                wxXmlAttribute * var_type = new wxXmlAttribute("type", "timer", name);
                                                vars_node->SetAttributes(var_type);
                                            }

                                    }
                                }


                    }

                    ///////////////////////////////////////////
                    //Saving Attached Animations And Settings//
                    ///////////////////////////////////////////

                    if( typeid(*entity) == typeid(Text) )
                    {
                        Text * text_entity = (Text*)entity;

                        wxXmlNode * anim_node = new wxXmlNode(pshentity_data, wxXML_ELEMENT_NODE, "Animation");

                        wxXmlAttribute * anim_attrib_fps    = new wxXmlAttribute("fps", convertDouble(text_entity->GetFrameRate()), NULL);
                        wxXmlAttribute * anim_attrib_enable = new wxXmlAttribute("enabled", convertDouble(text_entity->IsAnimating()), anim_attrib_fps);

                        anim_node->SetAttributes(anim_attrib_enable);
                    }
                    else if(typeid(*entity) == typeid(Sprite))
                    {
                        Sprite * sprite_entity = (Sprite*)entity;

                        for( int i=0; i<sprite_entity->GetNumberOfAnimation(); i++ )
                        {
                            wxXmlNode * anim_node = new wxXmlNode(pshentity_data, wxXML_ELEMENT_NODE, "Animation");

                            wxXmlAttribute * anim_attrib_index  = new wxXmlAttribute("index", convertDouble(i), NULL);
                            wxXmlAttribute * anim_attrib_enable  = new wxXmlAttribute("enable", convertDouble(sprite_entity->IsAnimationPlaying(i)), anim_attrib_index);
                            wxXmlAttribute * anim_attrib_fps  = new wxXmlAttribute("fps", convertDouble(sprite_entity->GetAnimation(i)->GetFrameRate()), anim_attrib_enable);
                            wxXmlAttribute * anim_attrib_name = new wxXmlAttribute("name", sprite_entity->GetAnimationName(i), anim_attrib_fps);

                            anim_node->SetAttributes(anim_attrib_name);
                        }
                    }

                    /////////////////////
                    //Saving Basic Data//
                    /////////////////////

                    if( typeid(*entity) == typeid(Text) )
                    {
                        object_text = new wxXmlAttribute("text", ((Text*)entity)->getText(), NULL);
                        object_tail = object_text;
                    }


                    if(typeid(*entity) == typeid(Sprite))
                    {
                        Sprite * sprite = (Sprite*)entity;

                        wxXmlAttribute * object_textureFY = new wxXmlAttribute("flipy", convertDouble(sprite->isSpriteVFlip()), object_text);
                        wxXmlAttribute * object_textureFX = new wxXmlAttribute("flipx", convertDouble(sprite->isSpriteHFlip()), object_textureFY);
                        wxXmlAttribute * object_textureRY = new wxXmlAttribute("repeaty", convertDouble(sprite->getTextureRepeatY()), object_textureFX);
                        wxXmlAttribute * object_textureRX = new wxXmlAttribute("repeatx", convertDouble(sprite->getTextureRepeatX()), object_textureRY);
                        object_texture  = new wxXmlAttribute("texture" , entity->s_getTexture(), object_textureRX);
                        object_tail = object_texture;
                    }


                    itoa(entity->getLayer(), c_buffer, 10);
                    wxXmlAttribute * object_layer  = new wxXmlAttribute("layer" , c_buffer  , object_tail);

                    //wxXmlAttribute * object_scale  = new wxXmlAttribute("scale" , "3"  , NULL);
                        wxXmlAttribute * object_position_sz = new wxXmlAttribute("sz", convertDouble(entity->getScale().getZ()), object_layer);
                        wxXmlAttribute * object_position_sy = new wxXmlAttribute("sy", convertDouble(entity->getScale().getY()), object_position_sz);
                        wxXmlAttribute * object_position_sx = new wxXmlAttribute("sx", convertDouble(entity->getScale().getX()), object_position_sy);
                    //object_scale->SetNext(object_position_sx);

                    wxXmlAttribute * object_rotate  = new wxXmlAttribute("rotation", convertDouble(entity->getRotation())  , object_position_sx);

                    //wxXmlAttribute * object_position  = new wxXmlAttribute("position" , "3"  , NULL);
                        wxXmlAttribute * object_position_z = new wxXmlAttribute("z", convertDouble(entity->getPosition().getZ()), object_rotate);
                        wxXmlAttribute * object_position_y = new wxXmlAttribute("y", convertDouble(entity->getPosition().getY()), object_position_z);
                        wxXmlAttribute * object_position_x = new wxXmlAttribute("x", convertDouble(entity->getPosition().getX()), object_position_y);
                    //object_position->SetNext(object_position_x);

                    wxColour temp_color((int)(entity->getColor().getX()*255.0f), (int)(entity->getColor().getY()*255.0f), (int)(entity->getColor().getZ()*255.0f), (int)(entity->getColor().getW()*255.0f));
                    wxXmlAttribute * object_color     = new wxXmlAttribute("color", temp_color.GetAsString(wxC2S_CSS_SYNTAX), object_position_x);
                    wxXmlAttribute * object_type      = new wxXmlAttribute("type" , tree_view->entity_InScenesTree[i][j].second  , object_color);
                    wxXmlAttribute * object_name      = new wxXmlAttribute("name" , entity->getName(), object_type);

                pshentity_data->SetAttributes(object_name);

                if( (typeid(*entity) == typeid(Sprite) ) && (((Sprite*)entity)->GetNumberOfAnimation() > 0) )
                {

                }
            }
        }
    }



    ////////////////////////
    //Saving Resource Data//
    ////////////////////////

    wxXmlNode *texture_node;
    wxXmlNode *animation_node;
    wxXmlNode *scripts_node;

    ///////////
    //Scripts//
    ///////////

    if(script_manager!= NULL)
    if(script_manager->get_number_of_scripts()>0)
    {
        scripts_node = new wxXmlNode(root, wxXML_ELEMENT_NODE, "ScriptResource");

        for(int i=0; i<(int)script_manager->get_number_of_scripts(); i++)
        {
            if(script_manager->GetScriptByIndex(i) != NULL)
            {
                pScript * script = NULL;
                script = script_manager->GetScriptByIndex(i);

                wxXmlNode * scripts = new wxXmlNode(scripts_node, wxXML_ELEMENT_NODE, "Script");

                if( !script->EmbedExportMode() )
                {
                    wxString path_str = "./Scripts/";
                    path_str.append(script->getName());
                    path_str.append(".py");

                    fstream file;
                    file.open((const char*)path_str.c_str(), ios::out);
                    file << script->getData().c_str();
                    file.close();

                    wxXmlAttribute * path = new wxXmlAttribute("path", path_str, NULL );
                    scripts->SetAttributes(path);
                }
                else
                {
                    std::string script_data = script->getData();

                    for(int i=0; i<(int)script_data.length(); i++)
                    {
                        if( script_data[i] == '\n' )
                            script_data[i] = ';';
                    }

                    wxXmlAttribute * embed = new wxXmlAttribute("embed", script_data, NULL );
                    wxXmlAttribute * name  = new wxXmlAttribute("name", script->getName(), embed);
                    scripts->SetAttributes(name);
                }
            }
        }
    }


    //////////////
    //Animations//
    //////////////

    if(anim_manager != NULL)
    if(anim_manager->number_of_animations()>0)
    {
        animation_node = new wxXmlNode(root, wxXML_ELEMENT_NODE, "AnimationResource");

        for(int i=anim_manager->number_of_animations()-1; i>=0; i--)
        {
            wxXmlNode * animations = new wxXmlNode(animation_node, wxXML_ELEMENT_NODE, "Animation");
            wxXmlAttribute * name = new wxXmlAttribute("name", anim_manager->getAnimation(i)->AnimName());
            animations->SetAttributes(name);

            wxXmlNode * frames = new wxXmlNode(animations, wxXML_ELEMENT_NODE, "Frames");
            wxXmlAttribute * attrhold = NULL;

            for(int j=anim_manager->getAnimation(i)->GetNumberOfFrames()-1; j>=0; j--)
            {
                wxString fn = "f";
                fn.append(convertDouble(j));
                wxXmlAttribute * cframe = new wxXmlAttribute(fn, anim_manager->getAnimation(i)->s_GetFrame(j), attrhold);
                attrhold = cframe;
            }

            frames->SetAttributes(attrhold);

        }
    }

    ////////////
    //Textures//
    ////////////

    if(texture_manager!= NULL)
    if(texture_manager->GetNumberOfTextures()>0)
    {
        texture_node = new wxXmlNode(root, wxXML_ELEMENT_NODE, "TextureResource");

        for(int i=(int)texture_manager->GetNumberOfTextures()-1; i>=0; i--)
        {
            wxXmlAttribute * path = NULL;
            wxXmlNode * textures = new wxXmlNode(texture_node, wxXML_ELEMENT_NODE, "Texture");

            Texture * texture = texture_manager->GetTexture(i);

            if( texture->GetTextureSub() != NULL )
            {
                wxXmlAttribute * keyed = new wxXmlAttribute("keyed", "0" );
                wxXmlAttribute * suby = new wxXmlAttribute("suby", convertDouble(texture->GetTextureSub()->GetNumberOfChopedY()), keyed );
                wxXmlAttribute * subx = new wxXmlAttribute("subx", convertDouble(texture->GetTextureSub()->GetNumberOfChopedX()), suby );
                path = new wxXmlAttribute("path", texture->GetTexturePath(), subx );
            }
            else
            {
                wxXmlAttribute * keyed = new wxXmlAttribute("keyed", "0" );
                path = new wxXmlAttribute("path", texture->GetTexturePath(), keyed );
				std::cout << "Saving Texture Path: " << texture->GetTexturePath() << std::endl;
            }

            textures->SetAttributes(path);
        }

    }

    ////////////////////////
    doc.SetRoot( root );

    if(!ProjectDirectory.empty())
        doc.Save(ProjectDirectory);
}

void ProjectFile::SaveOutput(std::string path)
{
	ProjectDirectoryFile = path;
    Save();
    doc.Save(path);

}

void ProjectFile::Load(std::string path)
{
	wxString tmpstr;
    tmpstr = path;

	ProjectDirectoryFile = path;
	ProjectDirectory = tmpstr.BeforeLast('/');

	if(ProjectDirectory.empty())
		ProjectDirectory = tmpstr.BeforeLast('\\');

	if( !is_forard_slash_dir(ProjectDirectory) )
		foward_slash_dir(ProjectDirectory);

    std::cout << "Entered Loading..." << std::endl;
    FileModified = false;

    if( !doc.Load(path.c_str(), "UTF-8") )
        std::cout << "Failed to load or can't find project file!" << std::endl;
    else
    {
        if( doc.GetRoot()->GetName() != "Root" )
            std::cout << "Root not found!" << std::endl;
        else
        {
            wxXmlNode * child = doc.GetRoot()->GetChildren();
            int nScenes = -1;

            while( child )
            {
                //////////////////////////////////
                //Loading Textures Into Resource//
                //////////////////////////////////

                if(child->GetName() == "TextureResource")
                {
                    wxXmlNode * tr_node = NULL;

                    tr_node = child->GetChildren();

                    while(tr_node)
                    {


                        wxXmlAttribute * attrib0 = tr_node->GetAttributes();
                        wxString path = attrib0->GetValue();
                        wxString tname = path.AfterLast('/');
						wxString tnameext = path.AfterLast('.');
						tnameext.Prepend(".");
                        tname = tname.BeforeLast('.');

                        wxXmlAttribute * attrib1 = attrib0->GetNext();
                        bool keyed = (bool)atoi(attrib1->GetValue().c_str());

                        if( attrib1->GetName() == "keyed" )
                        {
                            if( texture_manager->GetTexture(tname.c_str()) == NULL )
                            {
								wxPathList path_list;
								if( !path_list.Add(ProjectDirectory) )
									std::cout << "Couldn't Add Path!" << std::endl;
								if( !path_list.Add(ProjectDirectory+"/Textures") )
									std::cout << "Couldn't Add Path!" << std::endl;
								if( !path_list.Add(ProjectDirectory+"/Animation") )
									std::cout << "Couldn't Add Path!" << std::endl;

								wxFileName file_name;
								std::string _file_name;
								wxString astr;
                                TextureBase * texture;
                                //std::cout << "Adding Texture: " << tname+tnameext << " : path-> " << path << std::endl;

								if( path.Find("Animation") != wxNOT_FOUND )
								{
									std::string __astr = (std::string)path;
									if( !is_forard_slash_dir(__astr) )
										foward_slash_dir(__astr);

									wxString astr = __astr;

									if( astr[0] == '.' )
									{
										astr = astr.AfterFirst('/');
										astr = astr.AfterFirst('/');
									}
									else
										astr = astr.AfterFirst('/');

									astr = astr.BeforeFirst('/');

									if( !path_list.Add(ProjectDirectory+"/Animation/"+astr) )
										std::cout << "Couldn't Add Path!" << std::endl;
									//std::cout << ProjectDirectory+"/Animation/"+astr << std::endl;
								}

								file_name.Assign( path_list.FindValidPath( tname+tnameext ));
								file_name.MakeRelativeTo(ProjectDirectory);

								_file_name = file_name.GetFullPath();

								if( !is_forard_slash_dir(_file_name) )
									foward_slash_dir( _file_name );

								//std::cout << "Relative Path: " << _file_name << std::endl;

								texture = texture_manager->addTexture(_file_name.c_str(), keyed);

                                if( texture != NULL )
                                {
                                    if( texture_resource != NULL )
                                        texture_resource->mUpdateResource();

                                    if( animation_resource != NULL )
                                        animation_resource->mUpdateResource();
                                }
                            }
                            else
                                std::cout << "Texture Already In Resource!" << std::endl;
                        }
                        else if( attrib1->GetName() == "subx" )
                        {
                            if( texture_manager->GetTexture(tname.c_str()) == NULL )
                            {
                                std::cout << "Adding Texture: " << tname << " : path-> " << path << std::endl;

                                int subx = atoi(attrib1->GetValue().c_str());
                                attrib1 = attrib1->GetNext();
                                int suby = atoi(attrib1->GetValue().c_str());
                                attrib1 = attrib1->GetNext();
                                bool keyed = atoi( attrib1->GetValue().c_str());

                                Texture * texture = NULL;
                                texture = texture_manager->addTexture(path.c_str(), keyed);

                                if( texture != NULL )
                                {
                                    TextureSub * texture_sub = new TextureSub();
                                    texture_sub->AttachMasterTexture(texture);
                                    texture_sub->ChopTexture(suby, subx);

                                    if( texture_resource != NULL )
                                        texture_resource->mUpdateResource();

                                    if( animation_resource != NULL )
                                        animation_resource->mUpdateResource();
                                }
                                else
                                    std::cout << "Couldn't Add Texture Or Not Found!" << std::endl;


                            }
                            else
                                std::cout << "Texture Already In Resource!" << std::endl;
                        }

                        tr_node = tr_node->GetNext();

                    }
                }

                ////////////////////////////////////
                //Loading Animations Into Resource//
                ////////////////////////////////////

                if(child->GetName() == "AnimationResource")
                {
                    wxXmlNode * ar_node = NULL;

                    ar_node = child->GetChildren();

                    while(ar_node)
                    {
                        if( anim_manager->getAnimation((std::string)ar_node->GetAttributes()->GetValue()) == NULL )
                        {
                            Animation * animation = new Animation();
                            animation->SetAnimationName( (std::string)ar_node->GetAttributes()->GetValue() );

                            wxXmlNode * ar_anim = ar_node->GetChildren();
                            wxXmlAttribute * ar_anim_attrib = ar_anim->GetAttributes();

                            std::cout << "Animation: " << ar_node->GetAttributes()->GetValue() << std::endl;

                            while(ar_anim_attrib)
                            {
                                animation->s_AddFrame( (std::string)ar_anim_attrib->GetValue() );
                                std::cout << ar_anim_attrib->GetName() << " : " << ar_anim_attrib->GetValue() << "  ";
                                ar_anim_attrib = ar_anim_attrib->GetNext();
                            }
                            std::cout << std::endl;

                            anim_manager->InsertAnimation(animation->AnimName(), animation);
                        }
                        else
                            std::cout << "Animation Already Exists!" << std::endl;

                        ar_node = ar_node->GetNext();
                    }
                }

                /////////////////////////////////
                //Loading Scripts Into Resource//
                /////////////////////////////////

                if(child->GetName() == "ScriptResource")
                {
                    wxXmlNode * sr_node = NULL;

                    sr_node = child->GetChildren();

                    while(sr_node)
                    {
                        if( sr_node->GetAttributes()->GetName().compare("path") == 0 )
                        {
                            wxXmlAttribute * attrib0 = sr_node->GetAttributes();
                            wxString path = attrib0->GetValue();
                            wxString sname = path.AfterLast('/');
                            sname = sname.BeforeLast('.');

                            if( script_manager->getScript((std::string)sname) == NULL )
                            {
                                pScript * script = NULL;
                                script = script_manager->addScript((std::string)path);
                            }
                            else
                                std::cout << "Script Already In Resource!" << std::endl;
                        }
                        else
                        {
                            wxXmlAttribute * attrib0 = sr_node->GetAttributes();
                            wxString name = attrib0->GetValue();
                            wxXmlAttribute * attrib1 = attrib0->GetNext();
                            std::string data = (std::string)attrib1->GetValue();

                            if( script_manager->getScript((std::string)name) == NULL )
                            {
                                for(int i=0; i<(int)data.length(); i++)
                                {
                                    if( data[i] == ';' )
                                        data[i] = '\n';
                                }

                                pScript * script = NULL;
                                script = script_manager->addNewScript((std::string)name);
                                script->loadScript(data);
                                script->SetSaveMode(true);
                            }
                            else
                                std::cout << "Script Already In Resource!" << std::endl;
                        }


                        sr_node = sr_node->GetNext();
                    }
                }

                ////////////////
                //Adding Scene//
                ////////////////

                if(child->GetName() == "Scene")
                {
                    wxXmlNode * scene_node = NULL;
                    scene_node = child;

                    wxXmlAttribute * scene_name = NULL;
                    scene_name = scene_node->GetAttributes();

                    if( scene_name != NULL )
                    {
                        entityManager * entity_management = NULL;
                        std::cout << scene_name->GetValue() << std::endl;
                        entity_management = tree_view->AddScene( (std::string)scene_name->GetValue() );

                        wxXmlAttribute * scene_render = scene_name->GetNext();

                        if( scene_render != NULL )
                            entity_management->renderEnabled( atoi(scene_render->GetValue()) );

                        nScenes++;

                    }
                    else
                    {
                        std::cout << "No Scenes To Load!" << std::endl;
                        break;
                    }

                    while( scene_node )
                    {
                        /////////////////////////////
                        //Setting Basic Object Data//
                        /////////////////////////////

                        if(scene_node->GetName() == "Data")
                        {

                            while( scene_node != NULL )
                            {
                                float _x, _y, _z;
                                float _r;
                                float _sx, _sy, _sz;
                                int   _L;

                                wxXmlAttribute * attrib;
                                Entity * _entity = NULL;
                                std::string str_name = "";

                                attrib = scene_node->GetAttributes();

                                while( attrib )
                                {
                                    std::cout << attrib->GetValue() << std::endl;

                                    if( attrib->GetName() == "name" )
                                    {
                                        str_name = attrib->GetValue();
                                    }

                                    if( attrib->GetName() == "type" )
                                    {
                                        _entity = tree_view->AddEntity(nScenes, str_name, (std::string)attrib->GetValue());

                                        pair<std::string, std::string> _p(str_name, (std::string)attrib->GetValue());
                                        tree_view->entity_InScenesTree[nScenes].push_back( _p );
                                    }

                                    if( attrib->GetName() == "color" )
                                    {
                                        wxColour _color;
                                        if(_color.Set(attrib->GetValue()))
                                            _entity->setColor( (float)_color.Red()/255.0f, (float)_color.Green()/255.0f, (float)_color.Blue()/255.0f, (float)_color.Alpha()/255.0f );
                                    }

                                    if( attrib->GetName() == "x" )
                                    {
                                        _x = 0.0f;
                                        _x = atof(attrib->GetValue().c_str());
                                    }

                                    if( attrib->GetName() == "y" )
                                    {
                                        _y = 0.0f;
                                        _y = atof(attrib->GetValue().c_str());
                                    }

                                    if( attrib->GetName() == "z" )
                                    {
                                        _z = 0.0f;
                                        _z = atof(attrib->GetValue().c_str());

                                        _entity->setPosition(_x, _y, _z);
                                    }

                                    if( attrib->GetName() == "rotation" )
                                    {
                                        _r = 0.0f;
                                        _r = atof(attrib->GetValue().c_str());

                                        _entity->setRotation(_r);
                                    }

                                    if( attrib->GetName() == "sx" )
                                    {
                                        _sx = 0.0f;
                                        _sx = atof(attrib->GetValue().c_str());
                                    }

                                    if( attrib->GetName() == "sy" )
                                    {
                                        _sy = 0.0f;
                                        _sy = atof(attrib->GetValue().c_str());
                                    }

                                    if( attrib->GetName() == "sz" )
                                    {
                                        _sz = 0.0f;
                                        _sz = atof(attrib->GetValue().c_str());

                                        _entity->setScale(_sx, _sy, _sz);
                                    }

                                    if( attrib->GetName() == "layer" )
                                    {
                                        _L = 0;
                                        _L = atoi(attrib->GetValue().c_str());

                                        _entity->setLayer(_L);
                                    }

                                    if( attrib->GetName() == "texture" )
                                    {
                                        //Sprite * sprite = (Sprite*)_entity;
                                        _entity->setTexture((std::string)attrib->GetValue());
                                    }

                                    if( attrib->GetName() == "repeatx" )
                                    {
                                        Sprite * sprite = (Sprite*)_entity;

                                        //attrib = attrib->GetNext();
                                        sprite->setTextureRepeatX( atoi((const char*)attrib->GetValue().c_str()));

                                        attrib = attrib->GetNext();
                                        sprite->setTextureRepeatY( atoi((const char*)attrib->GetValue().c_str()));

                                    }

                                    if( attrib->GetName() == "flipx" )
                                    {
                                        Sprite * sprite = (Sprite*)_entity;

                                        if( atoi((const char*)attrib->GetValue().c_str()) == 1 )
                                            sprite->flipHorizontalTexCoordinates();

                                        attrib = attrib->GetNext();
                                        if( atoi((const char*)attrib->GetValue().c_str()) == 1 )
                                            sprite->flipVerticleTexCoordinates();

                                    }

                                    if( attrib->GetName() == "text" )
                                    {
                                        ((Text*)_entity)->setText((std::string)attrib->GetValue());
                                    }

                                    attrib = attrib->GetNext();
                                }

                                /////////////////////
                                //Attach Animations//
                                /////////////////////

                                if( scene_node->GetChildren() != NULL )
                                {
                                    wxXmlNode * attach_anim = scene_node->GetChildren();

                                    while(attach_anim && attach_anim->GetName()=="Animation")
                                    {
                                        wxXmlAttribute * anim_attrib = attach_anim->GetAttributes();

                                        while( anim_attrib )
                                        {
                                            if( anim_attrib->GetName() == "name" )
                                            {
                                                Sprite * sprite = (Sprite*)_entity;
                                                Animation * add_animation = new Animation( *anim_manager->getAnimation((std::string)anim_attrib->GetValue()) );
                                                sprite->AddAnimation(add_animation);

                                                anim_attrib = anim_attrib->GetNext();
                                                add_animation->SetFPS( atoi(anim_attrib->GetValue().c_str()) );


                                                if(anim_attrib->GetNext() != NULL)
                                                {
                                                    anim_attrib = anim_attrib->GetNext();
                                                    if( atoi(anim_attrib->GetValue().c_str()) )
                                                    {
                                                        anim_attrib = anim_attrib->GetNext();

                                                        sprite->play_animationSet( atoi(anim_attrib->GetValue().c_str()) );
                                                        sprite->UseAnimation(true);
                                                    }
                                                }
                                            }
                                            else if( anim_attrib->GetName() == "enabled" )
                                            {
                                                Text * text = (Text*)_entity;
                                                text->AnimateText( (bool)atoi( anim_attrib->GetValue().c_str() ) );

                                                anim_attrib = anim_attrib->GetNext();
                                                text->SetFrameRate( atoi(anim_attrib->GetValue()) );
                                            }

                                            anim_attrib = anim_attrib->GetNext();
                                        }

                                        attach_anim = attach_anim->GetNext();
                                    }

                                    //////////////////
                                    //Attach scripts//
                                    //////////////////

                                    attach_anim = scene_node->GetChildren();

                                    while( attach_anim )
                                    {
                                        if(attach_anim->GetName()=="Script")
                                        {
                                            //Attaching Scripts To Objects
                                            pScript * script = NULL;
                                            wxXmlAttribute * attrib = attach_anim->GetAttributes();

                                            std::string object_name = _entity->getName();
                                            std::string script_name = (std::string)attrib->GetValue();
                                            attrib = attrib->GetNext();
                                            bool isrun = (bool) atoi( attrib->GetValue().c_str() );

                                            script = tree_view->AddScriptFromResource(_entity, script_name, nScenes);
                                            if( isrun )
                                                script->run();
                                            else
                                                script->stop();

                                            //script->AddVar("timer");
                                            //script->AddVar("bool");
                                            //script->AddVar("int");
                                            wxXmlNode * script_var_node = attach_anim->GetChildren();

                                            while( script_var_node )
                                            {
                                                std::cout << "VARS: " << script_var_node->GetAttributes()->GetName() << " , " << script_var_node->GetAttributes()->GetValue() << std::endl;;
                                                //exit(0);
                                                //system("PAUSE");

                                                //tree_view->AddVarToScript2(_entity->getName() + "Scripts", script_name, "timer", "");
                                                //tree_view->AddVarToScript2(_entity->getName() + "Scripts", script_name, "bool", "");
                                                //tree_view->AddVarToScript2(_entity->getName() + "Scripts", script_name, "int", "");
                                                wxXmlAttribute * var_attrib = script_var_node->GetAttributes();
                                                while( var_attrib )
                                                {
                                                    if( var_attrib->GetValue() == "timer" )
                                                    {
                                                        var_attrib = var_attrib->GetNext();
                                                        tree_view->AddVarToScript2(_entity->getName() + "Scripts", script_name, "timer", (std::string)var_attrib->GetValue());
                                                    }
                                                    else if( var_attrib->GetValue() == "string" )
                                                    {
                                                        var_attrib = var_attrib->GetNext();

                                                        std::string var_name =  (std::string)var_attrib->GetValue();
                                                        var_attrib = var_attrib->GetNext();
                                                        std::string var_value =  (std::string)var_attrib->GetValue();

                                                        tree_view->AddVarToScript2(_entity->getName() + "Scripts", script_name, "string", (std::string)var_name);
                                                        script->SetVarStr(var_name.c_str(), var_value);
                                                    }
                                                    else if( var_attrib->GetValue() == "float" )
                                                    {
                                                        var_attrib = var_attrib->GetNext();

                                                        std::string var_name =  (std::string)var_attrib->GetValue();
                                                        var_attrib = var_attrib->GetNext();
                                                        std::string var_value =  (std::string)var_attrib->GetValue();

                                                        tree_view->AddVarToScript2(_entity->getName() + "Scripts", script_name, "float", (std::string)var_name);
                                                        script->SetVarFloat(var_name.c_str(), atof(var_value.c_str()));
                                                    }
                                                    else if( var_attrib->GetValue() == "bool" )
                                                    {
                                                        var_attrib = var_attrib->GetNext();

                                                        std::string var_name =  (std::string)var_attrib->GetValue();
                                                        var_attrib = var_attrib->GetNext();
                                                        std::string var_value =  (std::string)var_attrib->GetValue();

                                                        tree_view->AddVarToScript2(_entity->getName() + "Scripts", script_name, "bool", (std::string)var_name);
                                                        script->SetVarBool(var_name.c_str(), atoi(var_value.c_str()));
                                                    }
                                                    else if( var_attrib->GetValue() == "int" )
                                                    {
                                                        var_attrib = var_attrib->GetNext();

                                                        std::string var_name =  (std::string)var_attrib->GetValue();
                                                        var_attrib = var_attrib->GetNext();
                                                        std::string var_value =  (std::string)var_attrib->GetValue();

                                                        tree_view->AddVarToScript2(_entity->getName() + "Scripts", script_name, "int", (std::string)var_name);
                                                        script->SetVarInt(var_name.c_str(), atoi(var_value.c_str()));
                                                    }

                                                    var_attrib = var_attrib->GetNext();
                                                }

                                                script_var_node = script_var_node->GetNext();
                                            }

                                        }

                                        attach_anim = attach_anim->GetNext();
                                    }
                                }

                                std::cout << std::endl;
                                scene_node = scene_node->GetNext();
                            }
                        }

                        if( scene_node != NULL )
                        scene_node = scene_node->GetChildren();

                    }

                }

                child = child->GetNext();
            }
        }
    }
}

bool ProjectFile::IsModified()
{
    return FileModified;
}

void ProjectFile::SetModified(bool b)
{
    FileModified = b;
}

std::string ProjectFile::GetDirectoryBaseFile()
{
	return ProjectDirectoryFile;
}

void ProjectFile::ClearDirectoryBaseFile()
{
	ProjectDirectoryFile = "";
}
