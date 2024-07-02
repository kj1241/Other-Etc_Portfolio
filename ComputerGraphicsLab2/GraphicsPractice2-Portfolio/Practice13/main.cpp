//#include <Ogre.h>
//#include <OgreApplicationContext.h>
//#include <OgreInput.h>
//#include <OgreFrameListener.h>
//#include <OgreMaterialManager.h>
//#include <OgreRTShaderSystem.h>
//#include <OgreCompositorManager.h>
//#include <SDL2/SDL.h>
//#include <iostream>
//
//class Practice13 : public OgreBites::ApplicationContext, public OgreBites::InputListener {
//public:
//    Practice13() : OgreBites::ApplicationContext("Practice13") {}
//
//    void setup() override {
//        OgreBites::ApplicationContext::setup();
//        addInputListener(this);
//
//        Ogre::Root* root = getRoot();
//        Ogre::SceneManager* scnMgr = root->createSceneManager();
//
//        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
//        shadergen->addSceneManager(scnMgr);
//
//        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//
//        Ogre::Camera* cam = scnMgr->createCamera("myCam");
//        cam->setNearClipDistance(5);
//        cam->setAutoAspectRatio(true);
//
//        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        camNode->attachObject(cam);
//        camNode->setPosition(0, 50, 200);
//        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
//
//        getRenderWindow()->addViewport(cam);
//
//        Ogre::Light* light = scnMgr->createLight("MainLight");
//        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        lightNode->setPosition(0, 150, 250);
//        lightNode->attachObject(light);
//
//        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
//        Ogre::MeshManager::getSingleton().createPlane(
//            "plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
//            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
//
//        Ogre::Entity* ent = scnMgr->createEntity("LightPlaneEntity", "plane");
//        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
//        ent->setMaterialName("Examples/BeachStones");
//
//        Ogre::Entity* ogreEntity = scnMgr->createEntity("ogrehead.mesh");
//        Ogre::SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        ogreNode->setPosition(0, 0, 0);
//        ogreNode->attachObject(ogreEntity);
//
//        Ogre::CompositorManager::getSingleton().addCompositor(getRenderWindow()->getViewport(0), "Compositor1");
//        Ogre::CompositorManager::getSingleton().setCompositorEnabled(getRenderWindow()->getViewport(0), "Compositor1", true);
//    }
//};
//
//int main(int argc, char** argv) {
//    try {
//        Practice13 app;
//        app.initApp();
//        app.getRoot()->startRendering();
//        app.closeApp();
//    }
//    catch (Ogre::Exception& e) {
//        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
//    }
//    return 0;
//}


#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <SDL2/SDL.h>
#include <OgreCompositorManager.h>

class Practice13 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    Practice13() : OgreBites::ApplicationContext("Practice13") {}

    void setup() override
    {
        // 기본 설정을 호출하여 기본 설정을 적용합니다.
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        // SceneManager 생성
        Ogre::SceneManager* scnMgr = getRoot()->createSceneManager();

        // RTShader 시스템 생성
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // 카메라 생성
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);

        // 카메라 노드 생성 및 카메라 부착
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->attachObject(cam);
        camNode->setPosition(0, 100, 200);
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);

        // 뷰포트 생성
        Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);
        vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
        cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

        Ogre::Light* light = scnMgr->createLight("MainLight");
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);
        lightNode->attachObject(light);

        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
        Ogre::MeshManager::getSingleton().createPlane(
            "plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        Ogre::Entity* ent = scnMgr->createEntity("LightPlaneEntity", "plane");
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
        ent->setMaterialName("Examples/BeachStones");

        // Sinbad 엔티티 생성 및 장면 노드에 부착
        Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode("Node1", Ogre::Vector3(0, 0, 10));
        Ogre::Entity* ent2 = scnMgr->createEntity("Entity1", "Sinbad.mesh");

        // MyMaterial18이라는 이름의 재질 적용
        //ent2->setMaterial(Ogre::MaterialManager::getSingleton().getByName("MyMaterial15"));
        node->attachObject(ent2);
        node->setScale(Ogre::Vector3(5.0f, 5.0f, 5.0f));

        // Compositor 설정
        Ogre::CompositorManager* compMgr = Ogre::CompositorManager::getSingletonPtr();
        if (compMgr->hasCompositorChain(vp))
        {
            compMgr->addCompositor(vp, "Compositor2");
            compMgr->setCompositorEnabled(vp, "Compositor2", true);
        }
        else
        {
            Ogre::LogManager::getSingleton().logMessage("Compositor definition not found: Compositor1");
        }
    }

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == SDLK_ESCAPE)
        {
            getRoot()->queueEndRendering();
        }
        return true;
    }
};

int main(int argc, char** argv)
{
    Practice13 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}