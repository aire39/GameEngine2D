#ifndef UIFILE_H
#define UIFILE_H

#include <wx/xml/xml.h>
#include <wx/imaglist.h>

class UIFile
{
    private:

        wxXmlDocument document;
        wxXmlNode   * root;

        wxImageList * treeView_images;
        wxImageList * toolBarApp_images;
        wxImageList * toolBarScene_images;

    public:

        UIFile();
        ~UIFile();

        void Save();
        void Load();
};

#endif // UIFILE_H
