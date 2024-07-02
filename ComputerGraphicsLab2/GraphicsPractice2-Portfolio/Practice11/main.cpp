#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>

class Practice11 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    Practice11() : OgreBites::ApplicationContext("Practice11") {}

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

        // 뷰포트 생성
        getRenderWindow()->addViewport(cam);

        // 평면 생성
        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
        Ogre::MeshManager::getSingleton().createPlane("plane",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        Ogre::Entity* ent = scnMgr->createEntity("GrassPlane", "plane");
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
        ent->setMaterialName("Examples/GrassFloor");

        // 조명 생성
        Ogre::Light* light = scnMgr->createLight("Light1");
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        lightNode->attachObject(light);
        lightNode->setDirection(Ogre::Vector3(1, -1, 0));

        // ManualObject 생성
        Ogre::ManualObject* manual = scnMgr->createManualObject("grass");
        manual->begin("Examples/GrassBlades", Ogre::RenderOperation::OT_TRIANGLE_LIST);

        manual->position(5.0, 0.0, 0.0);
        manual->textureCoord(0, 1);
        manual->position(-5.0, 10.0, 0.0);
        manual->textureCoord(1, 0);
        manual->position(-5.0, 0.0, 0.0);
        manual->textureCoord(1, 1);
        manual->position(5.0, 10.0, 0.0);
        manual->textureCoord(0, 0);

        manual->position(2.5, 0.0, 4.3);
        manual->textureCoord(0, 1);
        manual->position(-2.5, 10.0, -4.3);
        manual->textureCoord(1, 0);
        manual->position(-2.0, 0.0, -4.3);
        manual->textureCoord(1, 1);
        manual->position(2.5, 10.0, 4.3);
        manual->textureCoord(0, 0);

        manual->position(2.5, 0.0, -4.3);
        manual->textureCoord(0, 1);
        manual->position(-2.5, 10.0, 4.3);
        manual->textureCoord(1, 0);
        manual->position(-2.0, 0.0, 4.3);
        manual->textureCoord(1, 1);
        manual->position(2.5, 10.0, -4.3);
        manual->textureCoord(0, 0);

        manual->index(0);
        manual->index(1);
        manual->index(2);

        manual->index(0);
        manual->index(3);
        manual->index(1);

        manual->index(4);
        manual->index(5);
        manual->index(6);

        manual->index(4);
        manual->index(7);
        manual->index(5);

        manual->index(8);
        manual->index(9);
        manual->index(10);

        manual->index(8);
        manual->index(11);
        manual->index(9);

        manual->end();

        manual->convertToMesh("BladesOfGrass");

        Ogre::StaticGeometry* field = scnMgr->createStaticGeometry("FieldOfGrass");
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                Ogre::Entity* grassEnt = scnMgr->createEntity("BladesOfGrass");
                field->addEntity(grassEnt, Ogre::Vector3(i * 3, -10, j * 3));
            }
        }

        field->build();
    }
};

int main(int argc, char** argv)
{
    Practice11 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
