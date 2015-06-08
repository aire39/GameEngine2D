#include "../IO/UIFile.h"

UIFile::UIFile()
{
    treeView_images   = new wxImageList();
    toolBarApp_images = new wxImageList();
    toolBarScene_images = new wxImageList();
}

UIFile::~UIFile()
{
    delete treeView_images;
    delete toolBarApp_images;
    delete toolBarScene_images;
}

void UIFile::Save()
{

}

void UIFile::Load()
{

}
