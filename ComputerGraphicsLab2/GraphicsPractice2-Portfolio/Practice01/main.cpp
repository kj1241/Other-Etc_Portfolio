#include "ExampleApplication.h"

class Practice1 : public ExampleApplication
{
public:
    void createScene(Ogre::SceneManager* scnMgr) override
    {
        Ogre::Entity* ent = scnMgr->createEntity("MyEntity", "Sinbad.mesh");
        scnMgr->getRootSceneNode()->attachObject(ent);
    }
};

int main(int argc, char** argv)
{
    Practice1 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}