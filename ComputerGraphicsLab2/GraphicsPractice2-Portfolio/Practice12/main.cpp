#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <SDL2/SDL.h>

class Practice12 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    Practice12() : OgreBites::ApplicationContext("Practice12") {}

    void setup() override
    {
        // �⺻ ������ ȣ���Ͽ� �⺻ ������ �����մϴ�.
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        // SceneManager ����
        Ogre::SceneManager* scnMgr = getRoot()->createSceneManager();

        // RTShader �ý��� ����
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // ī�޶� ����
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);

        // ī�޶� ��� ���� �� ī�޶� ����
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->attachObject(cam);
        camNode->setPosition(0, 100, 200);
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);

        // ����Ʈ ����
        getRenderWindow()->addViewport(cam);


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

        // Sinbad ��ƼƼ ���� �� ��� ��忡 ����
        Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode("Node1");
        Ogre::Entity* ent2 = scnMgr->createEntity("Entity1", "Sinbad.mesh");

        // MyMaterial18�̶�� �̸��� ���� ����
        ent2->setMaterial(Ogre::MaterialManager::getSingleton().getByName("MyMaterial10"));
        node->attachObject(ent2);
        node->setScale(Ogre::Vector3(5.0f, 5.0f, 5.0f));
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
    Practice12 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
