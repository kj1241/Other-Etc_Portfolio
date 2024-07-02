#include "ExampleApplication.h"

class Practice3 : public ExampleApplication
{
public:
    void createScene(Ogre::SceneManager* scnMgr) override
    {
        Ogre::Entity* ent = scnMgr->createEntity("MyEntity", "Sinbad.mesh");
        Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
        node->setPosition(0, 0, 0);
        scnMgr->getRootSceneNode()->addChild(node);
        node->attachObject(ent);

        Ogre::Entity* ent2 = scnMgr->createEntity("MyEntity2", "Sinbad.mesh");
        Ogre::SceneNode* node2 = scnMgr->createSceneNode("Node2");
        node->addChild(node2);
        node2->setPosition(10, 0, 0);
        node2->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
        node2->scale(2.0f, 2.0f, 2.0f);
        node2->attachObject(ent2);

        Ogre::Entity* ent3 = scnMgr->createEntity("MyEntity3", "Sinbad.mesh");
        Ogre::SceneNode* node3 = scnMgr->createSceneNode("Node3");
        node->addChild(node3);
        node3->translate(-10, 0, 0);
        node3->yaw(Ogre::Degree(90.0f));
        node3->scale(0.2f, 0.2f, 0.2f);
        node3->attachObject(ent3);

        Ogre::Entity* ent4 = scnMgr->createEntity("MyEntity4", "Sinbad.mesh");
        Ogre::SceneNode* node4 = scnMgr->createSceneNode("Node4");
        node->addChild(node4);
        node4->setPosition(-20, 0, 0);
        node4->roll(Ogre::Radian(Ogre::Math::HALF_PI));
        node4->attachObject(ent4);

        Ogre::Entity* ent5 = scnMgr->createEntity("MyEntity5", "Sinbad.mesh");
        Ogre::SceneNode* node5 = scnMgr->createSceneNode("Node5");
        node->addChild(node5);
        node5->translate(20, 0, 0, Ogre::Node::TS_LOCAL);
        node5->yaw(Ogre::Degree(90));
        node5->roll(Ogre::Degree(90));
        node5->attachObject(ent5);

        Ogre::Entity* ent6 = scnMgr->createEntity("MyEntity6", "Sinbad.mesh");
        Ogre::SceneNode* node6 = scnMgr->createSceneNode("Node6");
        node->addChild(node6);
        node6->translate(30, 0, 0);
        node6->yaw(Ogre::Degree(90), Ogre::Node::TS_WORLD);
        node6->roll(Ogre::Degree(90), Ogre::Node::TS_WORLD);
        node6->attachObject(ent6);

        Ogre::Entity* ent7 = scnMgr->createEntity("MyEntity7", "Sinbad.mesh");
        Ogre::SceneNode* node7 = scnMgr->createSceneNode("Node7");
        node->addChild(node7);
        node7->setPosition(0, 10, 0);
        node7->translate(0, 0, 10, Ogre::Node::TS_WORLD);
        node7->attachObject(ent7);

    }
};

int main(int argc, char** argv)
{
    Practice3 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
