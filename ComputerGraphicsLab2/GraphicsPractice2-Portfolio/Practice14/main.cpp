#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreFrameListener.h>
#include <OgreMaterialManager.h>
#include <OgreRTShaderSystem.h>
#include <SDL2/SDL.h>
#include <OgreCompositorManager.h>
#include <OgreParticleSystem.h>
#include <iostream>

class Practice14 : public OgreBites::ApplicationContext, public OgreBites::InputListener {
public:
    Practice14() : OgreBites::ApplicationContext("Practice14") {}

    void setup() override {
        // �ݵ�� �θ� Ŭ������ setup �޼��带 ȣ���ؾ� �մϴ�.
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();

        // RTSS(�ǽð� ���̴� �ý���)�� ��� ���
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // ī�޶� ����
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);

        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->attachObject(cam);
        camNode->setPosition(0, 50, 200);
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);

        getRenderWindow()->addViewport(cam);

        // ���� ����
        Ogre::Light* light = scnMgr->createLight("MainLight");
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 150, 250);
        lightNode->attachObject(light);

        // �ٴڸ� ����
        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
        Ogre::MeshManager::getSingleton().createPlane(
            "plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        Ogre::Entity* ent = scnMgr->createEntity("LightPlaneEntity", "plane");
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
        ent->setMaterialName("Examples/BeachStones");

        // ���� �ý��� ����
        Ogre::ParticleSystem* partSystem = scnMgr->createParticleSystem("Smoke", "Examples/Smoke");
        Ogre::SceneNode* partNode = scnMgr->getRootSceneNode()->createChildSceneNode("ParticleNode");
        partNode->attachObject(partSystem);
        partNode->setPosition(0, 0, 0);
    }
};

int main(int argc, char** argv) {
    try {
        Practice14 app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (Ogre::Exception& e) {
        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
    }
    return 0;
}
