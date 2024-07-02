#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>

class Practice4 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    Practice4() : OgreBites::ApplicationContext("Practice4") {}

    void setup() override
    {
        // �⺻ ���� �ʱ�ȭ
        OgreBites::ApplicationContext::setup();

        // Root, SceneManager �� RenderWindow ��������
        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // ī�޶� ����
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);
        camNode->setPosition(0, 10, 50);

        // Viewport�� ī�޶� �߰�
        getRenderWindow()->addViewport(cam);

        // ��� ����
        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
        Ogre::MeshManager::getSingleton().createPlane("plane",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        Ogre::Entity* planeEntity = scnMgr->createEntity("plane");
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(planeEntity);
        planeEntity->setMaterialName("Examples/BeachStones");


        // ���� �߰�
        Ogre::Light* light = scnMgr->createLight("Light");
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 0.0f));

        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 20, 0);  // ������ ī�޶� ��ó�� ��ġ
        lightNode->setDirection(Ogre::Vector3(0, -1, -1));
        lightNode->attachObject(light);


        Ogre::Light* light1 = scnMgr->createLight("Light1");
        light1->setType(Ogre::Light::LT_POINT);
        light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
        light1->setSpotlightInnerAngle(Ogre::Degree(5.0f));
        light1->setSpotlightOuterAngle(Ogre::Degree(45.0f));
        light1->setSpotlightFalloff(0.0f);
        light1->setDiffuseColour(Ogre::ColourValue(0.0f, 1.0f, 0.0f));

        Ogre::SceneNode* lightNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode2->setPosition(0, 20, 0);  // ������ ī�޶� ��ó�� ��ġ
        lightNode2->attachObject(light1);

        // ����Ʈ ��ƼƼ �߰�
        Ogre::Entity* sphereEntity = scnMgr->createEntity("sphere.mesh");
        Ogre::SceneNode* sphereNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        sphereNode->setScale(0.1f, 0.1f, 0.1f);
        sphereNode->setPosition(0, 20, 0);
        sphereNode->attachObject(sphereEntity);
    }
};

int main(int argc, char** argv)
{
    Practice4 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
