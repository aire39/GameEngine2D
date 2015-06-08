#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <wx/xml/xml.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/thread.h>

#include "../Common/UtilityFunctions.h"
#include "../Common/GLee.h"
#include "../Window/textureResource.h"
#include "../Window/projectTreeView.h"
#include "../Management/scriptMng.h"
#include "../Window/animationResource.h"

#include <iostream>

class ProjectFile
{
    private:

        bool FileModified;

        std::vector<entityManager *> * scene_manager;
        projectTreeView  * tree_view;
        scriptMng        * script_manager;
        texMng           * texture_manager;
        animationManager * anim_manager;

        textureResource   * texture_resource;
        animationResource * animation_resource;

        wxXmlDocument  doc;
        wxXmlNode    * root;

		std::string ProjectDirectoryFile;
        std::string ProjectDirectory;
        std::string ScriptDirectory;
        std::string ShaderDirectory;
        std::string TextureDirectory;

        std::string localizepath(std::string dir_name);

    public:

        ProjectFile();
        ~ProjectFile();

        void BindProjectTree(projectTreeView * tree_view);
        void BindSceneManager(std::vector<entityManager *> * scene_manager);
        void BindScriptManager(scriptMng * script_manager);
        void BindTextureManager(texMng * texture_manager);
        void BindAnimationManager(animationManager * anim_manager);
        void BindTextureResource(textureResource * texture_resource);
        void BindAnimationResource(animationResource * animation_resource);

        void Save();
        void SaveOutput(std::string path = "./projectfile.pshj");

        void Load(std::string path = "");

        bool IsModified();
        void SetModified(bool b);

		std::string GetDirectoryBaseFile();
		void ClearDirectoryBaseFile();
};

#endif // PROJECTFILE_H
