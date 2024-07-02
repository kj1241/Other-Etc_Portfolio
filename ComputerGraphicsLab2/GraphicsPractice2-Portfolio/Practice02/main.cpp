#include "ExampleApplication.h"

class Practice2 : public ExampleApplication
{
public:
    void createScene(Ogre::SceneManager* scnMgr) override
    {
        Ogre::Entity* ent = scnMgr->createEntity("MyEntity", "Sinbad.mesh");
        Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
        node->setPosition(10, 10, 0);
        scnMgr->getRootSceneNode()->addChild(node);
        node->attachObject(ent);

    }
};

int main(int argc, char** argv)
{
    Practice2 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}